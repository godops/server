#include "net-connection/NetConnection.h"
#include "request/RequestManager.h"
#include "threadpool/ThreadPool.h"
#include <cstdlib>
#include <fcntl.h>
#include <cerrno>
#include <vector>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/epoll.h>

#include <cstdio>
#include <cstring>
typedef std::vector<struct epoll_event> EventList;
using namespace std;

namespace
{
void unix_error(char *msg) /* unix-style error */
{
	fprintf(stderr, "%s: %s\n", msg, strerror(errno));
	exit(0);
}

int getPortFromCommandLine(char **argv)
{
	return atoi(argv[1]);
}

int getDefalutPort()
{
	return 8080;
}

int getPort(int argc, char **argv)
{
	if (argc == 2)
		return getPortFromCommandLine(argv);
	else
		return getDefalutPort();
}
}
static void SignalHandler(int nSigno)
{
    signal(nSigno, SignalHandler);
    switch(nSigno)
    {
    case SIGPIPE:
        printf("Process will not exit\n");
        break;
    default:
        printf("%d signal unregister\n", nSigno);
        break;
    }
}

void InitSignalHandler()
{
    signal(SIGPIPE , &SignalHandler);
}

int main(int argc, char **argv)
{
//	InitSignalHandler();
    signal(SIGPIPE, SIG_IGN);
    signal(SIGCHLD, SIG_IGN);
	NetConnection connection;
//	ThreadPool pool;

	int listenfd = connection.lisen(getPort(argc, argv));
//	pool.Create();
	//设置epoll的属性
	int epollfd;
	epollfd = epoll_create1(EPOLL_CLOEXEC);
	struct epoll_event event;
	vector<int> clients;
	event.data.fd = listenfd;
	//默认出发模式是LT模式（电平出发模式），或上EPOLLET变成ET模式（边沿触发）
	event.events = EPOLLIN;
	//把listenfd事件添加到epollfd进行管理
	epoll_ctl(epollfd, EPOLL_CTL_ADD, listenfd, &event);
	///定义事件列表，初始状态为16个，不够时进行倍增
	EventList events(16);

    struct sockaddr_in peeraddr;
    socklen_t peerlen;
	int nready;
	while (1)
	{		//epoll加在这
		nready = epoll_wait(epollfd, &*events.begin(), static_cast<int>(events.size()), -1);
		if(nready == -1)
		{
			if (errno == EINTR)
				continue;
			unix_error("epoll_wait");
		}
        if (nready == 0)//没有事件发生
            continue;
        //如果事件的数量达到预定义的上限值
        if ((size_t)nready == events.size())
             events.resize(events.size()*2);//扩充为原来的两倍
        int connfd;
        for (int i = 0; i < nready; ++i)
        {
        	if (events[i].data.fd == listenfd)
        	{
        		peerlen = sizeof(peeraddr);
        	//	connfd = ::accept4(listenfd, (struct sockaddr*)&peeraddr,&peerlen, SOCK_NONBLOCK | SOCK_CLOEXEC);
        		connfd = connection.accept();
        		if(connfd < 0)
        			unix_error("accept");
                clients.push_back(connfd);
                event.data.fd = connfd;
                event.events = EPOLLIN;//或EPOLLET变成ET模式
                //把新接受的事件加入关注
                epoll_ctl(epollfd, EPOLL_CTL_ADD, connfd, &event);
        	}
            //如果是pollin事件
            else if (events[i].events & EPOLLIN)
            {//取出文件描述符
                connfd = events[i].data.fd;
                if (connfd < 0)
                    continue;
//                pool.AddTask(connfd);
                RequestManager(connfd).run();
            }
        }
	}
	return 0;
}

#ifndef NET_CONNECTION_H
#define NET_CONNECTION_H

class NetConnection
{
public:
	NetConnection();
	int lisen(int port);
	int accept();
	void close();

private:
	int lisenfd;
	int connfd;
};

#endif

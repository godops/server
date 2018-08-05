/*
 * ThreadPool.cpp
 *
 *  Created on: 2018年8月1日
 *      Author: gongbiaoshuai
 */

#include <pthread.h>
#include <cstdlib>
#include <fcntl.h>
#include <cerrno>
#include <cstdio>
#include "ThreadPool.h"
#include "../request/RequestManager.h"

#define m_thread 5
pthread_t* pthread_id = new pthread_t[m_thread];
pthread_mutex_t Mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t Cond = PTHREAD_COND_INITIALIZER;

struct Task *head = NULL,*tail = NULL;

//回调函数
void* ThreadPool::func(void*)
{
	int fd = -1;

		pthread_mutex_lock(&Mutex);
		if(head == NULL)
			pthread_cond_wait(&Cond, &Mutex);
		fd = head->fd;
		struct Task* tmp  = head;
		head = head->next;
		delete tmp;
		pthread_mutex_unlock(&Mutex);
		RequestManager(fd).run();
}

int ThreadPool::Create()
{
	int err;
	for(int i = 0; i < m_thread; i++)
		err = pthread_create(&pthread_id[i], NULL, func, NULL);
	if(err != 0)
	{
		printf("pthread_create error");
		return -1;
	}
	return 0;
}

int ThreadPool::AddTask(int fd)
{
	pthread_mutex_lock(&Mutex);
	struct Task *new_task = new Task();
	new_task->fd = fd;
	new_task->next = NULL;
	if(head == NULL)
	{
		head = new_task;
		tail = new_task;
	}
	else
	{
		tail->next = new_task;
		tail = new_task;
	}
	pthread_cond_broadcast(&Cond);
	pthread_mutex_unlock(&Mutex);

	return 0;
}
int ThreadPool::Destory()
{
	//唤醒所有线程
	pthread_cond_broadcast(&Cond);

	//清楚僵尸
	for(int i = 0; i < m_thread; i++)
	{
		pthread_join(pthread_id[i], NULL);
	}

	delete [] pthread_id;
    pthread_id = NULL;

	//销毁互斥量和条件变量
    pthread_mutex_destroy(&Mutex);
    pthread_cond_destroy(&Cond);
    return 0;
}

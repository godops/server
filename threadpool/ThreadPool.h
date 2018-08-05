/*
 * ThreadPool.h
 *
 *  Created on: 2018年8月1日
 *      Author: gongbiaoshuai
 */

#ifndef THREADPOOL_THREADPOOL_H_
#define THREADPOOL_THREADPOOL_H_

struct Task
{
	int fd;
	Task *next;
};

class ThreadPool
{
public:
	static void* func(void*);
	int Create();
	int AddTask(int fd);
	int Destory();
};



#endif /* THREADPOOL_THREADPOOL_H_ */

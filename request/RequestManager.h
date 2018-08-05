#ifndef REQUEST_MANAGER_H
#define REQUEST_MANAGER_H

#include <string>

class Request;

class RequestManager
{
public:
	RequestManager(int connfd);
	void run();

private:
	Request* getRequestHandle();

private:
	int fileDescriptor;

	Request* request;
};

#endif

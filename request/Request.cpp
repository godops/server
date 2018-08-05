/*
 * Request.cpp
 *
 *  Created on: 2015年1月10日
 *      Author: augustus
 */
#include "Request.h"

void Request::init(int fd, std::string uri)
{
	 this->fileDescriptor = fd;
	 this->uri = uri;
}

void Request::execute()
{
	doExecute();
}

int Request::getFileDescriptor() const
{
	return fileDescriptor;
}

const std::string& Request::getUri() const
{
	return uri;
}




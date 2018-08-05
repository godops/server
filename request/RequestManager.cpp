#include "RequestManager.h"
#include "Request.h"
#include "RequestCreater.h"
#include "../base/IoReader.h"

namespace
{
class Parser
{
public:
	Parser(int connfd)
	{
		parseRequestHeaders(connfd);
	}

	const std::string getMethodName()
	{
		return method;
	}

	const std::string getUri()
	{
		return uri;
	}

private:
	void parseRequestHeaders(int fd)
	{
		IoReader reader(fd);
		std::vector<std::string> header;
		reader.getLineSplitedByBlank(header);

		method = header[0];
		uri = header[1];
		version = header[2];
	}

private:
	std::string method;
	std::string uri;
	std::string version;
};
}

RequestManager::RequestManager(int connfd) : fileDescriptor(connfd), request(0)
{
}

void RequestManager::run()
{
	if(getRequestHandle())
	    request->execute();
}

Request* RequestManager::getRequestHandle()
{
	Parser parser(fileDescriptor);
	return request = RequestCreater::getRequestHandler(fileDescriptor, parser.getMethodName(), parser.getUri());
}


#ifndef REQUEST_H
#define REQUEST_H

#include <string>

class Request
{
public:
	void init(int fd, std::string uri);
	void execute();
	virtual ~Request()
	{

	}

protected:
	int getFileDescriptor() const;
	const std::string& getUri() const;

private:
	virtual void doExecute() = 0;

private:
	int fileDescriptor;
	std::string uri;
};

#endif

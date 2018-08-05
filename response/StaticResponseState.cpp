/*
 * StaticResponseState.cpp
 *
 *  Created on: 2015年1月16日
 *      Author: augustus
 */

#include "StaticResponseState.h"
#include "../base/IoWriter.h"

StaticResponseState::StaticResponseState(int fd, std::string fName) : ResponseState(fd, fName)
{

}

const std::string StaticResponseState::buildForbiddenMsg()
{
	return "Tiny couldn't read the file";
}

void StaticResponseState::doRespond()
{
	IoWriter writer(getFileDescriptor());
	writer.writeString(buildRespondHeaders());
	writer.writeFile(getFileName(), getStat().st_size);
}

const std::string StaticResponseState::buildRespondHeaders()
{
	return ResponseState::buildRespondHeaders()
				+ std::string("Cache-Control: ")
				+ std::string("private")
//				+ std::string("max-age=315360000")
				+ "\r\n"
//				+ std::string("Last_Modify: ")
//				+ std::string("Tue, 23 Jan 2018 02:55:45 GMT")
//				+"\r\n"
				+ std::string("Content-length: ")
		        + sizeTypeToStr(getStat().st_size)
				+ "\r\n"
				+ std::string("Connection: ")
				+ std::string("keep-alive")
				+ "\r\n"
				+ std::string("Content-type: ")
		        + getFiletype()
				+ "\r\n\r\n";
}

const std::string StaticResponseState::getFiletype()
{
	std::string fileName = getFileName();
	if (fileName.find(".html"))
		return std::string("text/html");
	else if (fileName.find(".gif"))
		return std::string("image/gif");
	else if (fileName.find(".jpg"))
		return std::string("image/jpeg");
	else
		return std::string("text/plain");
}



/*
 * IoWriter.h
 *
 *  Created on: 2015年1月11日
 *      Author: augustus
 */

#ifndef IOWRITER_H_
#define IOWRITER_H_

#include <string>

class IoWriter
{
public:
	IoWriter(int fd);
	void writeString(const std::string& str);
	void writeFile(const std::string& fileName, int filesSize);
private:
	int fileDescriptor;
};



#endif /* IOWRITER_H_ */

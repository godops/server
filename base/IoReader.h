/*
 * IoReader.h
 *
 *  Created on: 2015年1月11日
 *      Author: augustus
 */

#ifndef IOREADER_H_
#define IOREADER_H_

#include <string>
#include <vector>

class IoReader
{
public:
	IoReader(int fd);
	void getLineSplitedByBlank(std::vector<std::string>& buf);
};

#endif /* IOREADER_H_ */

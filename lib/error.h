#ifndef __ERROR_REPORT__H__
#define __ERROR_REPORT__H__
#include <iostream>
#include <string>

class ErrorReporter
{

private:
	unsigned long many;
	bool hadError;

public:
	void report(std::string token, unsigned int line, unsigned int column, std::string message)
	{
		std::cerr <<message<< "[Lines: " << line << ":" << column << "]\t"
				  << "Token: " << token << '\n';
	}
};
#endif //__ERROR_REPORT__H__

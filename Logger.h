#pragma once

#include <fstream>

class Logger
{
	static Logger *instance;
	std::ofstream fout;
	char *buffer;
	Logger(void);
public:
	static Logger* client(void);
	~Logger(void);
	void write(char* message, bool writeNewLine = true);
	void writeToBuffer(const char *message);
	void writeBuffer(void);
	void close(void);
};

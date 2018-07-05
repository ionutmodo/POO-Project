#pragma warning(disable:4996)
#include "Logger.h"
#include "Util.h"
#include "HierarchyHeaders.h"
#include "DefinedCodes.h"

Logger* Logger::instance = new Logger;

Logger::Logger(void)
{
	fout.open("Events.log");
	buffer = new char[MAX];
	memset(buffer, '\0', MAX - 1);
}

Logger* Logger::client(void)
{
	return instance;
}

void Logger::write(char *message, bool writeNewLine)
{
	if (message)
	{
		fout << Util::getTime() << message;
		if(writeNewLine)
			fout << enter;
	}
}

void Logger::writeToBuffer(const char *message)
{
	uint bufferLength = strlen(buffer);
	uint messageLength = strlen(message);
	// daca mesajul incape in buffer
	if (bufferLength + messageLength < MAX - 1)
		strcat(buffer, message); // il scriu
	else
	{
		write(buffer, false); // pun continutul in fisier
		memset(buffer, '\0', MAX - 1); // golesc bufferul
		strcpy(buffer, message); // completez mesajul
	}
}

void Logger::writeBuffer(void)
{
	write(buffer);
	memset(buffer, '\0', MAX - 1);
}

Logger::~Logger(void)
{
	fout.flush();
	fout.close();
	Util::forgetString(buffer);
}

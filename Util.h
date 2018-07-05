#pragma once

#include <iostream>
#include "Logger.h"
using namespace std;

typedef unsigned int uint;

class Util
{
	static char* readString(istream &in, const char *message, uint minLength);
	static uint whitespacesCount(char *buffer);
	static bool isWhitespace(char ch);
public:
	static bool ERROR;
	static bool isCin(istream &in);
	static bool isCout(ostream &out);
	static bool stringsEqual(const char* const first, const char* const second);
	static uint characterCount(const char* buffer, char ch);
	static char* charToString(char ch);
	static char* trim(const char *str);
	static char* removeTabs(const char *str);
	static char* getTime(void);
	static void warning(const char *line);
	static void clearBuffer(istream &in);
	static void validateTrue(bool condition, char *message);
	static void forgetString(char *&str);
	static void forgetArray(char **&str, int length);
	static char* copyString(const char *str);
	static void openFile(const char *fileName);
	template<typename T> static bool successfullyRead(const char *buffer, T &value);
	template<typename T> static T read(istream &in, const char *message);
	template<typename T> static void write(ostream &out, const char* message, T content, bool writeNewLine);
};

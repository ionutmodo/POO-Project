#pragma warning(disable:4996)
#include <ctime>
#include <sstream>
#include "Util.h"
#include "HierarchyHeaders.h"
#include "DefinedCodes.h"

bool Util::ERROR = false;

bool Util::isCin(istream &in)
{
	return (&in == &cin);
}

bool Util::isCout(ostream &out)
{
	return (&out == &cout);
}

bool Util::stringsEqual(const char* const first, const char* const second)
{
	return (strcmp(first, second) == 0);
}

uint Util::characterCount(const char* buffer, char ch)
{
	uint counter = 0;
	int length = strlen(buffer);
	for (int i = 0; i < length; ++i)
		counter += (buffer[i] == ch);
	return counter;
}

char* Util::charToString(char ch)
{
	char *c = new char;
	*c = ch;
	return c;
}

char* Util::trim(const char *str)
{
	int length = strlen(str);
	int start = 0, stop = length - 1;
	while (start < length && isWhitespace(str[start]))
		++start;
	while (stop >= 0 && isWhitespace(str[stop]))
		--stop;
	char *trimmedString = new char[stop - start + 2];
	for (length = start; length <= stop; ++length)
		trimmedString[length - start] = str[length];
	trimmedString[length - start] = '\0';
	return trimmedString;
}

char* Util::removeTabs(const char *str)
{
	char *p, *copy = new char[2 + strlen(str)];
	strcpy(copy, str);
	while ((p = strchr(copy, '\t')) != nullptr)
	{
		copy[p - copy] = ' ';
	}
	return copy;
}

char* Util::getTime(void)
{
	time_t now = time(0);
	tm* time = localtime(&now);
	char *timeString = new char[16];
	sprintf(timeString, "[%02d:%02d:%02d] ", time->tm_hour, time->tm_min, time->tm_sec);
	return timeString;
}

void Util::warning(const char *line)
{
	Logger::client()->writeToBuffer("ERROR >>> Linia \"");
	Logger::client()->writeToBuffer(line);
	Logger::client()->writeToBuffer("\" nu a putut fi convertita la AutoMobil. Am trecut peste ea");
	Logger::client()->writeBuffer();
}

void Util::clearBuffer(istream &in)
{
	in.clear();
	in.ignore(MAX, '\n');
	Logger::client()->write("Util >>> clearBuffer");
}

void Util::validateTrue(bool condition, char *message)
{
	if (!condition)
	{
		Logger::client()->write(strcat("EROARE >>> ", message));
		Util::forgetString(message);
		exit(EXIT_FAILURE);
	}
}

void Util::forgetString(char *&str)
{
	if (str != nullptr)
	{
		delete[] str;
		str = nullptr;
	}
}

void Util::forgetArray(char **&str, int length)
{
	for (int i = 0; i < length; ++i)
		forgetString(str[i]);
	delete[] str;
	str = nullptr;
}

char* Util::copyString(const char *str)
{
	validateTrue(str != nullptr, "Nu pot determina lungimea unui string null");
	size_t size = (2 + strlen(str)) * sizeof(char);
	char *newString = new char[size];
	strcpy_s(newString, size, str);
	return newString;
}

void Util::openFile(const char *fileName)
{
	char *command = new char[128];
	strcpy(command, "explorer /e,");
	strcat(command, fileName);
	system(command);
	Util::forgetString(command);
}

bool Util::isWhitespace(char ch)
{
	return (ch == ' ') || (ch == '\t');
}

// numara cate caractere albe are parametrul la inceput si la sfarsit
uint Util::whitespacesCount(char *buffer)
{
	uint count = 0;
	int length = strlen(buffer);
	for (int i = 0; i < length && isWhitespace(buffer[i]); ++i)
		++count;
	for (int i = length - 1; i >= 0 && isWhitespace(buffer[i]); ++i)
		++count;
	return count;
}

template<typename T>
bool Util::successfullyRead(const char *buffer, T &value)
{
	const char *typeName = typeid(T).name();
	char *format[] = { "%d", "%f", "%u", "%c" };
	char *type[] = { _int_, _float_, _uint_, _char_ };
	for (int i = 0; i < 4; ++i)
		if (Util::stringsEqual(typeName, type[i]))
			return (sscanf(buffer, format[i], &value) > 0);
	return false;
}

char* Util::readString(istream &in, const char *message, uint minLength)
{
	char buffer[MAX];
	uint length;
	do
	{
		if (isCin(in))
			cout << message;
		in.getline(buffer, MAX - 1);
		length = strlen(trim(buffer));
	} while (length < minLength);
	char *newString = copyString(trim(buffer));
	return newString;
}

template<>
char* Util::read<char*>(istream &in, const char *message)
{
	return readString(in, message, 2);
}

template<typename T>
T Util::read(istream &in, const char *message)
{
	if (Util::isCin(in))
	{
		const char *typeName = typeid(T).name();
		char *format[] = { "%d", "%f", "%u", "%c" };
		char *type[] = { _int_, _float_, _uint_, _char_ };
		for (int index = 0; index < 4; ++index)
		{
			if (Util::stringsEqual(typeName, type[index]))
			{
				T value;
				char *buffer = Util::readString(in, message, 1);
				int code = sscanf(buffer, format[index], &value);
				while (code == 0)
				{
					Logger::client()->writeToBuffer("ERROR >>> Wrong Number Format: \"");
					Logger::client()->writeToBuffer(buffer);
					Logger::client()->writeToBuffer("\" nu contine un prefix de tip ");
					Logger::client()->writeToBuffer(type[index]);
					Logger::client()->writeBuffer();
					buffer = Util::readString(in, message, 1);
					code = sscanf(buffer, format[index], &value);
					if (Util::stringsEqual(buffer, "."))
						code = 0;
				}
				return value;
			}
		}
	}
	Util::ERROR = true;
	return 0;
}

template<typename T>
void Util::write(ostream &out, const char* message, T content, bool writeNewLine)
{
	if (!isCout(out)) // scriere in fisier
		out << content << separator;
	else // scriere la consola
	{
		out.width(16);
		out.fill(' ');
		out << message << tab << content;
	}
	if (writeNewLine)
		out << enter;
}

template bool Util::successfullyRead(const char *buffer, char  &value);
template bool Util::successfullyRead(const char *buffer, int   &value);
template bool Util::successfullyRead(const char *buffer, float &value);
template bool Util::successfullyRead(const char *buffer, uint  &value);

template char* Util::read<char*>(istream &in, const char* message);
template char  Util::read<char>(istream &in, const char* message);
template float Util::read<float>(istream &in, const char* message);
template int   Util::read<int>(istream &in, const char* message);
template uint  Util::read<uint>(istream &in, const char* message);

template void Util::write(ostream &out, const char* message, char* content, bool writeNewLine);
template void Util::write(ostream &out, const char* message, char  content, bool writeNewLine);
template void Util::write(ostream &out, const char* message, float content, bool writeNewLine);
template void Util::write(ostream &out, const char* message, int   content, bool writeNewLine);
template void Util::write(ostream &out, const char* message, uint  content, bool writeNewLine);

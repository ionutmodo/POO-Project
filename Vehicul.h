#pragma once

#include "Util.h"

using namespace std;

class Vehicul
{
public:
	virtual ~Vehicul(void);
	virtual uint codObiect(void);
	virtual bool read(istream &in, bool writeLog) = 0;
	virtual void write(ostream &out, bool writeClassCode, bool writeNewLine, bool writeLog) = 0;
};

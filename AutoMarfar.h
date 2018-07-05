#pragma once

#include "AutoVehicul.h"
#include "Util.h"

using namespace std;

class AutoMarfar : public virtual AutoVehicul
{
protected:
	static uint autoMarfarCount;
	uint volumLitri;
	char *dotari;
	AutoMarfar(char *dotari, uint volumLitri);
public:
	static uint getAutoMarfarCount(void);

	AutoMarfar(void);
	AutoMarfar(char *marca, char *model, uint anFabricatie, float consumMediu, uint pretEUR, char *numar, char *dotari, uint volumLitri);
	AutoMarfar(const AutoMarfar &o);
	~AutoMarfar(void);

	uint codObiect(void);

	bool read(istream &in, bool writeLog);
	void write(ostream &out, bool writeClassCode, bool writeNewLine = true, bool writeLog = true);

	char* getDotari(void) const;
	uint getVolumLitri(void) const;

	void setDotari(char *dotari);
	void setVolumLitri(uint volumLitri);

	AutoMarfar& operator = (const AutoMarfar &o);
};

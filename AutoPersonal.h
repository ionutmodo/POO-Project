#pragma once

#include "Util.h"
#include "AutoVehicul.h"
#include "DefinedCodes.h"

class AutoPersonal : public virtual AutoVehicul
{
protected:
	static uint autoPersonalCount;
	char *caroserie;
	uint numarPersoane;
	AutoPersonal(char *caroserie, uint numarPersoane);
public:
	static uint getAutoPersonalCount(void);

	AutoPersonal(void);
	AutoPersonal(char *marca, char *model, uint anFabricatie, float consumMediu, uint pretEUR, char *numar, char *caroserie, uint numarPersoane);
	AutoPersonal(const AutoPersonal &o);
	~AutoPersonal(void);

	uint codObiect(void);

	bool read(istream &in, bool writeLog);
	void write(ostream &out, bool writeClassCode, bool writeNewLine = true, bool writeLog = true);

	char* getCaroserie(void) const;
	uint getNumarPersoane(void) const;

	void setCaroserie(char *caroserie);
	void setNumarPersoane(uint numarPersoane);

	AutoPersonal& operator = (const AutoPersonal &o);
};

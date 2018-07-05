#pragma once

#include "AutoMarfar.h"
#include "AutoPersonal.h"
#include "Util.h"

class AutoMobil : public AutoMarfar, public AutoPersonal
{
protected:
	static uint autoMobilCount;
	uint vitezaMaxima;
	char *isLimuzina;
public:
	static uint getAutoMobilCount(void);

	AutoMobil(void);
	AutoMobil(char *marca, char *model, uint anFabricatie, float consumMediu, uint pretEUR, char *numar, char *dotari, uint volumLitri, char *caroserie, uint numarPersoane, uint vitezaMaxima, char *isLimuzina);
	~AutoMobil(void);

	uint codObiect(void);

	bool read(istream &in, bool writeLog);
	void write(ostream &out, bool writeClassCode, bool writeNewLine = true, bool writeLog = true);

	uint getVitezaMaxima(void) const;
	char* getIsLimuzina(void) const;

	void setVitezaMaxima(uint vitezaMaxima);
	void setIsLimuzina(char *isLimuzina);

	AutoMobil& operator = (const AutoMobil &o);
};

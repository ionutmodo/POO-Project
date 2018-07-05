#pragma once

#include "Vehicul.h"

class AutoVehicul : public Vehicul
{
protected:
	static uint autoVehiculCount;
	char *marca;
	char *model;
	uint anFabricatie;
	float consumMediu;
	uint pretEUR;
	char *numar;
public:
	static uint getAutoVehiculCount(void);

	AutoVehicul(void);
	AutoVehicul(char *marca, char *model, uint anFabricatie, float consumMediu, uint pretEUR, char *numar);
	AutoVehicul(const AutoVehicul &o);
	~AutoVehicul(void);

	uint codObiect(void);

	bool read(istream &in, bool writeLog);
	void write(ostream &out, bool writeClassCode, bool writeNewLine, bool writeLog);

	char* getMarca(void) const;
	char* getModel(void) const;
	uint getAnFabricatie(void) const;
	float getConsumMediu(void) const;
	uint getPretEUR(void) const;
	char* getNumar(void) const;

	void setMarca(char *marca);
	void setModel(char *model);
	void setAnFabricatie(uint anFabricatie);
	void setConsumMediu(float consumMediu);
	void setPretEUR(uint pretEUR);
	void setNumar(char *numar);

	AutoVehicul& operator = (const AutoVehicul &o);
};

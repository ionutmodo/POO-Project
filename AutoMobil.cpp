#pragma warning(disable:4996)
#include "AutoMobil.h"
#include "HierarchyHeaders.h"
#include "DefinedCodes.h"
#include "Factory.h"

uint AutoMobil::autoMobilCount = 0;

uint AutoMobil::getAutoMobilCount(void)
{
	return autoMobilCount;
}

AutoMobil::AutoMobil(void)
{
	++autoMobilCount;
	Logger::client()->write("AutoMobil >>> Constructor implicit");
}

AutoMobil::AutoMobil(char *marca, char *model, uint anFabricatie, float consumMediu, uint pretEUR, char *numar, char *dotari, uint volumLitri, char *caroserie, uint numarPersoane, uint vitezaMaxima, char *isLimuzina) :
	AutoVehicul(marca, model, anFabricatie, consumMediu, pretEUR, numar),
	AutoMarfar(dotari, volumLitri),
	AutoPersonal(caroserie, numarPersoane)
{
	++autoMobilCount;
	setVitezaMaxima(vitezaMaxima);
	setIsLimuzina(isLimuzina);
	Logger::client()->write("AutoMobil >>> Constructor initializare");
}

AutoMobil::~AutoMobil(void)
{
	++autoMarfarCount;
	++autoPersonalCount;
	--autoMobilCount;
	Logger::client()->write("AutoMobil >>> Destructor");
}

uint AutoMobil::codObiect(void)
{
	return _CodAutoMobil_;
}

bool AutoMobil::read(istream &in, bool writeLog)
{
	if (writeLog)
		Logger::client()->write("AutoMobil >>> read");
	if (Util::isCin(in))
	{
		AutoMarfar::read(in, false);
		AutoPersonal::setCaroserie(Util::read<char*>(in, "\tCaroserie: "));
		AutoPersonal::setNumarPersoane(Util::read<uint>(in, "\tPersoane: "));
		setVitezaMaxima(Util::read<uint>(in, "\tViteza maxima: "));
		setIsLimuzina(Util::read<char*>(in, "\tEste limuzina(Da/Nu): "));
		return true;
	}
	else // citire din fisier, citesc cate o linie formatata
	{
		// trebuie sa am in fisier 12 + 1 componente separate intre separatori
		// -> codul obiectului
		// -> 12 campuri pentru obiect
		// total: 13 campuri => 12 separatori
		char *line = Util::read<char*>(in, "");
		const uint maxObjectFields = 12;
		if (Util::characterCount(line, '\t') != maxObjectFields - 1)
		{
			Util::warning(line);
			Util::forgetString(line);
			return false;
		}
		int n;
		char *copyLine = Util::copyString(line);
		char **matrix = new char*[maxObjectFields];
		char *token = strtok(line, "\t");
		for (n = 0; token != nullptr; ++n)
		{
			matrix[n] = new char[2 + strlen(token)];
			strcpy(matrix[n], token);
			token = strtok(NULL, "\t");
		}
		int code;
		float floatValue, uintValue;
		setMarca(matrix[0]);
		setModel(matrix[1]);
		if (Util::successfullyRead(matrix[2], uintValue))
			setAnFabricatie(uintValue);
		else
		{
			Util::forgetArray(matrix, maxObjectFields);
			return false;
		}
		if (Util::successfullyRead(matrix[3], floatValue))
			setConsumMediu(floatValue);
		else
		{
			Util::forgetArray(matrix, maxObjectFields);
			return false;
		}
		if (Util::successfullyRead(matrix[4], uintValue))
			setPretEUR(uintValue);
		else
		{
			Util::forgetArray(matrix, maxObjectFields);
			return false;
		}
		setNumar(matrix[5]);
		setDotari(matrix[6]);
		if (Util::successfullyRead(matrix[7], uintValue))
			setVolumLitri(uintValue);
		else
		{
			Util::forgetArray(matrix, maxObjectFields);
			return false;
		}
		setCaroserie(matrix[8]);
		if (Util::successfullyRead(matrix[4], uintValue))
			setNumarPersoane(uintValue);
		else
		{
			Util::forgetArray(matrix, maxObjectFields);
			return false;
		}
		if (Util::successfullyRead(matrix[10], uintValue))
			setVitezaMaxima(uintValue);
		else
		{
			Util::forgetArray(matrix, maxObjectFields);
			return false;
		}
		setIsLimuzina(matrix[11]);
		return true;
	}
}

void AutoMobil::write(ostream &out, bool writeClassCode, bool writeNewLine, bool writeLog)
{
	if (writeClassCode)
		if (!Util::isCout(out))
			Util::write(out, "", codObiect(), false);
	bool writeNewLineConsideringOut = Util::isCout(out);
	AutoMarfar::write(out, false, writeNewLineConsideringOut, false);
	Util::write(out, "Caroserie: ", caroserie, writeNewLineConsideringOut);
	Util::write(out, "Persoane: ", numarPersoane, writeNewLineConsideringOut);
	Util::write(out, "Viteza maxima: ", vitezaMaxima, writeNewLineConsideringOut);
	Util::write(out, "Este limuzina: ", isLimuzina, writeNewLine);
	if (writeLog)
		Logger::client()->write("AutoMobil >>> write");
}

uint AutoMobil::getVitezaMaxima(void) const
{
	return this->vitezaMaxima;
}

char* AutoMobil::getIsLimuzina(void) const
{
	return this->isLimuzina;
}

void AutoMobil::setVitezaMaxima(uint vitezaMaxima)
{
	this->vitezaMaxima = vitezaMaxima;
}

void AutoMobil::setIsLimuzina(char *isLimuzina)
{
	Util::forgetString(this->isLimuzina);
	this->isLimuzina = Util::copyString(isLimuzina);
}

AutoMobil& AutoMobil::operator = (const AutoMobil &o)
{
	if (this != &o)
	{
		setMarca(o.marca);
		setModel(o.model);
		setAnFabricatie(o.anFabricatie);
		setConsumMediu(o.consumMediu);
		setPretEUR(o.pretEUR);
		setNumar(o.numar);
		setDotari(o.dotari);
		setVolumLitri(o.volumLitri);
		setCaroserie(o.caroserie);
		setNumarPersoane(o.numarPersoane);
		setVitezaMaxima(o.vitezaMaxima);
		setIsLimuzina(o.isLimuzina);
	}
	Logger::client()->write("AutoMobil >>> operator =");
	return *this;
}
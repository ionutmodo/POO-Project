#pragma warning(disable:4996)
#include "AutoMarfar.h"
#include "HierarchyHeaders.h"
#include "DefinedCodes.h"

uint AutoMarfar::autoMarfarCount = 0;

uint AutoMarfar::getAutoMarfarCount(void)
{
	return autoMarfarCount;
}

AutoMarfar::AutoMarfar(char *dotari, uint volumLitri)
{
	setDotari(dotari);
	setVolumLitri(volumLitri);
	Logger::client()->write("AutoMarfar >>> Constructor protected");
}

AutoMarfar::AutoMarfar(void)
{
	++autoMarfarCount;
	Logger::client()->write("AutoMarfar >>> Constructor implicit");
}

AutoMarfar::AutoMarfar(char *marca, char *model, uint anFabricatie, float consumMediu, uint pretEUR, char *numar, char *dotari, uint volumLitri) : AutoVehicul(marca, model, anFabricatie, consumMediu, pretEUR, numar)
{
	++autoMarfarCount;
	setVolumLitri(volumLitri);
	setDotari(dotari);
	Logger::client()->write("AutoMarfar >>> Constructor initializare");
}

AutoMarfar::AutoMarfar(const AutoMarfar &o)
{
	++autoMarfarCount;
	setMarca(o.marca);
	setModel(o.model);
	setAnFabricatie(o.anFabricatie);
	setConsumMediu(o.consumMediu);
	setPretEUR(o.pretEUR);
	setNumar(o.numar);
	setDotari(o.dotari);
	setVolumLitri(o.volumLitri);
	Logger::client()->write("AutoMarfar >>> Constructor copiere");
}

AutoMarfar::~AutoMarfar(void)
{
	--autoMarfarCount;
	Logger::client()->write("AutoMarfar >>> Destructor");
}

uint AutoMarfar::codObiect(void)
{
	return _CodAutoMarfar_;
}

bool AutoMarfar::read(istream &in, bool writeLog)
{
	if (writeLog)
		Logger::client()->write("AutoMarfar >>> read");
	if (Util::isCin(in))
	{
		AutoVehicul::read(in, false);
		setDotari(Util::read<char*>(in, "\tDotari: "));
		setVolumLitri(Util::read<uint>(in, "\tVolum(litri): "));
		return true;
	}
	else
	{
		// trebuie sa am in fisier 12 + 1 componente separate intre separatori
		// -> codul obiectului
		// -> 12 campuri pentru obiect
		// total: 13 campuri => 12 separatori
		char *line = Util::read<char*>(in, "");
		const uint maxObjectFields = 8;
		if (Util::characterCount(line, '\t') != maxObjectFields - 1)
		{
			Util::warning(line);
			Util::forgetString(line);
			return false;
		}
		int n;
		char **matrix = new char*[maxObjectFields];
		char *token = strtok(line, "\t");
		for (n = 0; token != nullptr; ++n)
		{
			matrix[n] = new char[2 + strlen(token)];
			strcpy(matrix[n], token);
			token = strtok(NULL, "\t");
		}
		Util::forgetString(line);
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
		return true;
	}
	return false;
}

void AutoMarfar::write(ostream &out, bool writeClassCode, bool writeNewLine, bool writeLog)
{
	if (writeClassCode)
		if (!Util::isCout(out))
			Util::write(out, "", codObiect(), false);
	bool writeNewLineConsideringOut = Util::isCout(out);
	AutoVehicul::write(out, false, writeNewLineConsideringOut, false);
	Util::write(out, "Dotari: ", dotari, writeNewLineConsideringOut);
	Util::write(out, "Volum(litri): ", volumLitri, writeNewLine);
	if(writeLog)
		Logger::client()->write("Vehicul >>> write");
}

char* AutoMarfar::getDotari(void) const
{
	return this->dotari;
}

uint AutoMarfar::getVolumLitri(void) const
{
	return this->volumLitri;
}

void AutoMarfar::setVolumLitri(uint volumLitri)
{
	this->volumLitri = volumLitri;
}

void AutoMarfar::setDotari(char *dotari)
{
	Util::forgetString(this->dotari);
	this->dotari = Util::copyString(dotari);
}

AutoMarfar& AutoMarfar::operator = (const AutoMarfar &o)
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
	}
	Logger::client()->write("AutoMarfar >>> operator =");
	return *this;
}

#pragma warning(disable:4996)
#include "AutoPersonal.h"
#include "HierarchyHeaders.h"
#include "DefinedCodes.h"

uint AutoPersonal::autoPersonalCount = 0;

uint AutoPersonal::getAutoPersonalCount(void)
{
	return autoPersonalCount;
}

AutoPersonal::AutoPersonal(char *caroserie, uint numarPersoane)
{
	setCaroserie(caroserie);
	setNumarPersoane(numarPersoane);
	
	
	("AutoPersonal >>> Constructor protected");
}

AutoPersonal::AutoPersonal(void)
{
	++autoPersonalCount;
	Logger::client()->write("AutoPersonal >>> Constructor implicit");
}

AutoPersonal::AutoPersonal(char *marca, char *model, uint anFabricatie, float consumMediu, uint pretEUR, char *numar, char *caroserie, uint numarPersoane) : AutoVehicul(marca, model, anFabricatie, consumMediu, pretEUR, numar)
{
	++autoPersonalCount;
	setCaroserie(caroserie);
	setNumarPersoane(numarPersoane);
	Logger::client()->write("AutoPersonal >>> Constructor initializare");
}

AutoPersonal::AutoPersonal(const AutoPersonal &o)
{
	++autoPersonalCount;
	setMarca(o.marca);
	setModel(o.model);
	setAnFabricatie(o.anFabricatie);
	setConsumMediu(o.consumMediu);
	setPretEUR(o.pretEUR);
	setNumar(o.numar);
	setCaroserie(o.caroserie);
	setNumarPersoane(o.numarPersoane);
	Logger::client()->write("AutoPersonal >>> Constructor copiere");
}

AutoPersonal::~AutoPersonal(void)
{
	--autoPersonalCount;
	Logger::client()->write("AutoPersonal >>> Destructor");
}

uint AutoPersonal::codObiect(void)
{
	return _CodAutoPersonal_;
}

bool AutoPersonal::read(istream &in, bool writeLog)
{
	if (writeLog)
		Logger::client()->write("AutoPersonal >>> read");
	if (Util::isCin(in))
	{
		AutoVehicul::read(in, false);
		setCaroserie(Util::read<char*>(in, "\tCaroserie: "));
		setNumarPersoane(Util::read<uint>(in, "\tPersoane: "));
		return true;
	}
	else
	{
		char *line = Util::read<char*>(in, "");
		const uint maxObjectFields = 8;
		if (Util::characterCount(line, '\t') != maxObjectFields - 1)
		{
			Util::warning(line);
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
		else return false;
		if (Util::successfullyRead(matrix[3], floatValue))
			setConsumMediu(floatValue);
		else return false;
		if (Util::successfullyRead(matrix[4], uintValue))
			setPretEUR(uintValue);
		else return false;
		setNumar(matrix[5]);
		setCaroserie(matrix[6]);
		if (Util::successfullyRead(matrix[7], uintValue))
			setNumarPersoane(uintValue);
		else return false;
		return true;
	}
}

void AutoPersonal::write(ostream &out, bool writeClassCode, bool writeNewLine, bool writeLog)
{
	if (writeClassCode)
		if (!Util::isCout(out))
			Util::write(out, "", codObiect(), false);
	bool writeNewLineConsideringOut = Util::isCout(out);
	AutoVehicul::write(out, false, writeNewLineConsideringOut, false);
	Util::write(out, "Caroserie: ", caroserie, writeNewLineConsideringOut);
	Util::write(out, "Persoane: ", numarPersoane, writeNewLine);
	if(writeLog)
		Logger::client()->write("AutoPersonal >>> write");
}

char* AutoPersonal::getCaroserie(void) const
{
	return this->caroserie;
}

uint AutoPersonal::getNumarPersoane(void) const
{
	return numarPersoane;
}

void AutoPersonal::setCaroserie(char *caroserie)
{
	Util::forgetString(this->caroserie);
	this->caroserie = Util::copyString(caroserie);
}

void AutoPersonal::setNumarPersoane(uint numarPersoane)
{
	this->numarPersoane = numarPersoane;
}

AutoPersonal& AutoPersonal::operator = (const AutoPersonal &o)
{
	if (this != &o)
	{
		setMarca(o.marca);
		setModel(o.model);
		setAnFabricatie(o.anFabricatie);
		setConsumMediu(o.consumMediu);
		setPretEUR(o.pretEUR);
		setNumar(o.numar);
		setCaroserie(o.caroserie);
		setNumarPersoane(o.numarPersoane);
	}
	Logger::client()->write("AutoPersonal >>> operator =");
	return *this;
}
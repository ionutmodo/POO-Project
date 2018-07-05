#pragma warning(disable:4996)
#include "AutoVehicul.h"
#include "HierarchyHeaders.h"
#include "DefinedCodes.h"

uint AutoVehicul::autoVehiculCount = 0;

uint AutoVehicul::getAutoVehiculCount(void)
{
	return autoVehiculCount;
}

AutoVehicul::AutoVehicul(void)
{
	++autoVehiculCount;
	Logger::client()->write("AutoVehicul >>> Constructor implicit");
}

AutoVehicul::AutoVehicul(char *marca, char *model, uint anFabricatie, float consumMediu, uint pretEUR, char *numar)
{
	++autoVehiculCount;
	setMarca(marca);
	setModel(model);
	setAnFabricatie(anFabricatie);
	setConsumMediu(consumMediu);
	setPretEUR(pretEUR);
	setNumar(numar);
	Logger::client()->write("AutoVehicul >>> Constructor initializare");
}

AutoVehicul::AutoVehicul(const AutoVehicul &o)
{
	++autoVehiculCount;
	setMarca(o.marca);
	setModel(o.model);
	setAnFabricatie(o.anFabricatie);
	setConsumMediu(o.consumMediu);
	setPretEUR(o.pretEUR);
	setNumar(o.numar);
	Logger::client()->write("AutoVehicul >>> Constructor copiere");
}

AutoVehicul::~AutoVehicul(void)
{
	Util::forgetString(marca);
	Util::forgetString(model);
	Util::forgetString(numar);
	Logger::client()->write("AutoVehicul >>> Destructor");
}

uint AutoVehicul::codObiect(void)
{
	return _CodAutoVehicul_;
}

bool AutoVehicul::read(istream &in, bool writeLog)
{
	if (writeLog)
		Logger::client()->write("AutoVehicul >>> read");
	if (Util::isCin(in))
	{
		setMarca(Util::read<char*>(in, "\tMarca: "));
		setModel(Util::read<char*>(in, "\tModel: "));
		setAnFabricatie(Util::read<uint>(in, "\tAn fabricatie: "));
		setConsumMediu(Util::read<float>(in, "\tConsum mediu: "));
		setPretEUR(Util::read<uint>(in, "\tPret(EUR): "));
		setNumar(Util::read<char*>(in, "\tNumar: "));
		return true;
	}
	else
	{
		char *line = Util::read<char*>(in, "");
		const uint maxObjectFields = 6;
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
		float floatValue;
		uint uintValue;
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
		return true;
	}
	return false;
}

void AutoVehicul::write(ostream &out, bool writeClassCode, bool writeNewLine, bool writeLog)
{
	if (writeClassCode && !Util::isCout(out))
		Util::write(out, "", codObiect(), false);
	bool writeNewLineConsideringOut = Util::isCout(out);
	Util::write(out, "Marca: ", marca, writeNewLineConsideringOut);
	Util::write(out, "Model: ", model, writeNewLineConsideringOut);
	Util::write(out, "An fabricatie: ", anFabricatie, writeNewLineConsideringOut);
	Util::write(out, "Consum mediu: ", consumMediu, writeNewLineConsideringOut);
	Util::write(out, "Pret(EUR): ", pretEUR, writeNewLineConsideringOut);
	Util::write(out, "Numar: ", numar, writeNewLine);
	if(writeLog)
		Logger::client()->write("AutoVehicul >>> write");
}

char* AutoVehicul::getMarca(void) const
{
	return this->marca;
}

char* AutoVehicul::getModel(void) const
{
	return this->model;
}

uint AutoVehicul::getAnFabricatie(void) const
{
	return this->anFabricatie;
}

float AutoVehicul::getConsumMediu(void) const
{
	return this->consumMediu;
}

uint AutoVehicul::getPretEUR(void) const
{
	return this->pretEUR;
}

char* AutoVehicul::getNumar(void) const
{
	return this->numar;
}

void AutoVehicul::setMarca(char *marca)
{
	Util::forgetString(this->marca);
	this->marca = Util::copyString(marca);
}

void AutoVehicul::setModel(char *model)
{
	Util::forgetString(this->model);
	this->model = Util::copyString(model);
}

void AutoVehicul::setAnFabricatie(uint anFabricatie)
{
	this->anFabricatie = anFabricatie;
}

void AutoVehicul::setConsumMediu(float consumMediu)
{
	this->consumMediu = consumMediu;
}

void AutoVehicul::setPretEUR(uint pretEUR)
{
	this->pretEUR = pretEUR;
}

void AutoVehicul::setNumar(char *numar)
{
	Util::forgetString(this->numar);
	this->numar = Util::copyString(numar);
}

AutoVehicul& AutoVehicul::operator = (const AutoVehicul &o)
{
	if (this != &o)
	{
		setMarca(o.marca);
		setModel(o.model);
		setAnFabricatie(o.anFabricatie);
		setConsumMediu(o.consumMediu);
		setPretEUR(o.pretEUR);
		setNumar(o.numar);
	}
	Logger::client()->write("AutoVehicul >>> operator =");
	return *this;
}
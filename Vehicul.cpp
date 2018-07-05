#include "Vehicul.h"
#include "DefinedCodes.h"

Vehicul::~Vehicul(void)
{
	Logger::client()->write("Vehicul >>> Destructor");
}

uint Vehicul::codObiect(void)
{
	return _CodVehicul_;
}
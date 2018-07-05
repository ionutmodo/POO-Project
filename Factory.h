#pragma once

#include "Util.h"
#include "DefinedCodes.h"
#include "HierarchyHeaders.h"

class Factory
{
public:
	static Vehicul* getObject(uint cod)
	{
		switch (cod)
		{
		case _CodAutoVehicul_:
			return new AutoVehicul;
		case _CodAutoMarfar_:
			return new AutoMarfar;
		case _CodAutoPersonal_:
			return new AutoPersonal;
		case _CodAutoMobil_:
			return new AutoMobil;
		default:
			return nullptr;
		}
	}
};

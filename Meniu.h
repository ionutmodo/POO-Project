#pragma once

#include "Util.h"
#include "Vehicul.h"
#include "LinkedList.h"
#include <conio.h>

class Meniu
{
	// optiunea utilizatorului
	uint option;

	// true daca s-a facut serializarea
	bool savedToFile;

	// folosit pentru inserarea unui nou obiect
	Vehicul *vehicul;

	// lista de obiecte
	LinkedList *list;

	// afiseazala ecran optiunile disponibile pentru meniu
	uint mainMenuMessages(void);

	// afiseaza la ecran ierarhie de clase si returneaza optiunea aleasa
	uint secondMenuMessages(void);

	// afiseaza la ecran mesajele pentru inserare
	void insertMessages(uint op);

	// face serializare atunci cand userul doreste asta (optiunea 4)
	void doSerializeOnRequest(void);
	
	// serializare automata la iesirea din aplicatie daca nu a fost serializat deja
	void doSerializeAutomatically(void);
	
	// face deserializare si memoreaza datele in lista
	void doDeserialize(void);
	
	// face inserarea unui element in lista
	void doInsert(void);
	
	// face o stergere dupa *numarul de inmatriculare* (il si citeste)
	void doDelete(void);

	// face o cautare
	void doSearch(void);

	// afiseaza continutul listei (marca, model, numar)
	void doShowContent(void);
	
	// intarziere de 3 secunde
	void delay(void);

	// resetare la starea initiala (setari de constructor)
	void reset(void);

	//afisare informatii in coltul consolei
	void showCornerMessage(uint page);
	
	// afiseaza meniul cu ierarhia de clase
	void showSecondMenu(void);

	// afiseaza meniul principal cu optiunile
	void showMainMenu(void);


	// afiseaza un meniu de citire a unui nume de fisier
	char* showFileNameOption(char *title, char *message);
public:
	Meniu(void);

	// afiseaza meniul
	void show(void);
};
#include "FileWork.h"
#include "Meniu.h"
#include "Util.h"
#include "DefinedCodes.h"
#include "HierarchyHeaders.h"
#include <Windows.h>
#include "Factory.h"

Meniu::Meniu(void)
{
	savedToFile = false;
	option = 0;
	vehicul = nullptr;
	list = new LinkedList;
}

void Meniu::delay()
{
	cout << enter << "\t\tIncarcare, va rugam asteptati";
	for (int i = 3; i > 0; --i)
	{
		Sleep(1000);
		cout << ".";
	}
	Sleep(1000);
	cout << enter;
}

uint Meniu::mainMenuMessages(void)
{
	system("cls");
	showCornerMessage(_FirstPage_);
	cout << enter << enter;
	cout << "\t\tM E N I U" << enter << enter;
	cout << "\t1. Inserare" << enter;
	cout << "\t2. Stergere" << enter;
	cout << "\t3. Cautare" << enter;
	cout << "\t4. Serializare (scriere)" << enter;
	cout << "\t5. Deserializare (citire)" << enter;
	cout << "\t6. Afisare (marca, model, numar)" << enter;
	cout << "\t0. Iesire" << enter << enter;
	uint op = Util::read<uint>(cin, "\t?: ");
	while (op < 0 || op > 6)
		op = Util::read<uint>(cin, "\t?: ");
	return op;
}

uint Meniu::secondMenuMessages(void)
{
	system("cls");
	showCornerMessage(_SecondPage_); // adica 2
	cout << enter << enter;
	cout << "\t\tIERARHIE CLASE" << enter << enter;
	cout << "\t1. AutoVehicul  (nivel 1)" << enter;
	cout << "\t2. AutoMarfar   (nivel 2)" << enter;
	cout << "\t3. AutoPersonal (nivel 2)" << enter;
	cout << "\t4. AutoMobil    (nivel 3)" << enter;
	cout << "\t5. Inapoi" << enter << enter;
	uint op = Util::read<uint>(cin, "\t?: ");
	while (op < 1 || op > 5)
		op = Util::read<uint>(cin, "\t?: ");
	return op;
}

void Meniu::insertMessages(uint op)
{
	system("cls");
	cout << enter << enter;
	if (op == 1)	 cout << "\t\tCITIRE AutoVehicul";
	else if (op == 2) cout << "\t\tCITIRE AutoMarfar";
	else if (op == 3) cout << "\t\tCIIRE AutoPersonal";
	else if (op == 4) cout << "\t\tCITIRE AutoMobil";
	cout << enter << enter;
}

void Meniu::doSerializeAutomatically(void)
{
	cout << enter << "\t\tSalvare automata in \"MemoryContent.txt\"";
	delay();
	FileWork::serialize("MemoryContent.txt", list);
	cout << "\t\tSerializare reusita!" << enter;
	Util::openFile("MemoryContent.txt");
}

void Meniu::doSerializeOnRequest()
{
	char *fileName = showFileNameOption("\t\tCITIRE NUME FISIER SERIALIZARE", "\tNumeFisier: ");
	FileWork::serialize(fileName, list);
	cout << "\t\tSerializare reusita!" << enter;
	savedToFile = true;
}

void Meniu::doDeserialize(void)
{
	char *fileName = showFileNameOption("\t\tCITIRE NUME FISIER DESERIALIZARE", "\tNumeFisier: ");
	list = FileWork::deserialize(fileName);
	savedToFile = false;
	cout << enter << "\t\tDeserializare reusita!" << enter;
	delay();
}

void Meniu::doInsert(void)
{
	vehicul->read(cin, true);
	list->addBack(vehicul);
	savedToFile = false;
	reset();
}

void Meniu::doDelete(void)
{
	char *numar = showFileNameOption("\t\tCITIRE NUMAR PENTRU STERGERE", "\tNumar: ");
	cout << enter << tab << tab;
	if (list->remove(numar))
		cout << "Autovehiculul cu numarul \"" << numar << "\" a fost sters cu succes!";
	else
		cout << "Autovehiculul cu numarul \"" << numar << "\" nu exista!";
	cout << enter << enter << tab;
	cout << "Apasati o tasta pentru a reveni la meniul principal...";
	_getch();
}

void Meniu::doSearch(void)
{
	char *numar = showFileNameOption("\t\tCITIRE PENTRU CAUTARE", "\tNumar: ");
	cout << enter << tab << tab;
	if (list->contains(numar) != nullptr)
		cout << "Autovehiculul cu numarul \"" << numar << "\" exista!";
	else
		cout << "Autovehiculul cu numarul \"" << numar << "\" NU exista!";
	cout << enter << enter << tab;
	cout << "Apasati o tasta pentru a reveni la meniul principal...";
	_getch();
}

void Meniu::doShowContent(void)
{
	system("cls");
	cout << enter << enter << tab << tab;
	cout << "\t\tCONTINUT LISTA" << enter << enter;
	list->showContent();
	cout << enter << enter << tab;
	cout << "Apasati o tasta pentru a reveni la meniul principal...";
	_getch();
}

void Meniu::showMainMenu(void)
{
	uint op = mainMenuMessages();
	if(op < 4)
		option = option * 10 + op;
	switch (op)
	{
	case 1: // inserare
		showSecondMenu();
		return;
	case 2: // stergere
		doDelete();
		break;
	case 3: // cautare
		doSearch();
		break;
	case 4:
		doSerializeOnRequest();
		break;
	case 5:
		doDeserialize();
		break;
	case 6:
		doShowContent();
		break;
	case 0:
		if (!savedToFile && list->getSize() > 0)
			doSerializeAutomatically();
		return;
		break;
	}
	system("cls");
	cout << enter << enter;
	showMainMenu();
}

void Meniu::showSecondMenu(void)
{
	uint op = secondMenuMessages();
	if (op == 5)
	{
		option /= 10;
		showMainMenu();
		return;
	}
	vehicul = Factory::getObject(op);
	insertMessages(op);
	doInsert();
	/*switch (option)
	{
	case 1: // Inserare
		insertMessages(op);
		doInsert();
		break;
	case 2: // Stergere
		doDelete();
		break;
	case 3: // Cautare
		doSearch();
		break;
	}*/
}

char* Meniu::showFileNameOption(char *title, char *message)
{
	system("cls");
	cout << enter << enter << title << enter << enter;
	char *fileName = Util::read<char*>(cin, message);
	return fileName;
}

void Meniu::showCornerMessage(uint page)
{
	if (page == _FirstPage_)
		cout << "1|2 >>> Meniu Principal";
	else if(page == _SecondPage_)
	{
		cout << "2|2 >>> ";
		if(option == 1)
			cout << "Inserare";
		else if(option == 2)
			cout << "Stergere";
		else if(option == 3)
			cout << "Cautare";
		else if(option == 4)
			cout << "Serializare";
		else if(option == 5)
			cout << "Deserializare";	
	}
	cout << enter;
}

void Meniu::reset(void)
{
	option = 0;
	savedToFile = false;
	showMainMenu();
}

void Meniu::show(void)
{
	showMainMenu();
}
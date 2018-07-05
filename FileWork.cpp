#include "Factory.h"
#include "FileWork.h"
#include "Vehicul.h"
#include "LinkedList.h"

void FileWork::serialize(char *outputFile, LinkedList *list)
{
	if (list->getSize() > 0)
	{
		ofstream fout(outputFile);
		LinkedList::myIterator it;
		for (it = list->begin(); it != list->end(); ++it)
			(*it)->write(fout, true, true, true);
		fout.close();
	}
}

LinkedList* FileWork::deserialize(char *inputFile)
{
	LinkedList *list = new LinkedList();
	ifstream fin(inputFile);
	uint codObiect;
	while (fin >> codObiect)
	{
		Vehicul *v = Factory::getObject(codObiect);
		if (v->read(fin, true))
			list->addBack(v);
	}
	fin.close();
	return list;
}
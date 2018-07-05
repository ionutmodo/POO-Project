#pragma once

#include <fstream>
#include "Stack.h"
#include "Vehicul.h"
#include "LinkedList.h"

using namespace std;

class FileWork
{
public:
	static void serialize(char *outputFile, LinkedList *list);
	static LinkedList* deserialize(char *inputFile);
};
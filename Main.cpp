#include <conio.h>
#include "Util.h"
#include "Meniu.h"
using namespace std;

int main()
{
	Meniu meniu;
	meniu.show();
	delete Logger::client();
	Util::openFile("Events.log");
	return 0;
}

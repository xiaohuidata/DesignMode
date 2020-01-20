#include "Waitress.h"

int main(int argc, char* argv[])
{
	PancakeHouseMenu pancakeHouseMenu;
	DinerMenu dinerMenu;
	Waitress waiterss(pancakeHouseMenu, dinerMenu);
	waiterss.printMenu();
	return 0;
}
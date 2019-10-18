#include <iostream>
#include "CaffeineBeverage.h"
#include "CaffeineBeverageWithHook.h"
using namespace std;

int main(int argc, char*argv[])
{
	Tea * myTea = new Tea();
	myTea->preparerecipe();
 
	cout << endl;
	
	TeaWithHook *teaHook = new TeaWithHook();
	CoffeeWithHook  *coffeeHook = new CoffeeWithHook();

	cout << "Making tea..." << endl;
	teaHook->preparerecipe();

	cout << "Making coffee..." << endl;
	coffeeHook->preparerecipe();
	return 0;
}
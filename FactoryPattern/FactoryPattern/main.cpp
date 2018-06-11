#include <iostream>

#include "AbstractFactory.h"

using namespace std;

int main(int argc, char *argv[])
{
	NYPizzaStore pizzaStore;
	Pizza * pizza = pizzaStore.CreatePizza("cheese");
	pizza->Prepare();
	pizza->ToString();

	return 0;
}
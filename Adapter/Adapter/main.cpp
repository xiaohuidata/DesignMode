#include <iostream>
#include "ObjectAdapter.h"
#include "ClassAdapter.h"

void TestDuck(Duck* duck)
{
	duck->quack();
	duck->fly();
}

int main(int argc, char* argv[])
{
	Duck* duck = new MallardDuck();
	Turkey* turkey = new WildTurkey();
	Duck* turkeyAdapter = new TurkeyAdapter(turkey);

	std::cout << "The Turkey says..." << std::endl;
	turkey->gobble();
	turkey->fly();

	std::cout << "The Duck says..." << std::endl;
	TestDuck(duck);

	std::cout << "The TurkeyAdapter says..." << std::endl;
	TestDuck(turkeyAdapter);

	Duck* classdocker = new ClassAdapter();
	std::cout << "The Class Adapter says..." << std::endl;
	TestDuck(classdocker);

	return 0;
}
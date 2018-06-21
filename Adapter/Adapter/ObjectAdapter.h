#pragma once
#include "Duck.h"

class TurkeyAdapter : public Duck
{
	Turkey* turkey;
public:
	TurkeyAdapter(Turkey* turkey) {
		this->turkey = turkey;
	}

	void quack()
	{
		turkey->gobble();
	}

	void fly()
	{
		for (int i = 0; i < 5; i++)
		{
			turkey->fly();
		}
	}
};
#pragma once
#include "Duck.h"

class ClassAdapter :public Duck, WildTurkey
{
public:

	void quack()
	{
		WildTurkey::gobble();
	}

	void fly()
	{
		for (int i = 0; i < 5; i++)
		{
			WildTurkey::fly();
		}
	}
};
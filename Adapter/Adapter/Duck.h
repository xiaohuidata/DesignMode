#pragma once

#include <iostream>

class Duck
{
public:
	virtual void quack() = 0;
	virtual void fly() = 0;
};

class MallardDuck :public Duck
{
public:
	void quack()
	{
		std::cout << "Quack" << std::endl;
	}
	void fly()
	{
		std::cout << "I'm flying" << std::endl;
	}
};

class Turkey
{
public:
	virtual void gobble() = 0;
	virtual void fly() = 0;
};

class WildTurkey : public Turkey
{
public:
	void gobble()
	{
		std::cout << "Gobble gobble" << std::endl;
	}
	void fly()
	{
		std::cout << "I'm flying a short distance" << std::endl;
	}
};
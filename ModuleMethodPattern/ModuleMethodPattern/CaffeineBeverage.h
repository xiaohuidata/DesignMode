#pragma once
#include <iostream>

class CaffeineBeberage{
public:
	void preparerecipe(){
		boilWater();
		brew();
		pourInCup();
		addCondiments();
	}

	virtual void brew() = 0;
	virtual void addCondiments() = 0;

	void boilWater(){
		std::cout << "Boiling water" << std::endl;
	}

	void pourInCup(){
		std::cout << "Rouring into cup" << std::endl;
	}
};

class Tea : public CaffeineBeberage{
public:
	void brew(){
		std::cout << "Steeping the tea" << std::endl;
	}
	void addCondiments(){
		std::cout << "Adding Lemon" << std::endl;
	}
};

class Coffee : public CaffeineBeberage{
public:
	void brew(){
		std::cout << "Dripping Coffee through filter" << std::endl;
	}
	void addCondiments(){
		std::cout << "Adding Sugar and Milk" << std::endl;
	}
};
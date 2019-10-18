#pragma once
#include <iostream>
#include <string>

class CaffeineBeberageWithHook{
public:
	void preparerecipe(){
		boilWater();
		brew();
		pourInCup();
		if (customerWantsCondiments()){
			addCondiments();
		}
	}

	virtual void brew() = 0;
	virtual void addCondiments() = 0;

	void boilWater(){
		std::cout << "Boiling water" << std::endl;
	}

	void pourInCup(){
		std::cout << "Rouring into cup" << std::endl;
	}

	virtual bool customerWantsCondiments(){
		return true;
	}
};

class TeaWithHook : public CaffeineBeberageWithHook{
public:
	void brew(){
		std::cout << "Steeping the tea" << std::endl;
	}
	void addCondiments(){
		std::cout << "Adding Lemon" << std::endl;
	}
};

class CoffeeWithHook : public CaffeineBeberageWithHook{
public:
	void brew(){
		std::cout << "Dripping Coffee through filter" << std::endl;
	}
	void addCondiments(){
		std::cout << "Adding Sugar and Milk" << std::endl;
	}

	bool customerWantsCondiments(){
		std::string answer = getUserInput();
		if (answer[0] == 'y'){
			return true;
		}
		else {
			return false;
		}
	}

	std::string getUserInput(){
		std::string answer;
		std::cout << "Wold you like milk and sugar whith your coffee (y/n)£¿" << std::endl;
		std::cin >> answer;
		return answer;
	}
};
#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include <string>
#include <iostream>
class MenuItem
{
public:
	MenuItem()
	{}
	MenuItem(std::string name, std::string description, bool vegetarian, double price)
		: name(name), description(description), vegetarian(vegetarian), price(price)
	{}

	std::string getName()
	{
		return name;
	}

	std::string getDescription()
	{
		return description;
	}

	double getPrice()
	{
		return price;
	}

	bool isVegetarian()
	{
		return vegetarian;
	}

	const static int MAX_ITEMS = 6;
private:
	std::string name;
	std::string description;
	bool vegetarian;
	double price;
};
#endif
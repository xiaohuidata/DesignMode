#pragma once
/*
#ifndef WAITERSS_H
#define WAITERSS_H
#endif
*/

#include "DinerMenu.h"
#include "PancakeHouseMenu.h"
#include <iostream>

class Waitress
{
public:
	Waitress(PancakeHouseMenu pancakeHouseMenu, DinerMenu dinerMenu) : pancakeHouseMenu(pancakeHouseMenu), dinerMenu(dinerMenu)
	{}
	void printMenu()
	{
		Iterator *pancakerIterator = pancakeHouseMenu.createIterator();
		Iterator *dinerIterator = dinerMenu.createIterator();
		std::cout << "MENU\n----\nBREAKFAST" << std::endl;
		printMenu(pancakerIterator);
		std::cout << "\nLUNCH" << std::endl;
		printMenu(dinerIterator);
		delete pancakerIterator;
		delete dinerIterator;
	}

	void printMenu(Iterator* it)
	{
		while (it->hasNext())
		{
			MenuItem menuIterm = (MenuItem)it->next();
			std::cout << menuIterm.getName() << ","
				<< menuIterm.getPrice() << " -- "
				<< menuIterm.getDescription() << std::endl;
		}
	}
private:
	PancakeHouseMenu pancakeHouseMenu;
	DinerMenu dinerMenu;
};
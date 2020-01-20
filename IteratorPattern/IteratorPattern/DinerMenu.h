#pragma once
#include "MenuItem.h"
#include <array>
#include <iostream>
#include "Iterator.h"
#include "DinerMenuIterator.h"

class DinerMenu
{
public:
	DinerMenu()
	{
		addItem("Vegetarian BLT", "(Fakin') Bacon with lettuce & tomato on whole wheat", true, 2.99);
		addItem("BLT", "Bacon with lettuce & tomato on whole wheat", false, 2.99);
		addItem("Soup of the day", "Soup of the day, with a side of potato salad", false, 3.29);
		addItem("Hotdog", "A hot dog, with saurkraut, relish, onions, topped with cheese", false, 3.05);
	}

	void addItem(std::string name, std::string description, bool vegetarian, double price)
	{
		if (numberOfItems >= MenuItem::MAX_ITEMS)
		{
			std::cerr << "Sorry, menu is full! Can't add item to menu" << std::endl;
		}
		else
		{
			MenuItem menuItem(name, description, vegetarian, price);
			menuItems[numberOfItems] = menuItem;
			numberOfItems++;
		}
	}

	std::array<MenuItem, MenuItem::MAX_ITEMS> getMenuItems()
	{
		return menuItems;
	}

	Iterator* createIterator()
	{
		Iterator* p = new DineMenuIterator(menuItems);
		return p;
	}

private:
	
	int numberOfItems = 0;
	std::array<MenuItem, MenuItem::MAX_ITEMS> menuItems;
};
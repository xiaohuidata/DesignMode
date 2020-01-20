#pragma once
#include "MenuItem.h"
#include "Iterator.h"
#include "PancakeHouseMenuIterator.h"
#include <vector>

class PancakeHouseMenu
{
public:
	PancakeHouseMenu()
	{
		addItem("K&B's, Pancake Breakfast", "Pancakes with scrambled eggs, and toast", true, 2.99);
		addItem("Regular Pancake Breakfast", "Pancakes with fried eggs, sausage", false, 2.99);
		addItem("Blueberry Pancakes", "Pancakes made with fresh blueberries", true, 3.49);
		addItem("Waffles", "Waffles, with your choice of blueberries or strawberries", true, 3.59);
	}

	void addItem(std::string name, std::string description, bool vegetarian, double price)
	{
		MenuItem menuItem(name, description, vegetarian, price);
		menuItems.push_back(menuItem);
	}

	std::vector<MenuItem> getMenuItems()
	{
		return menuItems;
	}

	Iterator* createIterator()
	{
		Iterator* p = new PancakeHouseMenuIterator(menuItems);
		return p;
	}

private:
	std::vector<MenuItem> menuItems;
};
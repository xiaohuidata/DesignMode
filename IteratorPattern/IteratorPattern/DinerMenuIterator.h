#pragma once

#include"Iterator.h"
#include "MenuItem.h"
#include <array>


class DineMenuIterator : public Iterator
{
public:
	DineMenuIterator(std::array<MenuItem, MenuItem::MAX_ITEMS> items) :items(items)
	{
	}

	MenuItem next()
	{
		MenuItem menuitem = items[position];
		position = position + 1;
		return menuitem;
	}

	bool hasNext()
	{
		if (position >= items.size() || items.empty() || items.at(position).getDescription().empty())
		{
			return false;
		}
		else
		{
			return true;
		}
	}

private:
	std::array<MenuItem, MenuItem::MAX_ITEMS> items;
	unsigned int position = 0;
};
#pragma once

#include "Iterator.h"
#include <vector>

class PancakeHouseMenuIterator : public Iterator
{
public:
	PancakeHouseMenuIterator(std::vector<MenuItem> items) : items(items)
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
		if (position >= items.size() || items.empty())
		{
			return false;
		}
		else
		{
			return true;
		}
	}
private:
	std::vector<MenuItem> items;
	unsigned int position = 0;
};
#include "Container.h"

Container::~Container() {}

void Container::Reorder()
{
	if (reorderMethod)
	{
		for (unsigned i = 1; i < children.size(); ++i)
		{
			auto temp = children[i];
			int j = i - 1;
			while (j >= 0 && reorderMethod(children[j], temp))
			{
				children[j + 1] = children[j];
				--j;
			}
			children[j + 1] = temp;
		}
	}
}

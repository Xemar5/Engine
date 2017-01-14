#include "Container.h"
#include "State.h"

Container::~Container() {}

void Container::Add(std::shared_ptr<Body> ent)
{
	ent->parent = std::dynamic_pointer_cast<Container>(this->shared_from_this());
	children.push_back(ent);
}

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

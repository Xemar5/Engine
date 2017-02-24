#include "Container.h"
#include "State.h"

Container::~Container() {}

void Container::Destroy()
{
	for (auto child : children)
		child->Destroy();
	children.clear();
	Object::Destroy();
}

void Container::AddChild(std::shared_ptr<Object> ent)
{
	ent->parent = std::dynamic_pointer_cast<Container>(this->shared_from_this());
	children.push_back(ent);
	sorted_children.push_back(ent);
}

void Container::RemoveChild(std::shared_ptr<Object> obj)
{
	for (auto o = children.begin(); o != children.end(); ++o)
		if (*o == obj) { children.erase(o); break; }
	for (auto o = sorted_children.begin(); o != sorted_children.end(); ++o)
		if (*o == obj) { sorted_children.erase(o); break; }
	obj->parent = nullptr;
}

void Container::Reorder()
{
	if (reorderMethod)
	{
		for (unsigned i = 1; i < sorted_children.size(); ++i)
		{
			auto temp = sorted_children[i];
			int j = i - 1;
			while (j >= 0 && reorderMethod(sorted_children[j], temp))
			{
				sorted_children[j + 1] = sorted_children[j];
				--j;
			}
			sorted_children[j + 1] = temp;
		}
	}
}

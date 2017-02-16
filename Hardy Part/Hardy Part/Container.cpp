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
}

void Container::RemoveChild(std::shared_ptr<Object> obj)
{
	for (auto o = children.begin(); o != children.end(); ++o)
		if (*o == obj) { children.erase(o); break; }
	obj->parent = nullptr;
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

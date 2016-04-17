#include "Hitbox.h"
#include "Entity.h"


std::shared_ptr<Hitbox> Hitbox::Set(Entity* ent, unsigned width, unsigned height)
{
	if (!ent)
	{
		std::cout << "MSG Hitbox::Set : No entity supplied; returning pointer\n";
	}
	std::shared_ptr<Hitbox> h = std::make_shared<Hitbox>();
	h->__Width = width;
	h->__Height = height;
	if (ent) ent->__Hitbox = h;
	return h;
}

bool Hitbox::__Colision_Response()
{
	return false;
}

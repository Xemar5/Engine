#include <vector>
#include <memory>
#include "Object.h"
#include "Entity.h"
#include "Container.h"
#include "Camera.h"
#include "Screen.h"


std::shared_ptr<Object> Object::last_object = nullptr;

void Object::Destroy()
{
	if (is_destroyed) return;
	is_destroyed = true;
	std::cout << "before: " << this->shared_from_this().use_count() << std::endl;
	if (parent) parent->RemoveChild(this->shared_from_this());
	std::cout << "after: " << this->shared_from_this().use_count() << std::endl;
}

double Object::RootScale()
{
	std::shared_ptr<Object> p = std::dynamic_pointer_cast<Object>(parent);
	return scale * (p ? p->RootScale() : Camera::Main->scale);
}

std::vector<double> Object::RootPos()
{
	std::vector<double> v(3);
	std::shared_ptr<Object> p = std::dynamic_pointer_cast<Object>(parent);
	if (p) v = p->RootPos();
	v[0] += parent ? parent->Child_X(X) : 0;
	v[1] += parent ? parent->Child_Y(Y) : 0;
	v[2] += Z;
	return v;
}

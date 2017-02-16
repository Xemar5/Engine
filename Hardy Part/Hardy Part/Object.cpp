#include <vector>
#include <memory>
#include "Object.h"
#include "Entity.h"
#include "Container.h"
#include "Camera.h"
#include "Screen.h"


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
	v[0] += parent ? parent->Child_X(X) : Camera::Main->X;
	v[1] += parent ? parent->Child_Y(Y) : Camera::Main->Y;
	v[2] += Z;
	return v;
}

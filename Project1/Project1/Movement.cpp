#include "Movement.h"
#include "Entity.h"

template <typename T> int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}

std::shared_ptr<Movement> Movement::Set(double & x, double & y, int mass)
{
	if (mass < -1)
	{
		std::cout << "ERR Movement::Create : Given mass can't be less than -1\n";
		return nullptr;
	}
	std::shared_ptr<Movement> m = std::make_shared<Movement>();
	m->__X = &x;
	m->__Y = &y;
	m->__Mass = mass;
	return m;
}

std::shared_ptr<Movement> Movement::Set(Entity * ent, int mass)
{
	if (!ent)
	{
		std::cerr << "ERR Movement::Set : No entity supplied; use the other Movement::Set if only object needed\n";
		return nullptr;
	}
	ent->__Movement = Movement::Set(ent->X, ent->Y, mass);
	return ent->__Movement;
}

bool Movement::Move(Movement * movement, double force_x, double force_y, double traction)
{
	if (!movement)
	{
		std::cerr << "ERR Movement::Set : No Movement Supplied\n";
		return false;
	}
	if (traction > 1 || traction < 0)
	{
		std::cerr << "ERR Movement::Set : Unsupported traction values\n";
		return false;
	}
	if (movement->__Mass == -1) return true;
	if (traction == 0) return true;

	auto acc = movement->__Mass * 0.1 * traction;
	movement->__vx += acc * sgn(force_x - movement->__vx);
	movement->__vy += acc * sgn(force_y - movement->__vy);
	if (abs(force_x - movement->__vx) < acc) movement->__vx = force_x;
	if (abs(force_y - movement->__vy) < acc) movement->__vy = force_y;

	*movement->__X += movement->__vx;
	*movement->__Y += movement->__vy;
	return true;
}

bool Movement::Move(Entity * ent, double force_x, double force_y, double traction)
{
	if (!ent)
	{
		std::cerr << "ERR Movement::Move : No entity supplied; use the other Movement::Move function instead\n";
		return false;
	}
	if (!ent->Get_Movement())
	{
		std::cerr << "ERR Movement::Move : Given entity has no Movement\n";
		return false;
	}
	Movement::Move(ent->Get_Movement(), force_x, force_y, traction);
	return true;
}

double Movement::Get_Velocity_X()
{
	return __vx;
}

double Movement::Get_Velocity_Y()
{
	return __vy;
}

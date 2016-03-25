#include "Movement.h"
#include "Entity.h"

template <typename T> int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}

std::shared_ptr<Movement> Movement::Set(double & x, double & y, double speed, int mass)
{
	if (mass < -1)
	{
		std::cout << "ERR Movement::Create : Given mass can't be less than -1\n";
		return nullptr;
	}
	std::shared_ptr<Movement> m = std::make_shared<Movement>();
	m->__X = &x;
	m->__Y = &y;
	m->__Speed = speed;
	m->__Mass = mass;
	return m;
}


std::shared_ptr<Movement> Movement::Set(Entity * ent, double speed, int mass)
{
	if (!ent)
	{
		std::cerr << "ERR Movement::Set : No entity supplied; use the other Movement::Set if only object needed\n";
		return nullptr;
	}
	return ent->__Movement = Movement::Set(ent->X, ent->Y, speed, mass);
}

bool Movement::Add_Force(Movement * movement, double force_x, double force_y)
{
	if (!movement)
	{
		std::cerr << "ERR Movement::Set : No Movement Supplied\n";
		return false;
	}
	if (movement->__Mass == -1) return true;
	
	double x = cos(atan2(force_y, force_x)) * abs(force_x);
	double y = sin(atan2(force_y, force_x)) * abs(force_y);

	movement->__Forces.push_back(std::make_pair(x, y));
	return true;
}

bool Movement::Add_Force(Entity * ent, double force_x, double force_y)
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
	Movement::Add_Force(ent->Get_Movement(), force_x, force_y);
	return true;
}

double Movement::Get_Speed()
{
	return __Speed;
}

double Movement::Get_Mass()
{
	return __Mass;
}

double Movement::Get_Velocity_X()
{
	return __vx;
}

double Movement::Get_Velocity_Y()
{
	return __vy;
}


bool Movement::__Resolve_Movement(Movement * movement)
{
	if (!movement)
	{
		std::cerr << "ERR Movement::__Resolve_Movement : No Movement supplied\n";
		return false;
	}
	if (!movement->__X || !movement->__Y)
	{
		std::cerr << "ERR Movement::__Resolve_Movement : Given Movement points to no X or Y variables\n";
		return false;
	}

	double fx = 0, fy = 0;
	auto acc = movement->__Mass * 0.1;
	for (unsigned i = 0; i < movement->__Forces.size(); i++)
	{
		fx += movement->__Forces[i].first * movement->Get_Speed();
		fy += movement->__Forces[i].second * movement->Get_Speed();
	}
	movement->__vx += acc * sgn(fx - movement->__vx);
	movement->__vy += acc * sgn(fy - movement->__vy);
	if (abs(fx - movement->__vx) < acc) movement->__vx = fx;
	if (abs(fy - movement->__vy) < acc) movement->__vy = fy;
	*movement->__X += movement->__vx;
	*movement->__Y += movement->__vy;


	movement->__Forces.clear();
	return movement->__vx || movement->__vy;
}

bool Movement::__Resolve_Movement(Entity * ent)
{
	if (!ent)
	{
		std::cerr << "ERR Movement::__Resolve_Movement : No Entity supplied\n";
		return false;
	}
	return Movement::__Resolve_Movement(ent->Get_Movement());
}

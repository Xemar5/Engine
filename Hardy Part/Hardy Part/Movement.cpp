#include "Movement.h"
#include "Entity.h"
#include "Screen.h"
#include "Output_Handler.h"

template <typename T> T sgn(T val) {
	return (T(0) < val) - (val < T(0));
}


std::shared_ptr<Movement> Movement::Set(std::shared_ptr<Entity> ent, double speed, double mass)
{
	if (!ent)
	{
		Output_Handler::Error << "ERR Movement::Change : No entity supplied; use the other Movement::Change if only object needed\n";
		return nullptr;
	}
	if (mass < -1)
	{
		Output_Handler::Output << "ERR Movement::Create : Given mass can't be less than -1\n";
		return nullptr;
	}
	std::shared_ptr<Movement> m = std::make_shared<Movement>();
	m->__this = ent;
	m->speed = speed;
	m->mass = mass;
	return m;
}

bool Movement::Add_Force(std::shared_ptr<Movement> movement, double force_x, double force_y)
{
	if (!movement)
	{
		Output_Handler::Error << "ERR Movement::Change : No Movement Supplied\n";
		return false;
	}
	if (movement->mass == -1) return true;
	
	double x = cos(atan2(force_y, force_x)) * abs(force_x);
	double y = sin(atan2(force_y, force_x)) * abs(force_y);

	movement->__Forces.push_back(std::make_pair(x, y));
	return true;
}

bool Movement::Add_Force(std::shared_ptr<Entity> ent, double force_x, double force_y)
{
	if (!ent)
	{
		Output_Handler::Error << "ERR Movement::Move : No entity supplied; use the other Movement::Move function instead\n";
		return false;
	}
	return Movement::Add_Force(ent->movement, force_x, force_y);
}


double Movement::Get_Velocity_X()
{
	return __vx;
}

double Movement::Get_Velocity_Y()
{
	return __vy;
}


bool Movement::__Resolve_Movement(std::shared_ptr<Movement> movement)
{
	if (!movement)
	{
		Output_Handler::Error << "ERR Movement::__Resolve_Movement : No Movement supplied\n";
		return false;
	}

	double fx = 0, fy = 0;
	auto acc = movement->mass * 0.1;
	for (unsigned i = 0; i < movement->__Forces.size(); i++)
	{
		fx += movement->__Forces[i].first * movement->speed;
		fy += movement->__Forces[i].second * movement->speed;
	}
	movement->__vx += acc * sgn(fx - movement->__vx);
	movement->__vy += acc * sgn(fy - movement->__vy);
	if (abs(fx - movement->__vx) < acc) movement->__vx = fx;
	if (abs(fy - movement->__vy) < acc) movement->__vy = fy;
	movement->__this->X += movement->__vx;
	movement->__this->Y += movement->__vy;

	movement->__Forces.clear();
	return movement->__vx || movement->__vy;
}

bool Movement::__Resolve_Movement(std::shared_ptr<Entity> ent)
{
	if (!ent)
	{
		Output_Handler::Error << "ERR Movement::__Resolve_Movement : No Entity supplied\n";
		return false;
	}
	return Movement::__Resolve_Movement(ent->movement);
}

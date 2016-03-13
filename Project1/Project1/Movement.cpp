#include "Movement.h"

template <typename T> int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}

std::vector<std::shared_ptr<Movement>> Movement::__Movements;

Movement * Movement::Set(double & x, double & y, int mass)
{
	if (mass < -1)
	{
		std::cout << "ERR Movement::Create : Given mass can't be less than -1\n";
		return nullptr;
	}
	Movement::__Movements.emplace_back(std::make_shared<Movement>());
	Movement::__Movements.back()->__X = &x;
	Movement::__Movements.back()->__Y = &y;
	Movement::__Movements.back()->__Mass = mass;
	return Movement::__Movements.back().get();
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

double Movement::Get_Velocity_X()
{
	return __vx;
}

double Movement::Get_Velocity_Y()
{
	return __vy;
}

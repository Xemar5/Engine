#pragma once
#include "Entity.h"
class Player;

class Sword : public EntityObject
{
public:
	std::shared_ptr<Player> Wealder = nullptr;
	void Create() override;
	void Update() override;
	void Events() override;
	double Max_Swing = 270;
	double Swing_Speed = 40;
private:
	double __Old_Angle = 0.0;
	int __On_Left = 1;
	double __Angle_Offset = 0;
	bool __Swinging = false;
};

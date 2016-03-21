#pragma once

#include "Entity.h"

class Man : public Entity
{
public:
	void Create() override;
	void Update() override;
	void Events() override;
};

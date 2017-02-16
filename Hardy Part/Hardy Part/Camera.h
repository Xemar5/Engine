#pragma once

#include "Container.h"

class Camera : public Container
{
public:
	//*** The currently used camera
	//*** All entities are displayed according to this cam position
	static std::shared_ptr<Camera> Main;
private:
};
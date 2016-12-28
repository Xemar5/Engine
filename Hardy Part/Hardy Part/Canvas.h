#pragma once

#include "Layer.h"
class State;

class Canvas : public Layer
{
public:
	Canvas(unsigned w, unsigned h) : width(w), height(h), Layer() {};
	Canvas(unsigned w, unsigned h, Entity<State> parent) : width(w), height(h) { EntityObject::parent = parent; };

	unsigned width;
	unsigned height;

	double Child_X(double x) override { return ((double)width / 2 + x) / (double)width; }
	double Child_Y(double y) override { return ((double)height / 2 + y) / (double)height; }
};

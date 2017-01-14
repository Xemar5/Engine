#pragma once

#include "Layer.h"
class State;

class Canvas : public Layer
{
public:
	Canvas(unsigned w, unsigned h) : width(w), height(h), Layer() {};

	unsigned width;
	unsigned height;

	double Child_X(double x) override { return (x + 1)/2 * (width ? (double)width : Screen::Window_Size().first); }
	double Child_Y(double y) override { return (y + 1)/2 * (height ? (double)height : Screen::Window_Size().second); }
};

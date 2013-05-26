#pragma once

#include <string>
#include "Color.h"

using namespace std;

struct Node {
public:
	Node(int initX, int initY, Color initColor, string initType, bool initFilled) 
	{
		x = initX;
		y = initY;
		color = initColor;
		type = initType;
		filled = initFilled;
	}

	Node()
	{
		x = 0;
		y = 0;

	}

	int getX() { return x; }
	int getY() { return y; }
	Color getColor() { return color; }
	string getType() { return type; }
	bool isFilled() { return filled; }

private:
	int x;
	int y;
	Color color;
	string type;
	bool filled;
};
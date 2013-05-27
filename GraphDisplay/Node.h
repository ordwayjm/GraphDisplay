#pragma once

#include "Color.h"

class Node {
	public:
		Node(int initX, int initY, Color initColor, char initType, bool initFilled) 
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
			type = 's';
			filled = true;
		}

		int getX() { return x; }
		int getY() { return y; }
		Color getColor() { return color; }
		char getType() { return type; }
		bool isFilled() { return filled; }

		void setX(int newX) { x = newX; }
		void setY(int newY) { y = newY; }
		void setColor(Color newColor) { color = newColor; }
		void setType(char newType) { type = newType; }
		void setFilled(bool newFilled) { filled = newFilled; }

	private:
		int x;
		int y;
		Color color;
		char type;
		bool filled;
};
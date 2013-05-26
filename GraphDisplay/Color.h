#pragma once

struct Color {
	public:
		Color(int initR, int initG, int initB)
		{
			r = initR;
			g = initG;
			b = initB;
		}

		Color() 
		{
			r = g = b = 255;
		}

		int getR() const { return r; }
		int getG() const { return g; }
		int getB() const { return b; }

	private:
		int r, g, b;
};
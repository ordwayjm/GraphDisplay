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

		int getR() { return r; }
		int getG() { return g; }
		int getB() { return b; }

		void setColor(int newR, int newG, int newB) { r = newR; g = newG; b = newB; }
		void setR(int newR) { r = newR; }
		void setG(int newG) { g = newG; }
		void setB(int newB) { b = newB; }

	private:
		int r;
		int g;
		int b;
};
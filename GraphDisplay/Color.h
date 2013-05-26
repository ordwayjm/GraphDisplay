#include <cstdio>
using namespace std;

struct Color {
	public:
		Color(int initR, int initG, int initB)
		{
			r = initR;
			g = initG;
			b = initB;
		}

		int getR() const { return r; }
		int getG() const { return g; }
		int getB() const { return b; }

	private:
		int r, g, b;
};
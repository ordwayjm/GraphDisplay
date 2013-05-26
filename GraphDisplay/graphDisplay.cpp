#include <iostream>
#include <fstream>
#include <string>
#include "Color.h"
using namespace std;

#include <GL/freeglut.h>

const int W = 800, H = 400;
const int nodeWidth = 10;


void setClippingRectangle(double lx, double ly,
						  double rx, double ry)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();				
	gluOrtho2D(lx, rx, ly, ry);
}

void setViewport(GLint lx, GLint ly, GLint rx, GLint ry)
{
	glViewport(lx, ly, rx-lx+1, ry-ly+1);
}

void reshape(int w, int h)
{
	if (w <= 0 || h <= 0) return;

	setViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

	double wcH = 1;
	double wcW = 2;
	double wcAR = wcW / wcH;
	double vpAR = (double)w/h;
	double newWcWidth, newWcHeight;
	const double pixelsPerWC = 1;
	if (vpAR > wcAR) {
		newWcHeight = h / pixelsPerWC;
		newWcWidth = vpAR * newWcHeight;
	} 
	else {
		newWcWidth = w / pixelsPerWC;
		newWcHeight = newWcWidth / vpAR;
	}
	setClippingRectangle(0, 0, newWcWidth-1, newWcHeight-1);

	glutPostRedisplay();
}

// might not be needed
void keyboard(unsigned char key, int x, int y)
{
	key = toupper(key);

	glutPostRedisplay();
}

void square(int x, int y, Color color, bool filled)
{
	GLenum type = GL_LINE_LOOP;
	if(filled) 
		type = GL_POLYGON;
	glColor3ub(color.getR(), color.getG(), color.getB());
	glBegin(type);
		glVertex2i(x - (nodeWidth/2), y - (nodeWidth/2));
		glVertex2i(x - (nodeWidth/2), y + (nodeWidth/2));
		glVertex2i(x + (nodeWidth/2), y + (nodeWidth/2));
		glVertex2i(x + (nodeWidth/2), y - (nodeWidth/2));	
	glEnd();
}

void triangle(int x, int y, Color color, bool filled)
{
	GLenum type = GL_LINE_LOOP;
	if(filled) 
		type = GL_POLYGON;
	glColor3ub(color.getR(), color.getG(), color.getB());
	glBegin(type);
		glVertex2i(x - (nodeWidth/2), y - (nodeWidth/2));
		glVertex2i(x + (nodeWidth/2), y - (nodeWidth/2));	
		glVertex2i(x, y + (nodeWidth/2));	
	glEnd();
}

void display(void)
{
	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	Color color1(255, 0, 0);
	square(100, 150, color1, true);

	glutSwapBuffers();
	glFlush();
}

string getUserInput(string prompt)
{
	string input;
	cout << prompt;
	cin >> input;
	return input;
}

// TODO finish this
bool readFile(string filename)
{
	int nNodes, nEdges;
	ifstream input(filename);
	if(input.is_open())
	{
		input >> nNodes;

		for (int i=0; i<nNodes; i++) {
			string type;
			int r, g, b;
			int x, y;
			input >> type >> r >> g >> b >> x >> y;
			cout << type << "(" << x << "," << y << ")" << endl;
		}

		input >> nEdges;

		for (int i=0; i<nEdges; i++) {
			int n1, n2;
			input >> n1 >> n2;
			cout << "[" << n1 << "," << n2 << "]" << endl;
		}
		input.close();
		return true;
	}
	else {
		cout << "Unable to open file" << endl;
		return false;
	}
	
}

void main(int argc, char *argv[])
{
	// Get filename from user
	string filename;
	cout << "Welcome to the Graph Display program!" << endl;
	while(!readFile(filename))
	{
		filename = getUserInput("Enter the name of the input file: ");
	}

	// OpenGL initialization
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);	
	glutInitWindowSize(W, H);	
	glutCreateWindow("Graph Display");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
}
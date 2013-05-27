#include <iostream>
#include <fstream>
#include <string>
#include "Color.h"
#include "Node.h"
#include "Edge.h"

using namespace std;

#include <GL/freeglut.h>

const int W = 800, H = 400;
const int nodeWidth = 10;

Color edgeColor(255, 255, 255);
Color bgColor(0, 0, 0);

Node* nodes;
Edge* edges;
int numNodes;
int numEdges;

void setClippingRectangle(double lx, double ly, double rx, double ry)
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
	if (vpAR > wcAR)
	{
		newWcHeight = h / pixelsPerWC;
		newWcWidth = vpAR * newWcHeight;
	} 
	else 
	{
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

// TODO add arrow heads, shorten edge to not intersect node
void edge(int x1, int y1, int x2, int y2)
{
	glColor3ub(edgeColor.getR(), edgeColor.getG(), edgeColor.getB());
	glBegin(GL_LINES);
		glVertex2i(x1, y1);
		glVertex2i(x2, y2);	
	glEnd();
}

void display(void)
{
	glClearColor((float)bgColor.getR()/255, (float)bgColor.getG()/255, (float)bgColor.getB()/255, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for(int i = 0; i < numNodes; i++)
	{
		switch(nodes[i].getType()) 
		{
			case 's': 
					square(nodes[i].getX(), nodes[i].getY(), nodes[i].getColor(), nodes[i].isFilled());
					break;
			case 't': 
					triangle(nodes[i].getX(), nodes[i].getY(), nodes[i].getColor(), nodes[i].isFilled());
					break;
		}

	}

	for(int i = 0; i < numEdges; i++)
	{
		edge(edges[i].getNode1().getX(), edges[i].getNode1().getY(), edges[i].getNode2().getX(), edges[i].getNode2().getY());
	}
	
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

bool readFile(string filename)
{
	int nNodes, nEdges;
	ifstream input(filename);
	if(input.is_open())
	{
		input >> nNodes;
		numNodes = nNodes;
		nodes = new Node[numNodes];
		
		string type;
		int r, g, b;
		int x, y;
		Color color;
		bool filled;

		for (int i=0; i<numNodes; i++) 
		{
			input >> type >> r >> g >> b >> x >> y;
			//cout << type << "(" << x << "," << y << ")" << endl;
			
			color.setColor(r, g, b);

			if(type.at(0) == 'f')
				filled = true;
			else filled = false;

			nodes[i].setX(x);
			nodes[i].setY(y);
			nodes[i].setColor(color);
			nodes[i].setType(type.at(1));
			nodes[i].setFilled(filled);
		}

		input >> nEdges;
		numEdges = nEdges;
		edges = new Edge[numEdges];

		int n1, n2;
		for (int i=0; i<numEdges; i++) 
		{
			input >> n1 >> n2;

			edges[i].setNode1(nodes[n1]);
			edges[i].setNode2(nodes[n2]);

			//cout << "[" << n1 << "," << n2 << "]" << endl;
		}
		input.close();
		return true;
	}
	else 
	{
		cout << "Unable to open file" << endl;
		return false;
	}
}

void main(int argc, char *argv[])
{
	// Get filename from user
	string filename;
	cout << "Welcome to the Graph Display program!" << endl;
	do
	{
		filename = getUserInput("Enter the name of the input file: ");
	} 
	while(!readFile(filename));

	cout << "Drawing graph..." << endl;
	
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
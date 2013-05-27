#pragma once

#include "Node.h"

class Edge {
	public:
		Edge(Node initNode1, Node initNode2) 
		{
			node1 = initNode1;
			node2 = initNode2;
		}

		Edge() 
		{
			node1 = Node();
			node2 = Node();
		}

		Node getNode1() { return node1; }
		Node getNode2() { return node2; }

		void setNode1(Node newNode1) { node1 = newNode1; }
		void setNode2(Node newNode2) { node2 = newNode2; }
	private:
		Node node1;
		Node node2;
};
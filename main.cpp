#include <iostream>
#include <utility>
#include "grid.h"
#include "tree.hpp"
#include "ids.hpp"
#include "tzfe.cpp"
using namespace std;

int main()
{
	ofstream test;
	test.open( "test.txt" );

	Grid *g = new Grid();
	g->print();

	// cout << "making root node" << endl;

	// tree_node *t = new tree_node( g );
	// pair<int,char> move = chooseMove( t, t->root()->iteration, test );
	// cout << "choose direction " << move.second << endl;
	// cout << "max direction value " << move.first << endl;

	// return 0;

	tree_node *n = new tree_node(g);
	int i = 0;
	//ofstream &out;
	while (!(g->maxVal() != 2048)) {
		pair<int,char> c = chooseMove(n, i, test);
		if (c.first == 0) break;
		if (c.second == ('u')) g->moveUp();
		else if (c.second == ('l')) g->moveLeft();
		else if (c.second ==('d')) g->moveDown();
		else if (c.second ==('r')) g->moveRight();
		n = new tree_node(g);
		//print();
		i++;
	}
if (g->maxVal() == 2048)
	cout << "winner winner chicken dinner" << endl;
else
	cout << "you failed, badly"<< endl;
}

#include <iostream>
#include "grid.h"
#include "tree.hpp"
#include "ids.hpp"
using namespace std;

int main()
{
	ofstream test;
	test.open( "test.txt" );

	Grid *g = new Grid();
	g->print();

	cout << "making root node" << endl;

	tree_node *t = new tree_node( g );
	pair<int,char> move = chooseMove( t, t->root()->iteration, test );
	cout << "choose direction " << move.second << endl;
	cout << "max direction value " << move.first << endl;

	return 0;
}

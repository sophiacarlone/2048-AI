#include <iostream>
#include <utility>
#include "grid.h"
#include "tree.hpp"
#include "ids.hpp"
using namespace std;

int main()
{
	srand(time(NULL));

	ofstream output;
	output.open( "ai.output" );
	ofstream print;
	print.open( "tzfe.csv" );

	Grid *g = new Grid();
	g->print_to_stream( output );

	// cout << "making root node" << endl;

	// tree_node *t = new tree_node( g );
	// pair<int,char> move = chooseMove( t, t->root()->iteration, test );
	// cout << "choose direction " << move.second << endl;
	// cout << "max direction value " << move.first << endl;

	// return 0;

	tree_node *n = new tree_node(g);
	//ofstream &out;
	while (g->maxVal() != 2048) {

		pair<double,char> c = chooseMove(n, g->iteration, output);
		if (c.first == 0){
			cout << "you balloooon"  << endl;
			break;
		} 

		if (c.second == ('u')) g = g->moveUp();
		else if (c.second == ('l')) g = g->moveLeft();
		else if (c.second ==('d')) g = g->moveDown();
		else if (c.second ==('r')) g = g->moveRight();
		if ( g == NULL ){
			cout << "you baffooon"  << endl;
			break;
		}

		g->addBlock();

		print << c.second << "," << c.first << endl;
		output << g->dir << " " << g->maxVal() << endl;
		cout << g->dir << " " << g->maxVal() << endl;
		g->print_to_stream( output );
		cout << "move # " << g->iteration/2 << endl;
		g->print();

		n = new tree_node(g);
	}
	if (g->maxVal() == 2048)
		cout << "winner winner chicken dinner" << endl;
	else
		cout << "you failed, badly"<< endl;
}

#include <iostream>
#include "grid.h"
using namespace std;

int main()
{
	ofstream test;
	test.open( "test.txt" );

	Grid g;
	g.print();

	g = g.moveLeft();
	cout << "moving left..." << endl;
	g.print();
	g.print_to_stream( test );

	g = g.moveUp();
	cout << "moving up..." << endl;
	g.print();
	g.print_to_stream( test );

	g = g.moveRight();
	cout << "moving right..." << endl;
	g.print();
	g.print_to_stream( test );

	g = g.moveDown();
	cout << "moving down..." << endl;
	g.print();
	g.print_to_stream( test );

	return 0;
}

#include <iostream>
#include "grid.h"
using namespace std;

int main()
{
	Grid g;
	g.print();
	g.moveLeft();
	cout << "moving left..." << endl;
	g.print();
	g.moveUp();
	cout << "moving up..." << endl;
	g.print();
	g.moveRight();
	cout << "moving right..." << endl;
	g.print();
	g.moveDown();
	cout << "moving down..." << endl;
	g.print();

	return 0;
}

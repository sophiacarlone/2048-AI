#ifndef GRID_H
#define GRID_H

#include <fstream>

class Block
{
	public:
	// integer value of block
	int num;
	// for move functions
	bool isEmpty, notCombined;

	// constructors
	Block();
	Block( int );
	Block( int, bool );
	Block( const Block&, int );

	// getters and setters
	void remove();
};

class Grid
{
	public:
	// array of blocks
	Block blocks[16];
	// score of game
	int score;

	// constructors
	Grid();
	Grid( const Grid& );
	
	// helper functions
	void addBlock( char );
	void makeAllCombinable();

	// move functions
	bool moveLeft();
	bool moveRight();
	bool moveUp();
	bool moveDown();

	// print function
	void print_to_stream( std::ostream & );
	void print();
};

#endif

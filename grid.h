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

	// equal function
	friend bool operator==( Block const&, Block const& );
	friend bool operator!=( Block const&, Block const& );
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
	Grid moveLeft();
	Grid moveRight();
	Grid moveUp();
	Grid moveDown();

	// value for IDS
	int value();

	// print function
	void print_to_stream( std::ostream & );
	void print();

	// equal function
	friend bool operator==( Grid const&, Grid const& );
	friend bool operator!=( Gird const&, Grid const& );

	// comparison functions
	friend bool operator>( Grid const&, Grid const& );
	friend bool operator<( Grid const&, Grid const& );
};

#endif

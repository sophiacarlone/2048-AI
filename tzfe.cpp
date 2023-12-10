#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include "grid.h"
using namespace std;

#define swap(a,b) ((a) ^= (b), (b) ^= (a), (a) ^= (b))

bool gridMoveable( Grid *, char );

//////// BLOCK FUNCTIONS ////////////
/* default constructor */
Block::Block()
{
	num = 0;
	isEmpty = true;
	notCombined = true;
}

/* constructor for specifying num */
Block::Block( int NUM )
{
	num = NUM;
	isEmpty = false;
	notCombined = true;
}

/* constructor for combined blocks */
Block::Block( int NUM, bool COMBINED )
{
	num = NUM;
	isEmpty = false;
	notCombined = COMBINED;
}

Block::Block( const Block &b, int NUM )
{
	num = NUM;
	isEmpty = false;
	notCombined = b.notCombined;
}

/* removes numbered block from grid */
void Block::remove()
{
	num = 0;
	isEmpty = true;
}

/* equality operator */
bool operator==( Block const &b1, Block const &b2 )
{
	return b1.num == b2.num ? true : false;
}

bool operator!=( Block const &b1, Block const &b2 )
{
	return b1.num != b2.num ? true : false;
}

////////// GRID FUNCTIONS //////////////
/* default constructor */
Grid::Grid()
{
	//srand(time(NULL));
	for ( int i = 0; i < 16; i++ )
		blocks[i] = Block();

	// two blocks start as 2
	int i = rand() % 16,j = rand() % 16;
	while ( i == j )
		j = rand() % 16;
	blocks[i] = Block( 2 );
	blocks[j] = Block( 2 );

	score = 0;
	iteration = 0;
	notMoved = true;
	dir = '\0';
}

/* constructor for new nodes */
Grid::Grid( const Grid &g )
{
	for ( int i = 0; i < 16; i++ )
		blocks[i] = g.blocks[i];
	
	score = g.score;
	iteration = g.iteration;
	notMoved = true;
	dir = g.dir;
}

/* destructor */
Grid::~Grid(){}

/* add a new 2 block to the grid
 * l for left, r for right, u for up, and d for down */
void Grid::addBlock( )
{
	char d = this->dir;

	// check if number has been added
	bool added = false;
	// add in random order
	int loc[4];
	for ( int i = 0; i < 4; i++ )
		loc[i] = i;

	//srand(time(NULL));

	for ( int i = 0; i < 4; i++ )
	{
		int j = rand() % 4; //+i
		swap( loc[j], loc[i] );
	}

	//THIS IS CREATING ARRAYS WITH MULTIPLE INSTANCES OF A NUMBER!!

	cout << "add block" << endl;
	for ( int i = 0; i < 4; i++ ) cout << loc[i] << " ";
    cout << endl;

	if ( d == 'l' )
		for ( int i = 0; i < 4; i++ )
			if ( blocks[loc[i]*4+3].isEmpty )
			{
				blocks[loc[i]*4+3] = Block(2);
				break;
			}
				
	if ( d == 'r' )
		for ( int i = 0; i < 4; i++ )
		{
			if ( blocks[loc[i]*4].isEmpty )
			{
				blocks[loc[i]*4] = Block(2);
				break;
			}
		}
				
	if ( d == 'u' )
		for ( int i = 0; i < 4; i++ )
			if ( blocks[loc[i]+12].isEmpty )
			{
				blocks[loc[i]+12] = Block(2);
				break;
			}
				
	if ( d == 'd' )
		for ( int i = 0; i < 4; i++ )
			if ( blocks[loc[i]].isEmpty )
			{
				blocks[loc[i]] = Block(2);
				break;
			}

	iteration++;
}

/* similar to above, but with a specific index to add to */
Grid *Grid::addBlock( int i )
{
	Grid *g = new Grid( (*this) );
	char d = g->dir;
	g->iteration++;

	if ( d == 'l' )
	{
		if ( blocks[i*4+3].isEmpty )
			g->blocks[i*4+3] = Block( 2 );
		else return NULL;
	}

	if ( d == 'r' )
	{
		if ( blocks[i*4].isEmpty )
			g->blocks[i*4] = Block( 2 );
		else return NULL;
	}

	if ( d == 'u' )
	{
		if ( blocks[i+12].isEmpty )
			g->blocks[i+12] = Block( 2 );
		else return NULL;
	}

	if ( d == 'd' )
	{
		if ( blocks[i].isEmpty )
			g->blocks[i] = Block( 2 );
		else return NULL;
	}

	return g;
}
	

/* makes all blocks in the grid combinable */
void Grid::makeAllCombinable()
{
	for ( int i = 0; i < 15; i++ )
		blocks[i].notCombined = true;
}

/* move blocks left */
Grid *Grid::moveLeft()
{
	makeAllCombinable();
	bool notMoved = true;
	Grid *g = new Grid( (*this) );

	// move blocks from col 2-4
	for ( int i = 1; i < 16; i++ )
	{
		if ( ( i%4 == 0 ) || g->blocks[i].isEmpty )
			continue;

		for ( int j = 1; j < 4; j++ )
		{
			// iterate through blocks within the row
			if ( j <= i % 4 )
			{
				// if block to the left is empty, move it left and delete old block
				if ( g->blocks[i-j].isEmpty )
				{
					g->blocks[i-j] = Block( g->blocks[i-j+1].num );
					g->blocks[i-j+1].remove();
					g->notMoved = false;
				}
				// if block to the left is not empty, check if numbers match and combine
				else if ( ( g->blocks[i-j].num == g->blocks[i-j+1].num ) && g->blocks[i-j].notCombined && g->blocks[i-j+1].notCombined )
				{
					g->blocks[i-j] = Block( g->blocks[i-j+1].num * 2, false );
					g->score += blocks[i-j].num;
					g->blocks[i-j+1].remove();
					g->notMoved = false;
				}
				else break;
			}
		}
	}
	// check if grid has moved and returns null if not
	if ( g->notMoved ) 
		return NULL;
	// increase iteration and return new grid object
	g->iteration++;
	g->dir = 'l';
	return g;
}

/* move blocks right */
Grid *Grid::moveRight()
{
	makeAllCombinable();
	bool notMoved = true;
	Grid *g = new Grid( (*this) );

	// move blocks from col 3-1
	for ( int i = 14; i > -1; i-- )
	{
		if ( ( i%4 == 3 ) || g->blocks[i].isEmpty )
			continue;

		for ( int j = 1; j < 4; j++ )
		{
			// iterate through blocks within the row
			if ( (4-j) > i % 4 )
			{
				// if block to the left is empty, move it left and delete old block
				if ( g->blocks[i+j].isEmpty )
				{
					g->blocks[i+j] = Block( g->blocks[i+j-1].num );
					g->blocks[i+j-1].remove();
					g->notMoved = false;
				}
				// if block to the left is not empty, check if numbers match and combine
				else if ( ( g->blocks[i+j].num == g->blocks[i+j-1].num ) && g->blocks[i+j].notCombined && g->blocks[i+j-1].notCombined )
				{
					g->blocks[i+j] = Block( g->blocks[i+j-1].num * 2, false );
					g->score += blocks[i+j].num;
					g->blocks[i+j-1].remove();
					g->notMoved = false;
				}
				else break;
			}
		}
	}
	// check if grid has moved and returns null if not
	if ( g->notMoved ) 
		return NULL;
	// increase iteration and return new grid object
	g->iteration++;
	g->dir = 'r';
	return g;
}

/* move blocks up */
Grid *Grid::moveUp()
{
	makeAllCombinable();
	bool notMoved = true;
	Grid *g = new Grid( (*this) );

	// move blocks from row 2-4
	for ( int i = 4; i < 16; i++ )
	{
		if ( g->blocks[i].isEmpty )
			continue;

		for ( int j = 1; j < 4; j++ )
		{
			// iterate through blocks within the col
			if ( i-4*j >= 0 )
			{
				// if block above is empty, move it left and delete old block
				if ( g->blocks[i-j*4].isEmpty )
				{
					g->blocks[i-j*4] = Block( g->blocks[i-(j-1)*4].num );
					g->blocks[i-(j-1)*4].remove();
					g->notMoved = false;
				}
				// if block above is not empty, check if numbers match and combine
				else if ( ( g->blocks[i-j*4].num == g->blocks[i-(j-1)*4].num ) && g->blocks[i-j*4].notCombined && g->blocks[i-(j-1)*4].notCombined )
				{
					g->blocks[i-j*4] = Block( g->blocks[i-(j-1)*4].num * 2, false );
					g->score += g->blocks[i-j*4].num;
					g->blocks[i-(j-1)*4].remove();
					g->notMoved = false;
				}
				else break;
			}
		}
	}
	// check if grid has moved and returns null if not
	if ( g->notMoved ) 
		return NULL;
	// increase iteration and return new grid object
	g->iteration++;
	g->dir = 'u';
	return g;
}

/* move blocks down */
Grid *Grid::moveDown()
{
	makeAllCombinable();
	bool notMoved = true;
	Grid *g = new Grid( (*this) );

	// move blocks from row 3-1
	for ( int i = 11; i > -1; i-- )
	{
		if ( g->blocks[i].isEmpty )
			continue;

		for ( int j = 1; j < 4; j++ )
		{
			// iterate through blocks within the col
			if ( i+j*4 < 16 )
			{
				// if block below is empty, move it left and delete old block
				if ( g->blocks[i+j*4].isEmpty )
				{
					g->blocks[i+j*4] = Block( g->blocks[i+(j-1)*4].num );
					g->blocks[i+(j-1)*4].remove();
					g->notMoved = false;
				}
				// if block below is not empty, check if numbers match and combine
				else if ( ( g->blocks[i+j*4].num == g->blocks[i+(j-1)*4].num ) && g->blocks[i+j*4].notCombined && g->blocks[i+(j-1)*4].notCombined )
				{
					g->blocks[i+j*4] = Block( g->blocks[i+(j-1)*4].num * 2, false );
					g->score += blocks[i+j*4].num;
					g->blocks[i+(j-1)*4].remove();
					g->notMoved = false;
				}
				else break;
			}
		}
	}
	// check if grid has moved and returns null if not
	if ( g->notMoved ) 
		return NULL;
	// increase iteration and return new grid object
	g->iteration++;
	g->dir = 'd';
	return g;
}

/* finds max index of the grid */
int Grid::maxVal() const
{
	int n = 0;
	for ( int i = 1; i < 16; i++ )
		if ( blocks[n].num < blocks[i].num )
			n = i;
	return blocks[n].num;
}

/* finds value of a grid for IDS */
double Grid::value() const {
    double q1, q2, q3, q4, sum;
    int max =  maxVal();
    int n = 0;
    for ( int i = 0; i < 15; i++ ){
        if (blocks[i].num == 0){
            n++;
        }
        if(i != 3 && i != 7 && i != 11 && i != 15){
            if(blocks[i].num == blocks[i+1].num && blocks[i].num != 0){
                n++;
            }
		}
        if(i != 3 && i != 7 && i != 11 && i != 15 && i != 2 && i != 6 && i != 10 && i != 14){
            if(blocks[i].num == blocks[i+2].num && blocks[i].num != 0 && blocks[i+1].num == 0){
                n++;
            }
        }
        if(i == 0 || i == 4 || i == 8 || i == 12){
            if(blocks[i].num == blocks[i+3].num && blocks[i].num != 0 && blocks[i+1].num == blocks[i+2].num == 0){
                n++;
            }
        }
        if(i <= 11){
            if(blocks[i].num == blocks[i+4].num && blocks[i].num != 0){
                n++;
            }
        }
        if(i <= 7){
            if(blocks[i].num == blocks[i+8].num && blocks[i].num != 0 && blocks[i+4].num == 0){
                n++;
            }
        }
        if(i <= 3){
            if(blocks[i].num == blocks[i+12].num && blocks[i].num != 0 && (blocks[i+4].num  == blocks[i+8].num == 0)){
                n++;
            }
        }
    }
	if(max == blocks[0].num || max == blocks[1].num || max == blocks[4].num || max == blocks[5].num){
        q1 = (4*blocks[0].num + 2*(blocks[1].num + blocks[4].num) + blocks[5].num);
    }
    else{
        q1 = .5*(blocks[0].num + blocks[1].num + blocks[4].num + blocks[5].num);
    }

    if(max == blocks[2].num || max == blocks[3].num || max == blocks[6].num || max == blocks[7].num){
        q2 = (4*blocks[3].num + 2*(blocks[2].num + blocks[7].num) + blocks[6].num);
    }
    else{
        q2 = .5*(blocks[3].num + blocks[2].num + blocks[7].num + blocks[6].num);
    }
    if(max == blocks[12].num || max == blocks[13].num || max == blocks[8].num || max == blocks[9].num){
        q3 = (4*blocks[12].num + 2*(blocks[13].num + blocks[8].num) + blocks[9].num);
    }
    else{
        q3 = .5*(blocks[12].num + blocks[13].num + blocks[8].num + blocks[9].num);
    }
    if(max == blocks[10].num || max == blocks[11].num || max == blocks[14].num || max == blocks[15].num){
        q4 = (4*blocks[15].num + 2*(blocks[14].num + blocks[11].num) + blocks[10].num);
    }
    else{
        q4 = .5*(blocks[15].num + blocks[14].num + blocks[11].num + blocks[10].num);
    }
    sum = ((n/10)+1)*(q1+q2+q3+q4);
    return sum;
}

// int Grid::value() const{
//     int q1, q2, q3, q4;
// 	int max =  maxVal();
//     if(max == blocks[0].num || max == blocks[1].num || max == blocks[4].num || max == blocks[5].num){
//         q1 = (4*blocks[0].num + 2*(blocks[1].num + blocks[4].num) + blocks[5].num);
//     }
//     else{
//         q1 = .5*(blocks[0].num + blocks[1].num + blocks[4].num + blocks[5].num);
//     }

//     if(max == blocks[2].num || max == blocks[3].num || max == blocks[6].num || max == blocks[7].num){
//         q2 = (4*blocks[3].num + 2*(blocks[2].num + blocks[7].num) + blocks[6].num);
//     }
//     else{
//         q2 = .5*(blocks[3].num + blocks[2].num + blocks[7].num + blocks[6].num);
//     }
//     if(max == blocks[12].num || max == blocks[13].num || max == blocks[8].num || max == blocks[9].num){
//         q3 = (4*blocks[12].num + 2*(blocks[13].num + blocks[8].num) + blocks[9].num);
//     }
//     else{
//         q3 = .5*(blocks[12].num + blocks[13].num + blocks[8].num + blocks[9].num);
//     }
//     if(max == blocks[10].num || max == blocks[11].num || max == blocks[14].num || max == blocks[15].num){
//         q4 = (4*blocks[15].num + 2*(blocks[14].num + blocks[11].num) + blocks[10].num);
//     }
//     else{
//         q4 = .5*(blocks[15].num + blocks[14].num + blocks[11].num + blocks[10].num);
//     }
// 	return q1 + q2 + q3 + q4;
// }
// int Grid::value() const
// {
//     return 2*(blocks[0].num + blocks[3].num + blocks[12].num + blocks[15].num) + blocks[1].num + blocks[2].num + blocks[4].num
// 		+ blocks[7].num + blocks[8].num + blocks[11].num + blocks[13].num + blocks[14].num + 1/2*(blocks[10].num + blocks[9].num + blocks[5].num + blocks[6].num );
// }

/* print function */
void Grid::print_to_stream( ostream &out )
{
	int n = 0;

	for ( int i = 0; i < 4; i++ )
	{
		// _------_------_------_------
		for ( int i = 0; i < 4; i++ )
		{
			out << " ";
			for ( int i = 0; i < 6; i++ )
				out << "-";
		}
		out << endl;
		
		// |      |      |      |      |
		for ( int i = 0; i < 4; i++ )
			out << "|      ";
		out << "|\n";

		// | xxxx | xxxx | xxxx | xxxx |
		for ( int i = 0; i < 4; i++ )
		{
			out << "| ";
			if ( blocks[n].num < 1000 )
				out << " ";
			if ( blocks[n].num  < 100 )
				out << " ";
			if ( blocks[n].num  < 10 )
				out << " ";
			out << blocks[n].num  << " ";
			n++;
		}
		out << "|\n";
		
		// |      |      |      |      |
		for ( int i = 0; i < 4; i++ )
			out << "|      ";
		out << "|\n";
	}
	
	// _------_------_------_------
	for ( int i = 0; i < 4; i++ )
	{
		out << " ";
		for ( int i = 0; i < 6; i++ )
			out << "-";
	}
	out << endl;
}

/* print to cout */
void Grid::print()
{
	ostream *out = &cout;
	print_to_stream( *out );
}

/* check if more blocks are able to be added to the grid */
bool gridMoveable( Grid *g, char d )
{
	int n = 0;
	
	// increment n is a block is unable to be moved
	if ( d == 'l' )
		for ( int i = 0; i < 4; i ++ )
			if ( !g->blocks[i*4+3].isEmpty )
				n++;

	if ( d == 'r' )
		for ( int i = 0; i < 4; i ++ )
			if ( !g->blocks[i*4].isEmpty )
				n++;

	if ( d == 'u' )
		for ( int i = 0; i < 4; i ++ )
			if ( !g->blocks[12+i].isEmpty )
				n++;

	if ( d == 'd' )
		for ( int i = 0; i < 4; i ++ )
			if ( !g->blocks[i].isEmpty )
				n++;

	// return 1 if all blocks are unable to be moved
	if ( n == 4 ) return false;
	return true;
}

/* equality operator */
bool operator==( Grid const &g1, Grid const &g2 )
{
	for ( int i = 0; i < 16; i++ )
		if ( !( g1.blocks[i] == g2.blocks[i]) )
			return false;
	return g1.score == g2.score ? true : false;
}

bool operator!=( Grid const &g1, Grid const &g2 )
{
	for ( int i = 0; i < 16; i++ )
		if ( g1.blocks[i] != g2.blocks[i] )
			return true;
	return g1.score != g2.score ? true : false;
}

/* gt/lt operator */
bool operator>( Grid const &g1, Grid const &g2 )
{
	return g1.value() > g2.value() ? true : false;
}

bool operator<( Grid const &g1, Grid const &g2 )
{
	return g1.value() < g2.value() ? true : false;
}
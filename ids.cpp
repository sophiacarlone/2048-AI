#include <iostream>
#include <vector>
#include <stack>
#include <utility>
#include "grid.h"
#include "tree.hpp"
#include "ids.hpp"
using namespace std;

/* ai! */
void ai2048()
{
	
}

/* returns integer value for choosing next best move for AI */
pair<int,char> chooseMove( tree_node *t, int m, ostream &out) //m is current interation
{
	// how u do this
	if ( t == NULL )
	{
		cout << "how the fuck u do that" << endl;
		exit(1);
	}
	//t->root()->print();
	//t->root()->print_to_stream( out );

	// deepest iteration children nodes
	if ( t->root()->iteration == STEPS_AHEAD + m )
	{
		cout << "found leaf node!" << endl;
		out << "found leaf node!" << endl;
		return { t->root()->value(), t->root()->dir };
	}

	// ULDR nodes find average of their children
	else if ( t->root()->iteration % 2 == 1 )
	{
		cout << "found ULDR node: " << t->root()->dir << endl;
		out << "found ULDR node: " << t->root()->dir << endl;
		int sum = 0;
		t->MakeChildrenRand2();
		if ( t->children.size() == 0 )
			return { 0, t->root()->dir };
		for ( int i = 0; i < t->children.size(); i++ )
			sum += chooseMove( t->children[i], m, out ).first;
		cout << "value at direction " << t->root()->dir << " : " << sum / t->children.size() << endl;
		return { sum / t->children.size(), t->root()->dir };
	}

	// addBlock nodes find max of their children
	else
	{
		cout << "found addBlock node" << endl;
		out << "found addBlock node" << endl;
		int max = 0;
		char dir = '\0';
		t->MakeChildrenUDLR();
		if ( t->children.size() == 0 )
		{
			cout << "seriously, what the fuck even\n";
			exit(1);
		}
		for ( int i = 0; i < t->children.size(); i++ )
		{
			pair<int,char> temp = chooseMove( t->children[i], m, out );
			if ( max < temp.first )
			{
				max = temp.first;
				dir = temp.second;
			}
		}
		return { max, dir };
	}
}


/*
// Built around max tree
Grid ids(int maxDepth, Grid start, Grid goal){
    for (int depth = 0; depth <= maxDepth; depth++){
        vector<Grid> possibleMoves();
        stack<Grid> dfs;
        dfs->push(start);

        
        Grid top = dfs.top();
        dfs.pop();
        for (int i = 0; i < 16; i++){
            if (top.blocks[i].num == 2048){ 
                cout << "2048 YIPEE";
                top.print();
                return top;
            }
        }
        int highVal = top->value(); //not real function yet, meant to get highest value block
        for (int i = 0; i < 4; i++){ // Fix vector initialization
            if (possibleMoves[i].value() > highVal){
                Grid temp = top;
                dfs->push(temp);
            }
        }
        cout << "Removing: ";
        top.print();
    }
    cout << "Failure, game impossible to win";
    return;
}
*/


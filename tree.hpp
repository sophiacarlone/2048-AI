#ifndef TREE_HPP
#define TREE_HPP

#include<iostream>
#include<vector>
#include <time.h>
#include <stdlib.h>
#include"grid.h"

#define STEPS_AHEAD 8 //how many steps ahead are we looking

class tree_node{
    private:
        Grid *root_node;
    public:
        tree_node(Grid *root) {root_node = root;}
		~tree_node() {
			free(root_node);
			for ( int i = 0; i < children.size(); i++ )
				free( children[i] );
		}
        std::vector<tree_node *> children;
        void MakeTree(bool udlr);
		Grid *root() { return root_node; }
        void MakeChildrenUDLR();
        void MakeChildrenRand2();
};

#endif

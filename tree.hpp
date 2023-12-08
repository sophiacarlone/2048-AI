#ifndef TREE_HPP
#define TREE_HPP

#include<iostream>
#include<vector>
#include"grid.h"

#define STEPS_AHEAD 4 //how many steps ahead are we looking

class tree_node{
    private:
        Grid *root_node;
    public:
        tree_node(Grid *root) {root_node = root;}
        std::vector<tree_node *> children;
        void MakeTree(bool udlr);
		Grid *root() { return root_node; }
        void MakeChildrenUDLR();
        void MakeChildrenRand2();
};

#endif

#ifndef TREE_HPP
#define TREE_HPP

#include<iostream>
#include<vector>
#include"grid.h"

#define STEPS_AHEAD //how many steps ahead are we looking

class tree_node{
    private:
        Grid root_node;
    public:
        tree_node(Grid root) {root_node = root;}
        std::vector<Grid*> children;
        void MakeTree(bool udlr);
        void MakeChildrenUDLR();
        void MakeChildrenRand2();
};



#endif
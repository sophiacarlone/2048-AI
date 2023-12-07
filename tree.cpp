#include"tree.hpp"

using namespace std;

void tree_node::MakeTree(bool udlr){
    if(udlr) MakeChildrenUDLR();
    else MakeChildrenRand2();
}

void tree_node::MakeChildrenUDLR(){
    if(root_node.moveLeft() != NULL)
        children.push_back(root_node.moveLeft());
    if(root_node.moveRight() != NULL)
        children.push_back(root_node.moveRight());
    if(root_node.moveUp() != NULL)
        children.push_back(root_node.moveUp());
    if(root_node.moveDown() != NULL)
        children.push_back(root_node.moveDown());
}

void tree_node::MakeChildrenRand2(){
    for(int i = 0; i < 4; i++){
        Grid * temp = root_node.addBlock(i);
        if(temp != NULL) children.push_back(temp); 
    }
}
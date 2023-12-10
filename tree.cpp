#include"tree.hpp"

using namespace std;

void tree_node::MakeTree(bool udlr){
    if(udlr) MakeChildrenUDLR();
    else MakeChildrenRand2();
}

/* make ULDR children for tree nodes */
void tree_node::MakeChildrenUDLR(){
    int loc[4];
	for ( int i = 0; i < 4; i++ ) loc[i] = i;
    //srand(time(NULL));

    for ( int i = 4; i > 0; i-- )
	{
		int j = rand() % i; //+i
		if ( j < i-1 )
			swap( loc[j], loc[i-1] );
	}

    cout << "make children udlr" << endl;
    for ( int i = 0; i < 4; i++ ) cout << loc[i] << " ";
    cout << endl;

    for(int i = 0; i < 4; i++){
        if( i == 0 ){
            if(root_node->moveLeft() != NULL)
                children.push_back(new tree_node(root_node->moveLeft()));
        }
        else if(i == 1){
            if(root_node->moveRight() != NULL)
                children.push_back(new tree_node(root_node->moveRight()));
        }
        else if( i == 2 ){
            if(root_node->moveUp() != NULL)
                children.push_back(new tree_node(root_node->moveUp()));
        }
        else if(i ==3){
           if(root_node->moveDown() != NULL)
                children.push_back(new tree_node(root_node->moveDown()));
        }
    }
}

/* make addBlock children for tree nodes */
void tree_node::MakeChildrenRand2(){
    for(int i = 0; i < 4; i++){
        Grid * temp = root_node->addBlock(i);
        if(temp != NULL) children.push_back(new tree_node(temp)); 
    }
}

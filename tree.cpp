#include"tree.hpp"

using namespace std;

void tree_node::MakeTree(bool udlr){
    if(udlr) MakeChildrenUDLR();
    else MakeChildrenRand2();
}

void tree_node::MakeChildrenUDLR(){

}

void tree_node::MakeChildrenRand2(){


}




    int looked_ahead = 0;
    while(looked_ahead < STEPS_AHEAD){
        for(int i = 0; i < 4; i++){
            switch (i){
                case 0:
                    //right
                    break;
                case 1:
                    //left
                    break;
                case 2:
                    //up
                    break;
                case 3:
                    //down
                    break;
            }
        }
    }
}

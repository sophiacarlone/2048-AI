#include <iostream>
#include <grid.h>
#include <vector>
#include <stack>
using namespace std;

// Built around max tree

int ids(int maxDepth, Grid start, Grid goal){
    for (int depth = 0; depth <= maxDepth; depth++){
        vector<Grid> refVector();
        stack<Grid> dfs;
        dfs.push(start);

        while(!dfs.empty()){
            Grid top = dfs.top();
            dfs.pop();
            for (int i = 0; i < 16; i++){
                if (top.blocks[i].num == 2048){ 
                    cout << "2048 YIPEE";
                    top.print();
                    return 0;
                }
            }
            int highScore = top.score; //not real function yet, meant to get highest value block
            for (int i = 0; i < refVector.size(); i++){ // Fix vector initialization
                if (refVector[i].score > highScore){
                    Grid temp = top;
                    dfs.push(temp);
                }
            }
            cout << "Removing: ";
            top.print();
        }
    }
    cout << "Failure, game impossible to win";
    return 0;
}
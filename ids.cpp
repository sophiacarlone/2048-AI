#include <iostream>
#include <grid.h>
#include <vector>
#include <stack>
using namespace std;

// Built around max tree

Grid ids(int maxDepth, Grid start, Grid goal){
    for (int depth = 0; depth <= maxDepth; depth++){
        vector<Grid> possibleMoves();
        stack<Grid> dfs;
        dfs.push(start);

        
        Grid top = dfs.top();
        dfs.pop();
        for (int i = 0; i < 16; i++){
            if (top.blocks[i].num == 2048){ 
                cout << "2048 YIPEE";
                top.print();
                return top;
            }
        }
        int highVal = top.value(); //not real function yet, meant to get highest value block
        for (int i = 0; i < 4; i++){ // Fix vector initialization
            if (possibleMoves[i].value() > highVal){
                Grid temp = top;
                dfs.push(temp);
            }
        }
        cout << "Removing: ";
        top.print();
    }
    cout << "Failure, game impossible to win";
    return;
}


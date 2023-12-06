#include <iostream>
#include <grid.h>
#include <vector>
#include <stack>
using namespace std;

int ids(int maxDepth, Grid start, Grid goal){
    for (int depth = 0; depth <= maxDepth; depth++){
        vector<Grid> refVector();
        stack<Grid> dfs;
        dfs.push(start);

        while(!dfs.empty()){
            Grid top = dfs.top();
            dfs.pop();
            if (top.equals(goal)){ //wrong, make goal test check if there is a 2048 block
                cout << "2048 YIPEE";
                top.print();
                return 0;
            }
            int highestBlock = top.maxBlock(); //not real function yet, meant to get highest value block
            for (int i = 0; i < refVector.size(); i++){
                if (/*refVector[i].maxBlock > top.maxBlock*/){
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
#ifndef IDS_HPP
#define IDS_HPP

#include <utility>
#include "grid.h"
#include "tree.hpp"
using namespace std;

void ai2048();
pair<int,char> chooseMove( tree_node *, int, ostream & );

#endif

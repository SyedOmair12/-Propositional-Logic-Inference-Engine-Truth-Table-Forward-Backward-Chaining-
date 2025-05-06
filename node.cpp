#include "node.h"

Node::Node(int a,int b,char c):x(a),y(b),blockColour(c),goal_cost(-1),distance(-1),visited(false),previous(NULL){};

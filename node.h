#ifndef MYNODE_H
#define MYNODE_H

#ifndef NULL
#define NULL nullptr
#endif
using namespace std;

class Node
{
    public:
    int x;                                      
    int y;
                         
    char blockColour;                                 
    bool visited;

    unsigned int goal_cost;                     
    unsigned int distance; 
                                   
    Node *previous;                             
    Node(int a = -1,int b =-1,char c='O');   
};
#endif
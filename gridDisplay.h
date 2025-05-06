#ifndef MYGRID_H
#define MYGRID_H

#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include "node.h"
using namespace std;

class GridClass
{
    public:
    int N;                   
    int M;                   
    Node Start;              
    vector<Node> Goals;      
    Node** G;                

    GridClass(int a,int b);

    void p();

    bool is_Valid(int x,int y);

    bool is_Valid_1(int x,int y,Node* curr);

    int cost(Node* src, Node * dest);
    
    void print_path(Node * tail,stringstream &S);

    void reset_visit();

    void DFS(Node *curr);

    void BFS(Node *curr);

    void GBFS(Node* src, Node * dest);

    void AS(Node* src, Node * dest);

    void CUS1(Node * src);

    void CUS2(Node * src);
};
#endif
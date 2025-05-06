#include<iostream>
#include<stdio.h>
#include<vector>

#include "node.h"
#include "gridDisplay.h"
#include "filehander.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc<3)
    {
        printf("Usage : %s <filename> <method>\n",argv[0]);
        return 0;
    }
    string method = argv[2];

    GridClass * grid_class_object = ParseLine(argv[1]);
    grid_class_object->p();
    grid_class_object->G[grid_class_object->Start.x][grid_class_object->Start.y].distance = 0;

    if(method == "DFS") {
        cout<<"Algorithm used is Depth First Search\n";
        grid_class_object->G[grid_class_object->Start.x][grid_class_object->Start.y].visited=true;
        grid_class_object->DFS(&(grid_class_object->Start));
    }
    else if(method == "BFS"){
        cout<<"Algorithm used is Breadth First Search\n";
        grid_class_object->BFS(&(grid_class_object->Start));
    }
    else if(method == "GBFS"){
        cout<<"Algorithm used is Greedy Best First Search\n";
        for(int i=0;i<grid_class_object->Goals.size();i++)
        {
            grid_class_object->GBFS(&(grid_class_object->Start),&(grid_class_object->Goals[i]));
            grid_class_object->reset_visit();
        }
    }
    else if(method == "AS"){
        cout<<"Algorithm used is A* Search\n";
        for(int i=0;i<grid_class_object->Goals.size();i++)
        {
            grid_class_object->AS(&(grid_class_object->Start),&(grid_class_object->Goals[i]));
            grid_class_object->reset_visit();
        }
    }
    else if(method == "CUS1")
    {
        cout<<"Algorithm used is Dijkstra’s Algorithm\n";
        grid_class_object->CUS1(&(grid_class_object->Start));
        for(int i=0;i<grid_class_object->Goals.size();i++)
        {
            int gx = grid_class_object->Goals[i].x;
            int gy = grid_class_object->Goals[i].y;
            stringstream path;
            grid_class_object->print_path(&(grid_class_object->G[gx][gy]),path);
            cout<<path.str()<<endl;
        }
    }
    else if(method == "CUS2")
    {
        cout<<"Algorithm used is Modified Djikstras to visit all Goals with shortest path.\n";
        grid_class_object->CUS2(&(grid_class_object->G[grid_class_object->Start.x][grid_class_object->Start.y]));
    }
    return 0;
}

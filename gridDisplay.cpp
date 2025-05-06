#include "gridDisplay.h"
/**
 * Constructor rows and columns
*/
GridClass::GridClass(int a,int b)
{
    N=a;
    M=b;
    G = new Node*[N];
    for(int i = 0; i < N; ++i){
        G[i] = new Node[M];
        // #pragma omp parallel for
        for(int j = 0; j < M; ++j) {
            G[i][j].x=i;
            G[i][j].y=j;
        }
    }   
}
//print results on terminal
void GridClass::p()
{
    for(int i=0 ;i<N ;i++)
    {
        for(int j=0 ;j<M;j++)cout<<G[i][j].blockColour<<" ";
        cout<<endl;
    }
}
//x rows, y columns
bool GridClass::is_Valid(int x,int y)
{
    if(x<0)return false;
    if(x>=N) return false;
    if(y<0)return false;
    if(y>=M)return false;
    if(G[x][y].blockColour=='W') return false;
    if(G[x][y].visited == true) return false;
    return true;
}

//x row number, y column number
bool GridClass::is_Valid_1(int x,int y,Node * current)
{
    if(x<0)return false;
    if(x>=N) return false;
    if(y<0)return false;
    if(y>=M)return false;
    if(G[x][y].blockColour=='W') return false;
    if(G[x][y].distance <= current->distance+1) return false;
    return true;
}

void GridClass::reset_visit(){
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<M;j++){
            G[i][j].visited=false;
            G[i][j].goal_cost=-1;
            G[i][j].distance=-1;
            G[i][j].previous=NULL;
        }
    }
}

//source and destination nodes
int GridClass::cost(Node * src, Node * dest)
{
    return abs(src->x - dest->x) + abs(src->y - dest->y);
}

//tail of pointer, path
void GridClass::print_path(Node * tail,stringstream & S)
{
    if(tail->previous==NULL) return; 
    print_path(tail->previous, S);
    int dx = tail->previous->x - tail->x ;
    int dy = tail->previous->y - tail->y ;

    if(tail->previous->blockColour=='R')S << "Start : ( "<<tail->previous->x<<", "<<tail->previous->y<<")\t ";
    

    if(dx == -1) S << "down; ";
    else if(dx == 1) S <<"up; ";
    else if (dy == 1) S << "left; ";
    else if (dy == -1) S << "right; ";

    if(tail->blockColour=='G')S << "Goal : ( "<<tail->x<<", "<<tail->y<<") ";
}
//current node
void GridClass::DFS(Node * current)
{
    current->visited = true;
    if(current->blockColour == 'G')
    {
        stringstream path;
        print_path(current,path);
        cout<<path.str()<<endl;
        return;
    } 
    
    if(is_Valid(current->x-1,current->y)) {

        G[current->x-1][current->y].previous = current;
        DFS(&G[current->x-1][current->y]);
        G[current->x-1][current->y].previous = NULL;
    }
    if(is_Valid(current->x,current->y-1)){

        G[current->x][current->y-1].previous = current;
        DFS(&G[current->x][current->y-1]);
        G[current->x][current->y-1].previous = NULL;
    }
    if(is_Valid(current->x+1,current->y)){

        G[current->x+1][current->y].previous = current;
        DFS(&G[current->x+1][current->y]);
        G[current->x+1][current->y].previous = NULL;
    }
    if(is_Valid(current->x,current->y+1)){

        G[current->x][current->y+1].previous = current;
        DFS(&G[current->x][current->y+1]);
        G[current->x][current->y+1].previous = NULL;
    }
    current->visited = false;
}

void GridClass::BFS(Node * current)
{
    queue<Node *> Search;
    current->visited = true;
    Search.push(current);
    
    while(!Search.empty())
    {
        Node * temp = Search.front();
        Search.pop();

        if(temp->blockColour == 'G')
        {
            stringstream path;
            print_path(temp,path);
            cout<<path.str()<<endl;
        }
        if(is_Valid(temp->x-1,temp->y))
        {
            G[temp->x-1][temp->y].previous = temp;
            G[temp->x-1][temp->y].visited = true;
            Search.push(&G[temp->x-1][temp->y]);
        }
        if(is_Valid(temp->x,temp->y-1))
        {
            G[temp->x][temp->y-1].previous = temp;
            G[temp->x][temp->y-1].visited = true;
            Search.push(&G[temp->x][temp->y-1]);
        }
        if(is_Valid(temp->x+1,temp->y))
        {
            G[temp->x+1][temp->y].previous = temp;
            G[temp->x+1][temp->y].visited = true;
            Search.push(&G[temp->x+1][temp->y]);
        }
        if(is_Valid(temp->x,temp->y+1))
        {
            G[temp->x][temp->y+1].previous = temp;
            G[temp->x][temp->y+1].visited = true;
            Search.push(&G[temp->x][temp->y+1]);
        }

    }
}

//Comparator for the priority queue for GBFS
struct compare
{
    bool operator()(const Node * a, const Node * b)
    {
        return a->goal_cost > b->goal_cost;
    }
};

void GridClass::GBFS(Node* src, Node* dest)
{
    priority_queue<Node*, vector<Node*>, compare > pq;
    src->goal_cost = cost(src,dest);
    pq.push(src);
    src->visited =true;
    
 
    while (!pq.empty()) {
        Node* temp = pq.top();
        pq.pop();
        
        if(temp->x==dest->x && temp->y == dest->y)
        {
            stringstream path;
            print_path(temp,path);
            cout<<path.str()<<endl;
            break;
        }
        int tx=temp->x;
        int ty=temp->y;

        if(is_Valid(tx-1,ty))
        {
            G[tx-1][ty].previous = temp;
            G[tx-1][ty].goal_cost = cost(&G[tx-1][ty],dest);
            G[tx-1][ty].visited = true;
            pq.push(&G[tx-1][ty]);
        }
        if(is_Valid(tx,ty-1))
        {
            G[tx][ty-1].previous = temp;
            G[tx][ty-1].goal_cost = cost(&G[tx][ty-1],dest);
            G[tx][ty-1].visited = true;
            pq.push(&G[tx][ty-1]);
        }
        if(is_Valid(tx+1,ty))
        {
            G[tx+1][ty].previous = temp;
            G[tx+1][ty].goal_cost = cost(&G[tx+1][ty],dest);
            G[tx+1][ty].visited = true;
            pq.push(&G[tx+1][ty]);
        }
        if(is_Valid(tx,ty+1))
        {
            G[tx][ty+1].previous = temp;
            G[tx][ty+1].goal_cost = cost(&G[tx][ty+1],dest);
            G[tx][ty+1].visited = true;
            pq.push(&G[tx][ty+1]);
        }
    }    
}

struct compare_1
{
    bool operator()(const Node * a, const Node * b)
    {
        return (a->goal_cost + a->distance) > (b->goal_cost + b->distance);
    }
};

void GridClass::AS(Node* src, Node* dest)
{

    priority_queue<Node*, vector<Node*>, compare_1> pq;

    src->goal_cost = cost(src,dest);
    src->distance = 0;
    src->visited =true;
    pq.push(src);
    
    
    while (!pq.empty()) {
        Node* temp = pq.top();
        pq.pop();
        
        if(temp->x==dest->x && temp->y == dest->y)
        {
            stringstream path;
            print_path(temp,path);
            cout<<path.str()<<endl;
            break;
        }
        int tx=temp->x;
        int ty=temp->y;

        if(is_Valid(tx-1,ty))
        {
            G[tx-1][ty].previous = temp;
            G[tx-1][ty].distance = temp->distance + 1;
            G[tx-1][ty].goal_cost = cost(&G[tx-1][ty],dest);
            G[tx-1][ty].visited = true;
            pq.push(&G[tx-1][ty]);
        }
        if(is_Valid(tx,ty-1))
        {
            G[tx][ty-1].previous = temp;
            G[tx][ty-1].distance = temp->distance + 1;
            G[tx][ty-1].goal_cost = cost(&G[tx][ty-1],dest);
            G[tx][ty-1].visited = true;
            pq.push(&G[tx][ty-1]);
        }
        if(is_Valid(tx+1,ty))
        {
            G[tx+1][ty].previous = temp;
            G[tx+1][ty].distance = temp->distance + 1;
            G[tx+1][ty].goal_cost = cost(&G[tx+1][ty],dest);
            G[tx+1][ty].visited = true;
            pq.push(&G[tx+1][ty]);
        }
        if(is_Valid(tx,ty+1))
        {
            G[tx][ty+1].previous = temp;
            G[tx][ty+1].distance = temp->distance + 1;
            G[tx][ty+1].goal_cost = cost(&G[tx][ty+1],dest);
            G[tx][ty+1].visited = true;
            pq.push(&G[tx][ty+1]);
        }
    }    
}

//Comparator for the priority queue for djkistra's
struct compare_2
{
    bool operator()(const Node * a, const Node * b)
    {
        return a->distance > b->distance;
    }
};

void GridClass::CUS1(Node * src)
{
    priority_queue<Node*, vector<Node*>, compare_1> pq;
    src->distance = 0;
    pq.push(src);
    while (!pq.empty())
    {
        Node* temp = pq.top();
        pq.pop();

        int tx=temp->x;
        int ty=temp->y;

        if(is_Valid_1(tx-1,ty,temp))
        {
            G[tx-1][ty].previous = temp;
            G[tx-1][ty].distance = temp->distance + 1;
            pq.push(&G[tx-1][ty]);
        }
        if(is_Valid_1(tx,ty-1,temp))
        {
            G[tx][ty-1].previous = temp;
            G[tx][ty-1].distance = temp->distance + 1;
            pq.push(&G[tx][ty-1]);
        }
        if(is_Valid_1(tx+1,ty,temp))
        {
            G[tx+1][ty].previous = temp;
            G[tx+1][ty].distance = temp->distance + 1;
            pq.push(&G[tx+1][ty]);
        }
        if(is_Valid_1(tx,ty+1,temp))
        {
            G[tx][ty+1].previous = temp;
            G[tx][ty+1].distance = temp->distance + 1;
            pq.push(&G[tx][ty+1]);
        }
    }
}

void GridClass::CUS2(Node * src)
{    
    stringstream path;
    int goal_count = 0;
    
    while(goal_count < Goals.size())
    {
        GridClass::CUS1(src);
        int MIN =-1;
        unsigned int dt = -1;

        for(int i=0;i<Goals.size();i++)
        {
            if(Goals[i].visited == true ) continue;

            if(G[Goals[i].x][Goals[i].y].distance < dt)
            {
                MIN = i;
                dt = G[Goals[i].x][Goals[i].y].distance;
            }
        }
        
        Goals[MIN].visited = true;
        int gx = Goals[MIN].x;
        int gy = Goals[MIN].y;
        goal_count++;

        print_path(&G[gx][gy],path);

        src = &G[gx][gy];
        reset_visit();
    }
    cout<<path.str()<<endl;
}
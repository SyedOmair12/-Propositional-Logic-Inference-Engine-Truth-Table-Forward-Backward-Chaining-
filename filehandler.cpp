#include "filehander.h"

vector <int> ParseLine(char *line,int len)
{
    
    vector<int> args;
    int i=0;
    int sum=0;
    bool start = false;

    while(i<len)    //loop till the line is not finished
    {
        if(line[i]>='0' && line[i]<='9')    // check if the character is a digit 
        {
            if(!start) start = true;        // if yes change the current number 
            sum *= 10;
            sum += line[i]-'0';
        }

        if(!(line[i]>='0' && line[i]<='9') && start) //if character is not a number then ignore 
        {
            args.push_back(sum);
            start = false;
            sum = 0;
        }
        if(line[i]=='\n')break;
        i++;
    }
    
    return args;
}

GridClass * ParseLine(char * file)
{
    FILE * f = fopen(file,"r"); //open file in read mode
    if(f==NULL)
    {
        printf("Could not locate %s. Closing the program... \n",file);
        return NULL;  
    }

    
    char file_line[32];
    char line_goal[256];

    if(fgets(file_line,32,f)==NULL)               
    {
        printf("Arguments are missing. Exiting ...\n");
        return NULL;   
    }
    vector<int> argV = ParseLine(file_line,32);
    
    GridClass *grid_class = new GridClass(argV[0],argV[1]);

    //Checking and parsing for Start Values
    if(fgets(file_line,32,f)==NULL)
    {
        printf("Initial state missing. Exiting ...\n");
        return NULL;   
    }
    argV = ParseLine(file_line,32);
    grid_class->Start = Node(argV[1],argV[0],'R');
    grid_class->G[argV[1]][argV[0]].blockColour = 'R';
    

    // parsing the goal states into a node vector
    if(fgets(line_goal,256,f)==NULL)
    {
        printf("Missing goal. Exiting ...\n");
        return NULL;   
    }
    argV = ParseLine(line_goal,256);

    for(int i=0;i<argV.size();i+=2) {
        grid_class->Goals.push_back(Node(argV[i+1],argV[i],'G'));
        grid_class->G[argV[i+1]][argV[i]].blockColour = 'G';
    }

    // parsing the walls
    while(fgets(file_line,32,f)!=NULL)
    {
        argV = ParseLine(file_line,32);
        for(int i=0;i<argV[3];i++){
            for(int j=0;j<argV[2];j++) grid_class->G[argV[1]+i][argV[0]+j].blockColour='W';
        }
    }
    
    return grid_class;

}

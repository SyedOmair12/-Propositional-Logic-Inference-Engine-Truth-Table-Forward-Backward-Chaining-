#ifndef MYFILE_H
#define MYFILE_H

#include<iostream>
#include<stdio.h>
#include<vector>

#include "gridDisplay.h"
using namespace std;

vector<int> ParseLine(char *line,int len);
GridClass * ParseLine(char * file);


#endif
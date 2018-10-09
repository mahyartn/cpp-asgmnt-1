#ifndef PATHFINDER_H
#define PATHFINDER_H

#include"basic.h"
#include<vector>
#include<stdlib.h>

class Router 
{
public:
    int x;
    bool findRoute(std::vector <std::string> map,std::vector<cordinate*> &cordinates_queue,std::vector<int>  cordinates_parents_adress,cordinate home,cordinate destination);
    bool addCordinatesToQueue(std::vector<std::string> map,std::vector<cordinate*> &cordinates_queue,std::vector<int>  &cordinates_parents_adress,cordinate input,int input_address,cordinate destination);
};

#endif

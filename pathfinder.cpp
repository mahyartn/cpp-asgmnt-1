#include "pathfinder.h"


bool Router::findRoute(std::vector <std::string> map,std::vector<cordinate*> &cordinates_queue,std::vector<int>  cordinates_parents_adress,cordinate home,cordinate destination)
{
    bool status=addCordinatesToQueue(map,cordinates_queue,cordinates_parents_adress,home,0,destination);
    if (status==true) std::cout<<"path found"<<'\n';
}
bool Router::addCordinatesToQueue(std::vector<std::string> map,std::vector<cordinate*> &cordinates_queue,std::vector<int>  &cordinates_parents_adress,cordinate input,int input_address,cordinate destination)
{   
    if (map[input.y][input.x] != '#')
    {
        if (input==destination) return true;
        cordinates_queue.push_back(&input);
        cordinates_parents_adress.push_back(input_address);
        map[input.y][input.x] = '#';
        for (int i=0;i<4;i++)
        {
            bool status=addCordinatesToQueue(map,cordinates_queue,cordinates_parents_adress,neighourPosition(input,i),(input_address+i+1),destination);
            if (status== true) return true;
        }
    }
    return false;
}

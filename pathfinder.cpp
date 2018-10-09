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

// bool game::findPath(std::vector<std::string> &tmap, int number, int y, int x)
// {
//     cordinate tmp;
//     bool found = 0;
//     //std::cout<<"hummmm!!\n";
//     if (tmap[y][x] == (number + 49))
//     {
//         //std::cout<<"found :"<< number+1 <<" : "<<y<<" "<<x<<'\n';
//         found = true;
//     }
//     else if (tmap[y][x] != '#')
//     {
//         tmap[y][x] = '#';
//         found = findPath(tmap, number, y - 1, x);
//         if (!found)
//             found = findPath(tmap, number, y, x - 1);
//         if (!found)
//             found = findPath(tmap, number, y + 1, x);
//         if (!found)
//             found = findPath(tmap, number, y, x + 1);
//     }
//     if (found)
//     {
//         tmp.x = x;
//         tmp.y = y;
//         routes[number].push_back(tmp);
//     }
//     return found;
// }


// void game::findAllPaths()
// {
//     for (int childNum = 0; childNum < 7; childNum++)
//     {
//         std::vector<std::string> tmpMap;
//         tmpMap = static_map;
//         findPath(tmpMap, childNum, nokhodies[childNum].position.y, nokhodies[childNum].position.x);
//         iterators[childNum] = routes[childNum].end();
//     }
// }

#ifndef BASIC_H
#define BASIC_H
#include <fstream>
#include <iostream>
#include <string>
#include <vector>


extern int g_number_of_children;
extern int g_map_lenght;
extern int g_map_height;

class cordinate {
    public:
        int x;
        int y;
        bool operator==(cordinate subject);
};

class gameSetting
{
public:
    int initial_time;
    int eidi_bonus;
    std::vector<int> children_stamina;
    std::vector<std::string> static_map;
    void loadMap();
    void loadConfig();
};

cordinate neighourPosition(cordinate home,int neighbourNumber);
void printMap(std::vector <std::string> map);
bool findRoute(std::vector <std::string> map,std::vector<cordinate> &cordinates_queue,std::vector<int>  &cordinates_parents_adress,cordinate home,cordinate destination);


#endif

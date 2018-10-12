#ifndef BASIC_H
#define BASIC_H
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <time.h>

#define NUMBER_OF_CHILDREN 7
#define MAP_LENGHT 29
#define MAP_HEIGHT 11
#define FREEZ_TIME 5

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
    void LoadMap();
    void LoadConfig();
};



cordinate NeighourPosition(cordinate home,int neighbourNumber);


#endif

#ifndef BASIC_H
#define BASIC_H
#include <fstream>
#include <iostream>
#include <string>
#include <vector>


extern int number_of_children;
extern int map_lenght;
extern int map_height;

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



#endif

#ifndef CHARACTERS_H
#define CHARACTERS_H
#include "characters.h"
#include "basic.h"
#include <vector>
#include "pathfinder.h"
class child
{
    std::vector <cordinate> route;
    cordinate home;
    cordinate destination;
    
    int iterator=0;
  public:
    //child();
    char character_name;
    child(int initial_stamina,cordinate home_position,cordinate destination_position,char name_character);
    void makeMove(std::vector <std::string>& map,std::vector <std::string>& map2);
    void setRoute(std::vector <cordinate> given_route,std::vector <int> address_list);
    void showRoute();
    int starting_stamina;
    int current_stamina;
    int wait;
    int freez_time=0;
    bool IsFreez;
    bool IsScared=false;
    bool IsHandFull=false;
    bool IsAtHome;
    cordinate current_position;
};

class ghost
{
  public:
    ghost(cordinate start_position);
    cordinate current_position;
    void makeMove(std::vector <std::string> &map);
};

#endif
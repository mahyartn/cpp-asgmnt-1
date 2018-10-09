#ifndef GAME_H
#define GAME_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <unistd.h>
//#include "basic.h"
#include "characters.h"
//#include "pathfinder.h"

// class child
// {
//   public:
//     child();
//     int stamina;
//     int wait;
//     bool IsFreez;
//     bool IsScared;
//     bool IsHandFull;
//     bool IsAtHome;
//     cordinate position;
// };
class game
{
  private:
    std::vector<int> config;
    std::vector<std::string> static_map;
    std::vector<std::string> game_dynamic_map;
    std::vector<cordinate> routes[7];
    std::vector<cordinate> ghostList;
    int ghostNum = 0;
    //child nokhodies[7];
    std::vector<ghost*> ghosts;
    cordinate home_position;
    //void check

  public:
    
    game(std::vector<std::string> &map,int initial_time,std::vector<int> children_stamina,int eidi_bonus);
    std::vector <cordinate> destination_list;
    std::vector<child*> children;
    cordinate getHomePosition();
    void extractObjects();
    void updateTurn();
    void printmap();
    void refreshGhosts();
    void updateChildren();
    void checkState();
    void setHomePosition(int y,int x); 
    int getGameTime();
    int getChildInitialStamina(int num);
    int remainingObjectives();    
};

#endif
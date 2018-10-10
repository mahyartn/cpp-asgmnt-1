#ifndef GAME_H
#define GAME_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <unistd.h>
#include "characters.h"

class Game
{
  private:
    std::vector<int> config;
    std::vector<std::string> static_map;
    std::vector<std::string> game_dynamic_map;
    std::vector<cordinate> routes[7];
    std::vector<cordinate> ghostList;
    int ghostNum = 0;
    std::vector<ghost*> ghosts;
    cordinate home_position;

  public:
    
    Game(std::vector<std::string> &map,int initial_time,std::vector<int> children_stamina,int eidi_bonus);
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
    void createChildren(std::vector<std::string>map,std::vector<child*> &children,std::vector <cordinate> destination_list,std::vector<int> children_stamina,cordinate home_position);

};

#endif
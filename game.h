#ifndef GAME_H
#define GAME_H


#include <string>
#include <vector>
#include <time.h>
#include <unistd.h>
#include "characters.h"
#include "map.h"


class Game
{
  private:
    std::vector<int> config;
    std::vector<Ghost*> ghosts;
    std::vector<Child*> children;
    
  public:
    Map* map;
    Game(std::vector<std::string> &given_map,int initial_time,std::vector<int> children_stamina,int eidi_bonus);
    void createChildren(std::vector <cordinate> routes[],std::vector<int> children_stamina,cordinate home_position);
    void UpdateCharacters();
    void checkState();
    int getGameTime();
    int remainingObjectives();
    
    
};

#endif
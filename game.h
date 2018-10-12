#ifndef GAME_H
#define GAME_H

#include <time.h>
#include <unistd.h>
#include "characters.h"



class Game
{
  private:
    std::vector<int> config;
    std::vector<Ghost*> ghosts;
    std::vector<Child*> children;
    
  public:
    Mapper* map;
    Game(std::vector<std::string> &given_map,int initial_time,std::vector<int> children_stamina,int eidi_bonus);
    void CreateChildren(std::vector <cordinate> routes[],std::vector<int> children_stamina,cordinate home_position);
    void UpdateCharacters();
    void CheckState();
    int GetGameTime();
    int RemainingObjectives();
    
    
};

#endif
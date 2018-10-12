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

class Mapper
{
  private:
  std::vector <std::string> static_map;
  std::vector <std::string> game_dynamic_map;
  std::vector <cordinate> destination_list;
  cordinate home_position;
  void CheckForPrizes(int x,int y);
  void CheckForGhosts(int x,int y);
  void CheckForHome(int x,int y);
  void ExtractObjects();
  std::vector <cordinate> findRoute(cordinate home,cordinate destination);

  public:
  Mapper(std::vector<std::string> &map);
  std::vector <cordinate> routes[NUMBER_OF_CHILDREN];
  std::vector <cordinate> ghost_list;
  void PrintMap();
  void SetStaticChar(int x,int y,char character);
  void SetDynamicChar(int x,int y,char character);;
  char GetDynamicChar(int x,int y);
  char GetStaticChar(int x,int y);
  void RefreshDynamicMap();
  cordinate GetHomePosition();

};


cordinate NeighourPosition(cordinate home,int neighbourNumber);


#endif

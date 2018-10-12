#ifndef MAPPER_H
#define MAPPER_H

#include "basic.h"

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


#endif
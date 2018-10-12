#ifndef CHARACTERS_H
#define CHARACTERS_H
#include "characters.h"
#include "basic.h"
#include "map.h"
#include <vector>
#include <time.h>
class Child
{
  private:
  void showRoute();
  void CheckIfHome();
  bool CheckIfFrozen();
  void UpdateIterator();
  void IteratorLimiter();
  std::vector <cordinate> route;
  cordinate home;
  cordinate destination;
  int starting_stamina=0;
  int current_stamina=0;
  int freez_time=0;
  int iterator=0;
  bool IsScared=false;
  bool IsHandFull=false;

  public:
  Child(int initial_stamina,cordinate home_position,std::vector <cordinate> given_route,char name_character);
  void makeMove();
  void setRoute(std::vector <cordinate> given_route,std::vector <int> address_list);
  void CheckStamina();
  void CheckEidies(Map *map);
  void LookForGhosts(Map *map);
  void CheckCyns(Map *map);
  char character_name;
  bool done;
  cordinate current_position;
};

class Ghost
{
  public:
  Ghost(cordinate start_position);
  cordinate current_position;
  void makeMove();
};

#endif
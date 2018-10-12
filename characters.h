#ifndef CHARACTERS_H
#define CHARACTERS_H


#include "mapper.h"

class Child
{
  private:
  std::vector <cordinate> route;
  cordinate home;
  cordinate destination;
  void ShowRoute();
  void CheckIfHome();
  bool CheckIfFrozen();
  void UpdateIterator();
  void IteratorLimiter();
  int starting_stamina=0;
  int current_stamina=0;
  int freez_time=0;
  int iterator=0;
  bool is_scared=false;
  bool is_handFull=false;

  public:
  Child(int initial_stamina,cordinate home_position,std::vector <cordinate> given_route,char name_character);
  void MakeMove();
  void CheckStamina();
  void CheckEidies(Mapper *map);
  void LookForGhosts(Mapper *map);
  void CheckCyns(Mapper *map);
  char character_name;
  bool is_done;
  cordinate current_position;
};

class Ghost
{
  public:
  Ghost(cordinate start_position);
  cordinate current_position;
  void MakeMove();
};

#endif
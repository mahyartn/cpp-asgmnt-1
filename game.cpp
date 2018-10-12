#include "game.h"
//#include "map.h"

Game::Game(std::vector<std::string> &given_map,int initial_time,std::vector<int> children_stamina,int eidi_bonus)
{
    map=new Map(given_map);
    config.push_back(initial_time);
    config.push_back(eidi_bonus);
}

int Game::getGameTime()
{
    return config[0];
}

void Game::UpdateCharacters()
{ 
    map->RefreshDynamicMap();
    for (int j=0;j< children.size();j++)
    { 
        children[j]->makeMove();
        map->SetDynamicChar(children[j]->current_position.x , children[j]->current_position.y ,children[j]->character_name);
    }
    for (int i=0;i< ghosts.size();i++)
    {
        ghosts[i]->makeMove();
        map->SetDynamicChar(ghosts[i]->current_position.x , ghosts[i]->current_position.y ,'G');
    }
}

int Game::remainingObjectives()
{
    int h = 0;
    for (int i = 0; i < children.size(); i++)
    {
        if (children[i]->done)
        {
            h++;
        }
    }
    return 7 - h;
}

void Game::checkState()
{
    for (int i = 0; i < children.size(); i++)
    {
        children[i]->CheckCyns(map);
        children[i]->CheckStamina();
        children[i]->CheckEidies(map);
        children[i]->LookForGhosts(map);   
    }
}

void Game::createChildren(std::vector <cordinate> routes[],std::vector<int> children_stamina,cordinate home_position)
{
    for (int k=0;k< g_number_of_children;k++)
    {
        children.push_back(new Child(children_stamina[k],home_position,routes[k],k+'T'));
    }
}
#include "game.h"
//#include "mapper.h"

Game::Game(std::vector<std::string> &given_map,int initial_time,std::vector<int> children_stamina,int eidi_bonus)
{
    map=new Mapper(given_map);
    config.push_back(initial_time);
    config.push_back(eidi_bonus);
    for (int k=0;k<map->ghost_list.size();k++)
    {
        Ghost* tmp= new Ghost(map->ghost_list[k]);
        ghosts.push_back(tmp);    
    }
}

int Game::GetGameTime()
{
    return config[0];
}

void Game::UpdateCharacters()
{ 
    map->RefreshDynamicMap();
    for (int j=0;j< children.size();j++)
    { 
        children[j]->MakeMove();
        map->SetDynamicChar(children[j]->current_position.x , children[j]->current_position.y ,children[j]->character_name); 
    }
    for (int i=0;i< ghosts.size();i++)
    {
        ghosts[i]->MakeMove();
        map->SetDynamicChar(ghosts[i]->current_position.x , ghosts[i]->current_position.y ,'G');
    }
}

int Game::RemainingObjectives()
{
    int h = 0;
    for (int i = 0; i < children.size(); i++)
    {
        if (children[i]->is_done)
        {
            h++;
        }
    }
    return 7 - h;
}

void Game::CheckState()
{
    for (int i = 0; i < children.size(); i++)
    {
        children[i]->CheckCyns(map);
        children[i]->CheckStamina();
        children[i]->CheckEidies(map);
        children[i]->LookForGhosts(map);   
    }
}

void Game::CreateChildren(std::vector <cordinate> routes[],std::vector<int> children_stamina,cordinate home_position)
{
    for (int k=0;k< NUMBER_OF_CHILDREN;k++)
    {
        children.push_back(new Child(children_stamina[k],home_position,routes[k],k+'T'));
    }
}
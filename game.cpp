#include "game.h"

Game::Game(std::vector<std::string> &map,int initial_time,std::vector<int> children_stamina,int eidi_bonus)
{
    static_map=map;
    config.push_back(initial_time);
    config.push_back(eidi_bonus);
}
void Game::setHomePosition(int y, int x)
{
    home_position.x=x;
    home_position.y=y;
}
cordinate Game::getHomePosition()
{   
    return home_position;
}
int Game::getGameTime()
{
    return config[0];
}

void Game::CheckForPrizes(int x,int y)
{
    for(int i=1;i <= g_number_of_children;i++)
    {
        if (static_map[y][x] == i + '0')
        {
            cordinate tmp;
            tmp.y=y;
            tmp.x=x;
            destination_list.push_back(tmp);
        }
    } 
}

void Game::CheckForGhosts(int x,int y)
{
    if (static_map[y][x] == 'G')
    {
        cordinate tmp;
        tmp.x = x;
        tmp.y = y;
        Ghost* g= new Ghost(tmp);
        ghosts.push_back(g);
        static_map[y][x] = '.';
    }
}

void Game::CheckForHome(int x,int y)
{
    if (static_map[y][x] == 'H')
        {
            setHomePosition(y,x);
        }  
}

void Game::extractObjects()
{
    cordinate tmp;
    for (int y = 1; y < g_map_height-1; y++)
    {
        for (int x = 1; x < g_map_lenght -1; x++)
        {
            CheckForGhosts(x,y);
            CheckForHome(x,y);
            CheckForPrizes(x,y);             
        }
    }
}

void Game::printmap()
{
    for (int y = 0; y < g_map_height; y++)
    {
        for (int x = 0; x < g_map_lenght; x++)
        {
            std::cout << game_dynamic_map[y][x];
        }
        std::cout << '\n';
    }
}
void Game::UpdateCharacters()
{
    game_dynamic_map = static_map; 
    for (int j=0;j< children.size();j++)
    { 
        children[j]->makeMove(game_dynamic_map,static_map);
        game_dynamic_map[children[j]->current_position.y][children[j]->current_position.x] =children[j]->character_name;
    }
    for (int i=0;i< ghosts.size();i++)
    {
        ghosts[i]->makeMove(game_dynamic_map);
        game_dynamic_map[ghosts[i]->current_position.y][ghosts[i]->current_position.x]='G';
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

void Game::CheckStamina(int i)
{
    if (children[i]->current_stamina <= 0)
        {
            children[i]->freez_time=config[1];
            children[i]->current_stamina=children[i]->starting_stamina;
        }
       
}

void Game::CheckEidies(int i)
{
    if (static_map[children[i]->current_position.y][children[i]->current_position.x] == 'E')
    {
        children[i]->current_stamina += 5;
        static_map[children[i]->current_position.y][children[i]->current_position.x] = '.';
    }
}

void Game::LookForGhosts(int i)
{
    if (game_dynamic_map[children[i]->current_position.y][children[i]->current_position.x] == 'G')
    {
        children[i]->IsScared= true;
        children[i]->freez_time=5;
        return;
    }
    for (int j=0;j<4;j++)
    {
        cordinate tmp=neighourPosition(children[i]->current_position,j);
        if (game_dynamic_map[tmp.y][tmp.x] == 'G')
        {
            children[i]->IsScared = true;
            return;
        }
    }
}


void Game::checkState()
{
    for (int i = 0; i < children.size(); i++)
    {
        CheckStamina(i);
        CheckEidies(i);
        LookForGhosts(i);   
    }
}

void Game::createChildren(std::vector<std::string>map,std::vector<Child*> &children,std::vector <cordinate> destination_list,std::vector<int> children_stamina,cordinate home_position)
{
    for (int k=0;k<destination_list.size();k++)
    {
        Child* c= new Child(children_stamina[k],home_position,destination_list[k],k+'T');
        std::vector <cordinate> tmp_route;
        std::vector <int> tmp_address;
        findRoute(map,tmp_route,tmp_address,home_position,destination_list[k]);
        c->setRoute(tmp_route,tmp_address);
        children.push_back(c);
    }
}
#include "game.h"
//#include "pathfinder.h"

game::game(std::vector<std::string> &map,int initial_time,std::vector<int> children_stamina,int eidi_bonus)
{
    static_map=map;
    config.push_back(initial_time);
    config.push_back(eidi_bonus);
    
    // //config[1]
    // for (int i = 0; i < 7; i++)
    // {
    //     children[i].stamina=getChildInitialStamina(i);
    // }
}
void game::setHomePosition(int y, int x)
{
    home_position.x=x;
    home_position.y=y;
}
cordinate game::getHomePosition()
{   
    return home_position;
}
int game::getGameTime()
{
    return config[0];
}
void game::extractObjects()
{
    cordinate tmp;
    for (int y = 1; y < map_height-1; y++)
    {
        for (int x = 1; x < map_lenght -1; x++)
        {
            if (static_map[y][x] == 'G')
            {
                tmp.x = x;
                tmp.y = y;
                ghost* g= new ghost(tmp);
                ghosts.push_back(g);
                static_map[y][x] = '.';
            }
            else if (static_map[y][x] == 'H')
            {
                // std::cout<<x<<'\n';
                // std::cout<<y<<'\n';
                setHomePosition(y,x);
            }
            else 
            for(int i=1;i <= number_of_children;i++)
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
    }
}

void game::printmap()
{
    for (int y = 0; y < map_height; y++)
    {
        for (int x = 0; x < map_lenght; x++)
        {
            std::cout << game_dynamic_map[y][x];
        }
        std::cout << '\n';
    }
}
void game::updateTurn()
{
    game_dynamic_map = static_map; 
    for (int j=0;j< children.size();j++)
    {
        
        children[j]->makeMove(game_dynamic_map,static_map);
        std::cout<<children[j]->character_name<<":"<<children[j]->current_position.y<<" : "<<children[j]->current_position.x<<"\n";
        game_dynamic_map[children[j]->current_position.y][children[j]->current_position.x] =children[j]->character_name;
      //  std::cout<<"moving:"<<j<<" to "<<children[j]->current_position.x<<"and"<<children[j]->current_position.y<<'\n';

    }
    for (int i=0;i< ghosts.size();i++)
    {
        ghosts[i]->makeMove(game_dynamic_map);
        game_dynamic_map[ghosts[i]->current_position.y][ghosts[i]->current_position.x]='G';


    }
    
    //std::cin.get();
}
int game::remainingObjectives()
{
    int k = 0;
    for (int i = 0; i < children.size(); i++)
    {
        if (children[i]->IsAtHome)
        {
            k++;
        }
    }
    return 7 - k;
}

void game::checkState()
{
    for (int i = 0; i < children.size(); i++)
    {
        std::cout<<children[i]->character_name<<":"<<"1\n";
        if (children[i]->current_stamina <= 0)
        {
            children[i]->freez_time=config[1];
            children[i]->current_stamina=children[i]->starting_stamina;
        }
        std::cout<<"2\n";
        if (static_map[children[i]->current_position.y][children[i]->current_position.x] == 'E')
        {
            children[i]->current_stamina += 5;
            static_map[children[i]->current_position.y][children[i]->current_position.x] = '.';
        }
        std::cout<<"3\n";
        if (game_dynamic_map[children[i]->current_position.y][children[i]->current_position.x] == 'G')
        {
           
            children[i]->IsScared= true;
            children[i]->freez_time=5;
        }
        std::cout<<"4\n";
        if (game_dynamic_map[(children[i]->current_position.y) - 1][children[i]->current_position.x] == 'G' 
        || game_dynamic_map[(children[i]->current_position.y) + 1][children[i]->current_position.x] == 'G' 
        || game_dynamic_map[children[i]->current_position.y][(children[i]->current_position.x) - 1] == 'G' 
        || game_dynamic_map[children[i]->current_position.y][(children[i]->current_position.x) + 1] == 'G')
        {
             //std::cin.get();
            children[i]->IsScared = true;
        }
    }
}
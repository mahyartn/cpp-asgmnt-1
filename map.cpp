#include "map.h"

Map::Map(std::vector<std::string> map)
{
    static_map=map;
    game_dynamic_map=map;
    ExtractObjects();
    for (int i=0;i<g_number_of_children;i++)
    {
        std::vector <cordinate> tmp;
        routes[i]=findRoute(home_position,destination_list[i]);
    }
}

cordinate Map::getHomePosition()
{   
    return home_position;
}

void Map::CheckForPrizes(int x,int y)
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

void Map::CheckForGhosts(int x,int y)
{
    if (static_map[y][x] == 'G')
    {
        cordinate tmp;
        tmp.x = x;
        tmp.y = y;
        ghost_list.push_back(tmp);
        static_map[y][x] = '.';
    }
}

void Map::CheckForHome(int x,int y)
{
    if (static_map[y][x] == 'H')
        {
            cordinate tmp;
            tmp.y=y;
            tmp.x=x;
            home_position=tmp;
        }  
}

void Map::ExtractObjects()
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

void Map::PrintMap()
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

void Map::RefreshDynamicMap()
{
    game_dynamic_map=static_map;
}

char Map::GetDynamicChar(int x,int y)
{
    return  game_dynamic_map[y][x];
}

void Map::SetDynamicChar(int x,int y,char character)
{
    game_dynamic_map[y][x]=character;
}

void Map::SetStaticChar(int x,int y,char character)
{
    static_map[y][x]=character;
}
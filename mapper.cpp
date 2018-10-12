#include "mapper.h"


Mapper::Mapper(std::vector<std::string> &map)
{
    static_map=map;
    game_dynamic_map=map;
    ExtractObjects();
    for (int i=0;i<NUMBER_OF_CHILDREN;i++)
    {
        std::vector <cordinate> tmp;
        routes[i]=findRoute(home_position,destination_list[i]);
    }
}

cordinate Mapper::GetHomePosition()
{   
    return home_position;
}

void Mapper::CheckForPrizes(int x,int y)
{
    for(int i=1;i <= NUMBER_OF_CHILDREN;i++)
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

void Mapper::CheckForGhosts(int x,int y)
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

void Mapper::CheckForHome(int x,int y)
{
    if (static_map[y][x] == 'H')
        {
            cordinate tmp;
            tmp.y=y;
            tmp.x=x;
            home_position=tmp;
        }  
}

void Mapper::ExtractObjects()
{
    cordinate tmp;
    for (int y = 1; y < MAP_HEIGHT-1; y++)
    {
        for (int x = 1; x < MAP_LENGHT -1; x++)
        {
            CheckForGhosts(x,y);
            CheckForHome(x,y);
            CheckForPrizes(x,y);             
        }
    }
}

void Mapper::PrintMap()
{
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_LENGHT; x++)
        {
            std::cout << game_dynamic_map[y][x];
        }
        std::cout << '\n';
    }
}

void Mapper::RefreshDynamicMap()
{
    game_dynamic_map=static_map;
}

char Mapper::GetDynamicChar(int x,int y)
{
    return  game_dynamic_map[y][x];
}

char Mapper::GetStaticChar(int x,int y)
{
    return  static_map[y][x];
}

void Mapper::SetDynamicChar(int x,int y,char character)
{
    game_dynamic_map[y][x]=character;
}

void Mapper::SetStaticChar(int x,int y,char character)
{
    static_map[y][x]=character;
}

 std::vector <cordinate> Mapper::findRoute(cordinate home,cordinate destination)
 {
    cordinate tmp;
    std::vector<std::string> map=static_map;
    std::vector<cordinate> cordinates_queue;
    std::vector<cordinate> route;
    std::vector<int> cordinates_parents_adress;
    int counter=0;
    map[home.y][home.x] = 'O';
    cordinates_queue.push_back(home);
    cordinates_parents_adress.push_back(0);
    cordinate new_position;
    char m;
    bool breaker = true;
    while (breaker)
    {
        tmp.x = cordinates_queue[counter].x;
        tmp.y = cordinates_queue[counter].y;
        counter++;
        for (int j=0;j<4;j++)
        {
            new_position=NeighourPosition(tmp,j);
            m=map[new_position.y][new_position.x];
            if ( m != '#' && m != 'O') 
            {
                cordinates_queue.push_back(new_position);
                cordinates_parents_adress.push_back(counter);
                map[new_position.y][new_position.x] = 'O';
            }
            if (new_position==destination) 
            {
                std::cout<< "found!\n";
                std::cout<<destination.y<<" : "<<destination.x<<'\n';
                breaker=false;
                break;
            }
        }
    }
    int i = cordinates_queue.size();
    while(true)
    {
        route.push_back(cordinates_queue[i-1]);
        
        if (cordinates_queue[i-1]==home)
        {
            break; 
        }
        
        i=cordinates_parents_adress[i-1]; 
    }
    return route;
 }


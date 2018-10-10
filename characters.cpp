#include "characters.h"
#include <time.h>

child::child(int initial_stamina,cordinate home_position,cordinate destination_position,char name_character)
{
    character_name=name_character;
    IsHandFull = false;
    IsAtHome = false;
    wait = 0;
    IsScared = false;
    IsFreez = false;
    starting_stamina = initial_stamina;
    current_stamina = initial_stamina;
    home=home_position;
    destination=destination_position;
    current_position=home_position;
    
}

void child::setRoute(std::vector <cordinate> given_route,std::vector <int> address_list)
{
    int i = given_route.size();
    while(true)
    {
        route.push_back(given_route[i-1]);
        
        if (given_route[i-1]==home)
        {
            break; 
        }
        
        i=address_list[i-1]; 
    }
    iterator= route.size();
}

void child::makeMove (std::vector <std::string> &map,std::vector <std::string> &map2)
{
    if ( current_position==home)
    {
        IsScared = false;
        current_stamina = starting_stamina;
        if (IsHandFull)
        {
            IsAtHome = true;
        }
    }
    if (current_position==destination)
    {
        map2[current_position.y][current_position.x] ='.';
        IsHandFull=true;
    }
    if (IsAtHome)
    {
        return;
    }
    if (freez_time>0)
    {
        freez_time--;
        if (freez_time==0)
        {
           if (current_stamina == 0)
            {
                current_stamina = starting_stamina;
            } 
        }
        return;
    }
    if (IsScared)
    {
        iterator+=2;
    }
    else
    {
        if (IsHandFull)
        {
            iterator++;
        }
        else
        {
           iterator--;
        }
    }
    if (iterator>=route.size())
        {
            iterator=route.size()-1;
            IsScared=false;
        }
    if (iterator<0)
        {
            iterator=0;  
        }
    current_position=route[iterator]; 
    current_stamina--;
    
}

void child::showRoute()
{
    std::cout << character_name << "\n" ;
    for (int i=0;i< route.size();i++)
    {
        std::cout<<"x:"<<route[i].x<<"  y:"<<route[i].y<<'\n';
    }
    std::cin.get();
}

ghost::ghost(cordinate starting_postion)
{
    current_position=starting_postion;
}
void ghost::makeMove(std::vector <std::string> &map)
{
    int y_sequence[]={-1,0,1,0};
    int x_sequence[]={0,-1,0,1};
    int move=rand()%4;
    int move_x=x_sequence[move];
    int move_y=y_sequence[move];
    if (current_position.x==1 && move_x ==-1)
    {
        current_position.x+=1;
    }
    else if (current_position.x == map_lenght-2 && move_x == 1)
    {
        current_position.x-=1;        
    }
    else
    {
        current_position.x+=move_x;
    }
    if (current_position.y==1 && move_y ==-1)
    {
        current_position.y+=1;
    }
    else if (current_position.y == map_height-2 && move_y == 1)
    {
        current_position.y-=1;        
    }
    else
    {
        current_position.y+=move_y;
    }

}



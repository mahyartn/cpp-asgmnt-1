#include "characters.h"

Child::Child(int initial_stamina,cordinate home_position,std::vector <cordinate> given_route,char name_character)
{
    character_name=name_character;
    is_handFull = false;
    is_done = false;
    is_scared = false;
    starting_stamina = initial_stamina;
    current_stamina = initial_stamina;
    home=home_position;
    route=given_route;
    iterator=given_route.size();
    current_position=home_position;   
}



void Child::CheckIfHome()
{
    if ( current_position==home)
    {
        is_scared = false;
        current_stamina = starting_stamina;
        if (is_handFull)
        {
            is_done = true;
        }
    }
}

bool Child::CheckIfFrozen()
{
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
        return true;
    }
    return false;
}


void Child::IteratorLimiter()
{
    if (iterator>=route.size())
        {
            iterator=route.size()-1;
        }
    if (iterator<0)
        {
            iterator=0;  
        }
}

void Child::UpdateIterator()
{
    if (is_scared)
    {
        iterator+=2;
    }
    else
    {
        if (is_handFull)
        {
            iterator++;
        }
        else
        {
           iterator--;
        }
    }
}


void Child::MakeMove ()
{
    CheckIfHome();
    if (is_done) return;
    if (CheckIfFrozen()) return;
    UpdateIterator();
    IteratorLimiter(); 
    current_position=route[iterator]; 
    current_stamina--;
}

void Child::ShowRoute()
{
    std::cout << character_name << "\n" ;
    for (int i=0;i< route.size();i++)
    {
        std::cout<<"x:"<<route[i].x<<"  y:"<<route[i].y<<'\n';
    }
    std::cin.get();
}

void Child::CheckStamina()
{
    if (current_stamina <= 0)
        {
            freez_time=FREEZ_TIME;
            current_stamina=starting_stamina;
        }
       
}

void Child::CheckEidies(Mapper *map)
{
    if (map->GetStaticChar(current_position.x,current_position.y) == 'E')
    {
        current_stamina += 5;
        map->SetStaticChar(current_position.x,current_position.y,'.');
        map->SetDynamicChar(current_position.x,current_position.y,'.');
        
    }
}

void Child::CheckCyns(Mapper *map)
{
    if (current_position==route[0])
    {
        is_handFull=true;
        map->SetStaticChar(current_position.x,current_position.y,'.');
    }
}


void Child::LookForGhosts(Mapper *map)
{
    if (map->GetDynamicChar(current_position.x,current_position.y) == 'G')
    {
        is_scared= true;
        freez_time=5;
        return;
    }
    for (int j=0;j<4;j++)
    {
        cordinate tmp=NeighourPosition(current_position,j);
        if (map->GetDynamicChar(tmp.x,tmp.y) == 'G')
        {
            is_scared = true;
            return;
        }
    }
}

Ghost::Ghost(cordinate starting_postion)
{
    current_position=starting_postion;
}

void Ghost::MakeMove()
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
    else if (current_position.x == MAP_LENGHT-2 && move_x == 1)
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
    else if (current_position.y == MAP_HEIGHT-2 && move_y == 1)
    {
        current_position.y-=1;        
    }
    else
    {
        current_position.y+=move_y;
    }

}



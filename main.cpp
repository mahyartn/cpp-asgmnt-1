#include "game.h"
#include "characters.h"
#include "basic.h"
#include "pathfinder.h"

//router* find=new router;
//bool stat[4];

bool findRoute2(std::vector <std::string> &map,std::vector<cordinate*> &cordinates_queue,std::vector<int>  &cordinates_parents_adress,cordinate home,cordinate destination);

void printMap(std::vector <std::string> map)
{
    for (int y = 0; y < map_height; y++)
    {
        for (int x = 0; x < map_lenght; x++)
        {
            std::cout << map[y][x];
        }
        std::cout << '\n';
    }
}

bool findRoute2(std::vector <std::string> map,std::vector<cordinate> &cordinates_queue,std::vector<int>  &cordinates_parents_adress,cordinate home,cordinate destination)
{
    cordinate tmp;
    int counter=0;
    // std::cout<<"home:"<<home.x<<'\n';
    // std::cout<<"home:"<<home.y<<'\n';
    // std::cout<<"char:"<<map[home.y][home.x]<<'\n';
    map[home.y][home.x] = 'O';
    cordinates_queue.push_back(home);
    cordinates_parents_adress.push_back(0);
    cordinate new_position;
    char m;
    while (true)
    {
        tmp.x = cordinates_queue[counter].x;
        tmp.y = cordinates_queue[counter].y;
        counter++;
        // std::cout<<"posx:"<<tmp.x<<'\n';
        // std::cout<<"posy:"<<tmp.y<<'\n';
        // printMap(map);
        //std::cin.get();
        
        for (int j=0;j<4;j++)
        {
            new_position=neighourPosition(tmp,j);
            m=map[new_position.y][new_position.x];
            if ( m != '#' && m != 'O') 
            {
                cordinates_queue.push_back(new_position);
                cordinates_parents_adress.push_back(counter);
                map[new_position.y][new_position.x] = 'O';
                //std::cout <<"added"<<'\n';
            }
            if (new_position==destination) 
            {
                std::cout<< "found!\n";
                return true;
            }
        }
    }
}



void createChildren(std::vector<std::string>map,std::vector<child*> &children,std::vector <cordinate> destination_list,std::vector<int> children_stamina,cordinate home_position)
{
    for (int k=0;k<7/*destination_list.size()*/;k++)
    {
        child* c= new child(children_stamina[k],home_position,destination_list[k],k+'T');
        //std::cout<<"child number:"<<k+'T'<<'\n';
        std::vector <cordinate> tmp_route;
        std::vector <int> tmp_address;
        findRoute2(map,tmp_route,tmp_address,home_position,destination_list[k]);
        //std::cout<<"size:"<<address.size()<<'\n';
        c->setRoute(tmp_route,tmp_address);
        //c->showRoute();
        children.push_back(c);
        //std::cin.get();
    }
}
int main()
{
    
    srand(time(NULL));
    gameSetting game1;
    game1.loadMap();
    game1.loadConfig();
    game test(game1.static_map,game1.initial_time,game1.children_stamina,game1.eidi_bonus);
    test.extractObjects();
    createChildren(game1.static_map,test.children,test.destination_list,game1.children_stamina,test.getHomePosition());
    test.updateTurn();
    //std::cin.get();
    system("clear");
    test.printmap();
    std::cin.get();
    for (int i = 0; i <= test.getGameTime(); i++)
    {
    //     // test.updateChildren();
        test.checkState();
        //system("clear");
        test.updateTurn();
        test.printmap();
        //std::cin.get();
        std::cout << "Time remaining :" << (test.getGameTime() - i) << " Remaining Objectives:" << test.remainingObjectives() << '\n';
        usleep(200000);
    }
}

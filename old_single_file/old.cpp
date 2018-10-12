#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

struct cordinate
{
    int x;
    int y;
};
class child
{
  public:
    child();
    int stamina;
    int wait;
    bool IsFreez;
    bool IsScared;
    bool IsHandFull;
    bool IsAtHome;
    cordinate position;
};
child::child()
{
    IsHandFull = false;
    IsAtHome = false;
    wait = 0;
    IsScared = false;
    IsFreez = false;
    stamina = 10;
}
class gameSetting
{
public:
    std::vector<int> config;
    std::vector<std::string> static_map;
    void loadFiles();
};
void gameSetting::loadFiles()
{
    std::string line;
    char *line2;
    std::ifstream configFile("config.txt");
    if (configFile.is_open())
    {
        int cntr = 0;
        while (getline(configFile, line))
        {
            config.push_back(atoi(line.c_str()));
        }
        configFile.close();
    }
    else
        std::cout << "Unable to open file";

    std::ifstream mapFile("map.txt");
    if (mapFile.is_open())
    {
        static_map.push_back("#############################################################");
        while (getline(mapFile, line))
        {
            std::string tmp = "#" + std::string(line.c_str()) + "#";
            static_map.push_back(tmp);
        }
        static_map.push_back("##############################################################");
        for (int i = 0; i < 13; i++)
        {
            static_map[i][30] = '#';
        }
        mapFile.close();
        //std::cout << static_map[11].length();
    }
    else
        std::cout << "Unable to open file";
}


class game
{
  private:
    std::vector<int> config;
    std::vector<std::string> static_map;
    std::vector<std::string> game_dynamic_nap;
    std::vector<cordinate> routes[7];
    std::vector<cordinate>::iterator iterators[7];
    int objectList[8][2];
    std::vector<cordinate> ghostList;

    int ghostNum = 0;
    child nokhodies[7];

  public:
    game(std::vector<std::string> &map,std::vector<int> config);
    bool findPath(std::vector<std::string> &tmap, int number, int y, int x);
    void findAllPaths();
    void extractObjectCordinates();
    void printmap();
    void refreshGhosts();
    int getGameTime();
    int getChildInitialStamina(int num);
    void updateChildren();
    void checkState();
    int remainingObjectives();
    cordinate homePosition();
};
game::game(std::vector<std::string> &map,std::vector<int> conf)
{
    static_map=map;
    config=conf;
    for (int i = 0; i < 7; i++)
    {
        nokhodies[i].stamina=getChildInitialStamina(i);
    }
}
cordinate game::homePosition()
{
    cordinate temp;
    temp.x = objectList[0][1];
    temp.y = objectList[0][0];
    return temp;
}
int game::getGameTime()
{
    return config[0];
}
int game::getChildInitialStamina(int num)
{
    return config[num];
}
void game::extractObjectCordinates()
{
    cordinate tmp;
    for (int y = 1; y < 12; y++)
    {
        for (int x = 1; x < 30; x++)
        {
            //std::cout<<static_map[y][x];
            if (static_map[y][x] == 'G')
            {
                ghostNum++;
                tmp.x = x;
                tmp.y = y;
                ghostList.push_back(tmp);
                static_map[y][x] = '.';
            }
            else if (static_map[y][x] == 'H')
            {
                objectList[0][0] = y;
                objectList[0][1] = x;
                for (int i = 0; i < 7; i++)
                {
                    nokhodies[i].position.y = y;
                    nokhodies[i].position.x = x;
                }
            }
            else if (static_map[y][x] == '1')
            {
                objectList[1][0] = y;
                objectList[1][1] = x;
            }
            else if (static_map[y][x] == '2')
            {
                objectList[2][0] = y;
                objectList[2][1] = x;
            }
            else if (static_map[y][x] == '3')
            {
                objectList[3][0] = y;
                objectList[3][1] = x;
            }
            else if (static_map[y][x] == '4')
            {
                objectList[4][0] = y;
                objectList[4][1] = x;
            }
            else if (static_map[y][x] == '5')
            {
                objectList[5][0] = y;
                objectList[5][1] = x;
            }
            else if (static_map[y][x] == '6')
            {
                objectList[6][0] = y;
                objectList[6][1] = x;
            }
            else if (static_map[y][x] == '7')
            {
                objectList[7][0] = y;
                objectList[7][1] = x;
            }
        }
        //std::cout << '\n';
    }
    //std::cout << objectList[1][0]<< ":" << objectList [1][1];
    //std::cout <<ghostNum;
}
bool game::findPath(std::vector<std::string> &tmap, int number, int y, int x)
{
    cordinate tmp;
    bool found = 0;
    //std::cout<<"hummmm!!\n";
    if (tmap[y][x] == (number + 49))
    {
        //std::cout<<"found :"<< number+1 <<" : "<<y<<" "<<x<<'\n';
        found = true;
    }
    else if (tmap[y][x] != '#')
    {
        tmap[y][x] = '#';
        found = findPath(tmap, number, y - 1, x);
        if (!found)
            found = findPath(tmap, number, y, x - 1);
        if (!found)
            found = findPath(tmap, number, y + 1, x);
        if (!found)
            found = findPath(tmap, number, y, x + 1);
    }
    if (found)
    {
        tmp.x = x;
        tmp.y = y;
        routes[number].push_back(tmp);
    }
    return found;
}

void game::findAllPaths()
{
    for (int childNum = 0; childNum < 7; childNum++)
    {
        std::vector<std::string> tmpMap;
        tmpMap = static_map;
        findPath(tmpMap, childNum, nokhodies[childNum].position.y, nokhodies[childNum].position.x);
        iterators[childNum] = routes[childNum].end();
    }
}
void game::printmap()
{
    for (int y = 0; y < 13; y++)
    {
        for (int x = 0; x < 31; x++)
        {
            std::cout << game_dynamic_nap[y][x];
        }
        std::cout << '\n';
    }
}
void game::refreshGhosts()
{
    int move;
    game_dynamic_nap = static_map;
    for (int g = 0; g < ghostNum; g++)
    {
        move = rand() % 4;
        //std::cout << ghostList[g].y<<" : "<<ghostList[g].x<<"\n";
        game_dynamic_nap[ghostList[g].y][ghostList[g].x] = 'G';
        switch (move)
        {
        case 0:
            if ((ghostList[g].x - 1) > 1)
                ghostList[g].x -= 1;
            break;
        case 1:
            if ((ghostList[g].x + 1) < 28)
                ghostList[g].x += 1;
            break;
        case 2:
            if ((ghostList[g].y - 1) > 1)
                ghostList[g].y -= 1;
            break;
        case 3:
            if ((ghostList[g].y + 1) < 11)
                ghostList[g].y += 1;
            break;
        }
    }
}
int game::remainingObjectives()
{
    int k = 0;
    for (int i = 0; i < 7; i++)
    {
        if (nokhodies[i].IsAtHome)
        {
            k++;
        }
    }
    return 7 - k;
}
void game::updateChildren()
{
    for (int i = 0; i < 7; i++)
    {
        if (!nokhodies[i].IsAtHome)
        {
            game_dynamic_nap[nokhodies[i].position.y][nokhodies[i].position.x] = i + 84;
            if (nokhodies[i].wait == 5)
            {
                if (nokhodies[i].stamina == 0)
                {
                    nokhodies[i].stamina = getChildInitialStamina(i);
                }
                nokhodies[i].wait = 0;
                nokhodies[i].IsFreez = false;
            }
            if (nokhodies[i].IsFreez)
            {
                nokhodies[i].wait++;
            }
            else if (nokhodies[i].IsScared)
            {
                if (iterators[i] < ((routes[i].end()) - 1))
                {
                    iterators[i] += 2;
                    nokhodies[i].stamina -= 1;
                }
            }
            else
            {
                if (!nokhodies[i].IsHandFull)
                {
                    if (iterators[i] > routes[i].begin())
                    {
                        iterators[i]--;
                        nokhodies[i].stamina -= 1;
                    }
                }
                else
                {
                    if (iterators[i] < routes[i].end())
                    {
                        iterators[i]++;
                        nokhodies[i].stamina -= 1;
                    }
                }
            }
            if ((nokhodies[i].position.x == objectList[0][1]) && (nokhodies[i].position.y == objectList[0][0]))
            {
                if (nokhodies[i].IsHandFull)
                {
                    nokhodies[i].IsAtHome = true;
                }
                nokhodies[i].wait = 0;
                nokhodies[i].IsScared = false;
                nokhodies[i].stamina = getChildInitialStamina(i);
                nokhodies[i].IsFreez = false;
            }
            if (iterators[i] > routes[i].end())
            {
                iterators[i] = routes[i].end();
            }
            if (iterators[i] < routes[i].begin())
            {
                iterators[i] = routes[i].begin();
            }
            nokhodies[i].position.y = (*iterators[i]).y;
            nokhodies[i].position.x = (*iterators[i]).x;
            if (nokhodies[i].position.x == 0)
            {
                nokhodies[i].position.x = homePosition().x;
                nokhodies[i].position.y = homePosition().y;
            }
        }
    }
}
void game::checkState()
{
    for (int i = 0; i < 7; i++)
    {
        if (nokhodies[i].stamina == 0 && !nokhodies[i].IsFreez)
        {
            nokhodies[i].IsFreez = true;
            nokhodies[i].wait = 0;
        }

        if (static_map[nokhodies[i].position.y][nokhodies[i].position.x] == i + 49)
        {
            nokhodies[i].IsHandFull = true;
            static_map[nokhodies[i].position.y][nokhodies[i].position.x] = '.';
        }
        if (static_map[nokhodies[i].position.y][nokhodies[i].position.x] == 'E')
        {
            nokhodies[i].stamina += config[8];
            static_map[nokhodies[i].position.y][nokhodies[i].position.x] = '.';
        }
        if (game_dynamic_nap[nokhodies[i].position.y][nokhodies[i].position.x] == 'G')
        {
            nokhodies[i].IsFreez = true;
        }
        if (game_dynamic_nap[(nokhodies[i].position.y) - 1][nokhodies[i].position.x] == 'G' || game_dynamic_nap[(nokhodies[i].position.y) + 1][nokhodies[i].position.x] == 'G' || game_dynamic_nap[nokhodies[i].position.y][(nokhodies[i].position.x) - 1] == 'G' || game_dynamic_nap[nokhodies[i].position.y][(nokhodies[i].position.x) + 1] == 'G')
        {
            nokhodies[i].IsScared = true;
        }
    }
}
int main()
{
    srand(time(NULL));
    //std::cout << "test";
    gameSetting game1;
    game1.loadFiles();
    game test(game1.static_map,game1.config);
    test.extractObjectCordinates();
    test.findAllPaths();
    test.refreshGhosts();
    test.printmap();
    for (int i = 0; i <= test.getGameTime(); i++)
    {
        test.refreshGhosts();
        test.updateChildren();
        test.checkState();
        system("clear");
        test.printmap();
        std::cout << "Time remaining :" << (test.getGameTime() - i) << " Remaining Objectives:" << test.remainingObjectives() << '\n';
        usleep(100000);
    }
}

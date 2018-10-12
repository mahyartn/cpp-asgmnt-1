#include "basic.h"
//#include "mapper.h"


cordinate NeighourPosition(cordinate home,int neighbourNumber)
{
    int y_sequence[]={-1,0,1,0};
    int x_sequence[]={0,-1,0,1};
    cordinate tmp;
    tmp.y=home.y+y_sequence[neighbourNumber];
    tmp.x=home.x+x_sequence[neighbourNumber];
    return tmp;  
}


bool cordinate::operator==(cordinate subject) {
	return (x == subject.x && y == subject.y);
}

void gameSetting::LoadConfig()
{
    std::string line;
    char *line2;
    std::ifstream configFile("config.txt");
    if (configFile.is_open())
    {
       
        getline(configFile, line);
        initial_time= (atoi(line.c_str()));
        for (int i=0;i<NUMBER_OF_CHILDREN;i++)
        {
            getline(configFile, line);
            children_stamina.push_back(atoi(line.c_str()));
        }
        getline(configFile, line);
        eidi_bonus= (atoi(line.c_str()));
        configFile.close();
    }
    else
        std::cout << "Unable to open config file";

}
void gameSetting::LoadMap()
{
    std::string line;
    char *line2;
    
    std::ifstream mapFile("map.txt");
    if (mapFile.is_open())
    {
        while (getline(mapFile, line))
        {
            std::string tmp = std::string(line.c_str()) ;
            static_map.push_back(tmp);
            std::cout<<tmp<<"\n";
        }
        mapFile.close();
    }
    else
        std::cout << "Unable to open map file";
}


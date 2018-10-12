#include "game.h"
//#include "mapper.h"
#include "characters.h"
#include "basic.h"


int main()
{
    srand(time(NULL));
    gameSetting game_setting;
    game_setting.LoadMap();
    game_setting.LoadConfig();
    Game game(game_setting.static_map,game_setting.initial_time,game_setting.children_stamina,game_setting.eidi_bonus);
    
    game.CreateChildren(game.map->routes,game_setting.children_stamina,game.map->GetHomePosition());
    game.UpdateCharacters();
    system("clear");
    game.map->PrintMap();
    for (int i = 0; i <= game.GetGameTime(); i++)
    {
        game.CheckState();
        system("clear");
        game.UpdateCharacters();
        game.map->PrintMap();
        std::cout << "Time remaining :" << (game.GetGameTime() - i) << " Remaining Objectives:" << game.RemainingObjectives() << '\n';
        if (game.RemainingObjectives()== 0) break;
        usleep(200000);
    }
}

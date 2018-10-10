#include "game.h"
#include "characters.h"
#include "basic.h"


int main()
{
    srand(time(NULL));
    gameSetting game_setting;
    game_setting.loadMap();
    game_setting.loadConfig();
    Game game(game_setting.static_map,game_setting.initial_time,game_setting.children_stamina,game_setting.eidi_bonus);
    game.extractObjects();
    game.createChildren(game_setting.static_map,game.children,game.destination_list,game_setting.children_stamina,game.getHomePosition());
    game.UpdateCharacters();
    system("clear");
    game.printmap();
    for (int i = 0; i <= game.getGameTime(); i++)
    {
        game.checkState();
        system("clear");
        game.UpdateCharacters();
        game.printmap();
        std::cout << "Time remaining :" << (game.getGameTime() - i) << " Remaining Objectives:" << game.remainingObjectives() << '\n';
        if (game.remainingObjectives()== 0) break;
        usleep(200000);
    }
}

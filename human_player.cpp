// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "human_player.h"
#include <iostream>
#include "play_area.h"

//
// CPP course, task 2 - OX game
// (c) Oleksiy Svynchuk
//

namespace ox_game {

void human_player::do_step (PlayArea& area) {
    bool taken = false;
    int x, y;
    do {
        std::cout << "X:";
        std::cin >> x;
        std::cout << "Y:";
        std::cin >> y;

        taken = area.is_coord_taken(x, y);
        if (!taken) {
            area.set_value(x, y, m_own_cell_type);
            break;
        } else {
            std::cout << "This coord is incorrect or already taken. Try again." << std::endl;
        }
    } while (taken);
}

}

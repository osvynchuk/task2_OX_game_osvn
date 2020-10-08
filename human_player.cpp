// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "human_player.h"
#include <iostream>

//
// CPP course, task 2 - OX game
// (c) Oleksiy Svynchuk
//

namespace ox_game {

void human_player::do_step () {
    bool success = false;
    do {
        std::cout << "X:";
        std::cin >> m_x;
        std::cout << "Y:";
        std::cin >> m_y;
        success = set_coord(m_x, m_y);
        if (!success) std::cout << "This coord is incorrect or already taken. Try again." << std::endl;
    } while (!success);
}

}

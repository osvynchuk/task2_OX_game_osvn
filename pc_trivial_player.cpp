// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "pc_trivial_player.h"
#include <iostream>

//
// CPP course, task 2 - OX game
// (c) Oleksiy Svynchuk
//

namespace ox_game {

pc_trivial_player::pc_trivial_player(char cell_type) : player_base(cell_type) {
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    m_gen.seed(rd()); //Standard mersenne_twister_engine seeded with rd()
}

void pc_trivial_player::do_step (PlayArea& area) {
    bool taken = false;
    int x,y;
    do {
        x = distrib(m_gen);
        y = distrib(m_gen);

        taken = area.is_coord_taken(x, y);
        if (!taken) {
            area.set_value(x, y, m_own_cell_type);
            break;
        }
    }
    while (taken);
}

}

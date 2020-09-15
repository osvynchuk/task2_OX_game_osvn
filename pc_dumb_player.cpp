// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "pc_dumb_player.h"
#include <iostream>

namespace ox_game {

pc_dumb_player::pc_dumb_player() {
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    m_gen.seed(rd()); //Standard mersenne_twister_engine seeded with rd()
}

void pc_dumb_player::do_step () {
    do {
        m_x = distrib(m_gen);
        std::cout << "X:" << m_x << std::endl;
        m_y = distrib(m_gen);
        std::cout << "Y:" << m_y << std::endl;
    }
    while (!set_coord(m_x, m_y));
}

}

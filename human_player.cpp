// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "human_player.h"
#include <iostream>
#include <ncurses.h>
#include "play_area.h"

//
// CPP course, task 2 - OX game
// (c) Oleksiy Svynchuk
//

namespace ox_game {

void human_player::do_step (PlayArea& area) {

    while(1) {
        int c = wgetch(area.get_window());
        int cur_x, cur_y;
        getyx(area.get_window(), cur_y, cur_x);

        switch(c) {
            case KEY_UP:
                if (cur_y-1 < 2) cur_y++;
                wmove(area.get_window(), --cur_y, cur_x);
                break;
            case KEY_DOWN:
                 if (cur_y+1 == 5) cur_y--;
                 wmove(area.get_window(), ++cur_y, cur_x);
                break;

            case KEY_LEFT:
                if (cur_x-3 >= 4) cur_x -= 3;
                 wmove(area.get_window(), cur_y, cur_x);
                break;

            case KEY_RIGHT:
                if (cur_x+3 <= 10) cur_x += 3;
                wmove(area.get_window(), cur_y, cur_x);
                break;

            case ' ': {
                int x, y;
                getyx(area.get_window(), y, x);
                if (!area.is_coord_taken(x/3-1, y-2)) {
                    area.set_value(x/3-1, y-2, m_own_cell_type);
                    return;
                } else {
                    area.clear_info_str();
                    mvprintw(24, 0, "WARN: This coordinate is already taken!");
                    refresh();
                }
                break;
            }
            default:
                area.clear_info_str();
                mvprintw(24, 0, "Character pressed is not recognized");
                refresh();
                break;
        }
    }
}

}

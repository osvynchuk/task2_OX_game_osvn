#ifndef PLAYAREA_H
#define PLAYAREA_H
#include <iostream>
#include <array>
#include <memory>
#include <ncurses.h>
#include "player_base.h"

namespace ox_game {

class PlayArea {
public:
    static const int FieldRowSize = 3;
    PlayArea(std::unique_ptr<player_base>& player_1, std::unique_ptr<player_base>& player_2);
    ~PlayArea();
    void start_game();
    void set_value (int x, int y, char val) { m_area[FieldRowSize-y-1][x] = val; }
    char get_value (int x, int y) { return m_area[FieldRowSize-y-1][x]; }
    bool is_coord_taken(int x, int y) { return m_area[FieldRowSize-y-1][x] != ' '; }
    bool is_field_empty();
    WINDOW * get_window() { return  m_window_p; }
    void clear_info_str();

private:
    bool has_winner (char cell_type);
    bool has_winner ();
    void render();
    bool is_game_over();
private:
    std::array<std::array<char, FieldRowSize>, FieldRowSize> m_area;
    std::unique_ptr<player_base> m_player_1;
    std::unique_ptr<player_base> m_player_2;
    WINDOW *m_window_p = nullptr;
    static const int InfoMsgPositionY = 24;
    static  const int yMargin = 2;
    static const int xMargin = 3;
};

}

#endif // PLAYAREA_H

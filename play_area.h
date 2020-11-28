#ifndef PLAYAREA_H
#define PLAYAREA_H
#include <iostream>
#include <array>
#include <memory>
#include "player_base.h"

namespace ox_game {

class PlayArea {
public:
    static const int FieldRowSize = 3;
    PlayArea(std::unique_ptr<player_base>& player_1, std::unique_ptr<player_base>& player_2);
    void start_game();
    void set_value (int x, int y, char val) { m_area[FieldRowSize-y-1][x] = val; }
    char get_value (int x, int y) { return m_area[FieldRowSize-y-1][x]; }
    bool is_coord_taken(int x, int y) { return m_area[FieldRowSize-y-1][x] != '\0'; }
    bool is_field_empty();

private:
    bool has_winner (char cell_type);
    bool has_winner ();
    void render();
    bool is_game_over();

private:
    std::array<std::array<char, FieldRowSize>, FieldRowSize> m_area {'\0'};
    std::unique_ptr<player_base> m_player_1;
    std::unique_ptr<player_base> m_player_2;
};

}

#endif // PLAYAREA_H

// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "play_area.h"

//
// CPP course, task 2 - OX game
// (c) Oleksiy Svynchuk
//
namespace ox_game {

PlayArea::PlayArea(std::unique_ptr<player_base>& player_1, std::unique_ptr<player_base>& player_2):
 m_player_1(std::move(player_1)), m_player_2(std::move(player_2)) {
}

void PlayArea::start_game() {
    // Starting game
    while (!is_game_over()) {
        std::cout << "\n[Player 1] Do your Step:"<< std::endl;
        m_player_1->do_step(*this);
        render();

        if (has_winner(m_player_1->get_cell_type())) {
            std::cout << "Player 1 is winner!" << std::endl;
            break;
        }
        if (is_game_over()) break;

        std::cout << "\n[Player 2] Do your Step:"<< std::endl;
        m_player_2->do_step(*this);
        render();

        if (has_winner(m_player_2->get_cell_type())) {
            std::cout << "Player 2 is winner!" << std::endl;
            break;
        }
    }

    if (!has_winner()) std::cout << "\nNobody has won this time" << std::endl;
}

bool PlayArea::has_winner (char type) {

    auto scan_horizontally = [this, type] () {
        for (const auto& row: m_area) {
            bool res = true;
            for (const auto& entry: row) res = res && (entry == type);
            if (res) return true;
        }
        return false;
    };

    auto scan_vertically = [this, type] () {
        for (std::size_t j =0; j<FieldRowSize; ++j) {
            bool res = true;
            for (std::size_t i =0; i<FieldRowSize; ++i) {
                res = res && (m_area[i][j] == type);
            }
            if (res) return true;
        }
        return false;
    };

    auto scan_by_diagonal = [this, type] () {
        bool res = true;
        for (std::size_t j =0; j<FieldRowSize; ++j) {
            res = res && (m_area[j][j] == type);
        }
        if (res) return true;
        res = true;
        for (std::size_t j=0; j<FieldRowSize; ++j) {
            res = res && (m_area[FieldRowSize - 1 - j][j] == type);
        }
        return res;
    };

    return scan_horizontally() || scan_vertically() || scan_by_diagonal();
}

bool PlayArea::has_winner () {
    return has_winner('X') || has_winner('O');
}

void PlayArea::render() {
    for (std::size_t i =0; i<FieldRowSize; ++i) {
        for (std::size_t j =0; j<FieldRowSize; ++j) {
            std::cout << ((m_area[i][j] != '\0') ? m_area[i][j] : '_');
        }
        std::cout << std::endl;
    }
}

// Returns true if game is over
bool PlayArea::is_game_over () {
    for (const auto& row: m_area)
        for (const auto& entry: row) if (entry == '\0') return false;
    return true;
}

bool PlayArea::is_field_empty() {
    for (int i = 0; i<FieldRowSize; ++i){
        for (int j = 0; j<FieldRowSize; ++j){
            if (get_value(j,i) != '\0') return false;
        }
    }
    return true;
}

}

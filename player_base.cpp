// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "player_base.h"


//
// CPP course, task 2 - OX game
// (c) Oleksiy Svynchuk
//

namespace ox_game {

player_base::player_base() {
    for (auto& entries: m_coords)
        for (auto& entry: entries) entry = false;
}

bool player_base::set_coord(int x, int y) {
    if (can_set_coord(x, y) && m_opponent_p->can_set_coord(x, y)) {
        m_coords[FieldRowSize - y - 1][x] = true;
        return true;
    }
    return false;
}

bool player_base::can_set_coord(int x, int y) const {
    if (x < 0 || y < 0) return false;
    if (x >= FieldRowSize || y >= FieldRowSize) return false;
    return !m_coords[FieldRowSize - y - 1][x];
}

void player_base::set_opponent(const std::shared_ptr<player_base> opponent_p) {
    m_opponent_p = opponent_p;
}

bool player_base::is_winner() const {
    auto scan_horizontally = [] (const std::array<std::array<bool, FieldRowSize>, FieldRowSize>& coords) {
        for (const auto& entries: coords) {
            bool res = true;
            for (const auto& entry: entries) res = res && entry;
            if (res) return true;
        }
        return false;
    };

    auto scan_vertically = [] (const std::array<std::array<bool, FieldRowSize>, FieldRowSize>& coords) {
        for (std::size_t j =0; j<FieldRowSize; ++j) {
            bool res = true;
            for (std::size_t i =0; i<FieldRowSize; ++i) {
                res = res && coords[i][j];
            }
            if (res) return true;
        }
        return false;
    };

    auto scan_by_diagonal = [] (const std::array<std::array<bool, FieldRowSize>, FieldRowSize>& coords) {
        bool res = true;
        for (std::size_t j =0; j<FieldRowSize; ++j) {
            res = res && coords[j][j];
        }
        if (res) return true;
        res = true;
        for (std::size_t j=0; j<FieldRowSize; ++j) {
            res = res && coords[FieldRowSize - 1 - j][j];
        }
        return res;
    };

    return scan_horizontally(m_coords) || scan_vertically(m_coords) || scan_by_diagonal(m_coords);
}

const std::array<std::array<bool, FieldRowSize>, FieldRowSize>& player_base::get_coords() {
    return m_coords;
}


}

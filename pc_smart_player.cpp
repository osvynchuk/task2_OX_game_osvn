// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "pc_smart_player.h"
#include <iostream>

namespace ox_game {

// The logic below tires to prevent the opponent from winning
void pc_smart_player::do_step () {

    bool opp_not_empty = false;
    for (const auto& rows: m_opponent_p->get_coords()) {
        for (const auto& entry: rows) opp_not_empty = opp_not_empty || entry;
    }
    if (!opp_not_empty) {
        set_coord(FieldRowSize/2, FieldRowSize/2);
        return;
    }

    std::vector<int> cnt_by_rows;
    for (int y=FieldRowSize-1; y>=0; --y) {
        int cnt = 0;
        bool skip = false;
        for (auto& ownentry : m_coords[y]) if(ownentry) {skip = true; break;}
        if (!skip) {
            for (auto& entry : m_opponent_p->get_coords()[y]) {
                if(entry) cnt++;
            }
        }
        cnt_by_rows.push_back(cnt);
    }
    int max_row = 0;
    int max_row_cnt = -1;
    for (int i=0; i<cnt_by_rows.size(); ++i) {
        if (cnt_by_rows[i] > max_row_cnt) {
            max_row_cnt = cnt_by_rows[i];
            max_row = i;
        }
    }

    std::vector<int> cnt_by_columns;
    for (int i=0; i<FieldRowSize; ++i) {
        int cnt = 0;
        bool skip = false;
        for (int y=FieldRowSize-1; y>=0; --y) if (m_coords[y][i]) {skip=true; break;}
        if (!skip) {
            for (int y=FieldRowSize-1; y>=0; --y) {
                if (m_opponent_p->get_coords()[y][i]) cnt++;
            }
        }
        cnt_by_columns.push_back(cnt);
    }
    int max_column = 0;
    int max_col_cnt = -1;
    for (int i=0; i<cnt_by_columns.size(); ++i) {
        if (cnt_by_columns[i] > max_col_cnt) {
            max_col_cnt = cnt_by_columns[i];
            max_column = i;
        }
    }

    int fw_diag_cnt = -1;
    bool skip = false;
    for (int i=0; i<FieldRowSize; ++i)
        if (m_coords[FieldRowSize-1-i][i]) skip = true;

    if (!skip) {
        fw_diag_cnt=0;
        for (int i=0; i<FieldRowSize; ++i) {
            if (m_opponent_p->get_coords()[FieldRowSize-1-i][i]) fw_diag_cnt++;
        }
    }

    int bw_diag_cnt = -1;
    skip= false;
    for (int i=0; i<FieldRowSize; ++i)
        if (m_coords[i][i]) skip = true;

    if (!skip) {
        bw_diag_cnt=0;
        for (int i=0; i<FieldRowSize; ++i) {
            if (m_opponent_p->get_coords()[i][i]) bw_diag_cnt++;
        }
    }

    //std::cout << "+++++" << max_row_cnt << ", " << max_col_cnt << ", " << fw_diag_cnt<< ", " << bw_diag_cnt << std::endl;

    bool success = false;
    if (max_row_cnt >= max_col_cnt && max_row_cnt >= fw_diag_cnt && max_row_cnt >= bw_diag_cnt) {
        for (int x=0; x<FieldRowSize; ++x) {
            if(set_coord(x, max_row)) { success=true; break;}
        }
    } else if (max_col_cnt >= max_row_cnt && max_col_cnt >= fw_diag_cnt && max_col_cnt >= bw_diag_cnt) {
        for (int y=0; y<FieldRowSize; ++y) {
           if(set_coord(max_column, y)) { success=true; break;}
        }
    } else if (fw_diag_cnt >= max_row_cnt && fw_diag_cnt >= max_col_cnt && fw_diag_cnt >= bw_diag_cnt) {
        for (int i=0; i<FieldRowSize; ++i) {
            if(set_coord(i, i)) { success=true; break;}
        }
    } else if (bw_diag_cnt >= max_row_cnt && bw_diag_cnt >= max_col_cnt && bw_diag_cnt >= fw_diag_cnt) {
        for (int i=0; i<FieldRowSize; ++i) {
            if(set_coord(i, FieldRowSize-1-i)) { success=true; break;}
        }
    }
    else {
        std::cout << "WARN: unable to find right coord for next step!" << std::endl;
    }

    if (!success) {
        for (int y=0; y<FieldRowSize; ++y) {
            bool exit = false;
            for (int x=0; x<FieldRowSize; ++x) {
                if (set_coord(x,y)) {exit = true; break;}
            }
            if (exit) break;
        }
    }
}


}

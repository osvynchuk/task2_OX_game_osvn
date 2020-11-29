// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "pc_smart_player.h"
#include <iostream>

//
// CPP course, task 2 - OX game
// (c) Oleksiy Svynchuk
//
namespace ox_game {

pc_smart_player::pc_smart_player(char cell_type) : pc_trivial_player(cell_type) {
    m_opp_cell_type = (cell_type == 'X' ? 'O' : 'X');
}

void pc_smart_player::do_step (PlayArea& area) {

    // Do the first step
    if (area.is_field_empty()) {
        pc_trivial_player::do_step(area);
        return;
    }

    std::vector<int> cnt_by_rows; // <- count of entries taken by opponent in a row (aggregated for each row)
    for (int y=0; y<PlayArea::FieldRowSize; ++y) {
        int cnt = 0;
        for (int x=0; x<PlayArea::FieldRowSize; ++x) {
            if (area.get_value(x, y) == m_own_cell_type) {cnt = 0; break;}
            else if (area.get_value(x, y) == m_opp_cell_type) {
                cnt++;
            }
        }
        cnt_by_rows.push_back(cnt);
    }

    // find row with maximal count of entries taken by opponent
    int max_row = 0;
    int max_row_cnt = -1;
    for (int i=0; i<cnt_by_rows.size(); ++i) {
        if (cnt_by_rows[i] > max_row_cnt) {
            max_row_cnt = cnt_by_rows[i];
            max_row = i;
        }
    }

    std::vector<int> cnt_by_columns; // <- count of entries taken by opponent in a column (aggregated for each column)
    for (int x=0; x<PlayArea::FieldRowSize; ++x) {
        int cnt = 0;
        for (int y=0; y<PlayArea::FieldRowSize; ++y) {
            if (area.get_value(x, y) == m_own_cell_type) {cnt = 0; break;}
            else if (area.get_value(x, y) == m_opp_cell_type) {
                cnt++;
            }
        }
        cnt_by_columns.push_back(cnt);
    }

    // find column with maximal count of entries taken by opponent
    int max_column = 0;
    int max_col_cnt = -1;
    for (int i=0; i<cnt_by_columns.size(); ++i) {
        if (cnt_by_columns[i] > max_col_cnt) {
            max_col_cnt = cnt_by_columns[i];
            max_column = i;
        }
    }

    // count of entries taken by opponent in the forward diagonal
    int fw_diag_cnt = -1;
    bool skip = false;
    for (int y=0; y<PlayArea::FieldRowSize; ++y) {
        if (area.get_value(y, y) == m_own_cell_type) skip = true;
    }
    if (!skip) {
        fw_diag_cnt=0;
        for (int i=0; i<PlayArea::FieldRowSize; ++i) {
            if (area.get_value(i,i) == m_opp_cell_type) fw_diag_cnt++;
        }
    }

    // count of entries taken by opponent in the backward diagonal
    int bw_diag_cnt = -1;
    skip= false;
    for (int i=0; i<PlayArea::FieldRowSize; ++i)
        if (area.get_value(i, PlayArea::FieldRowSize - 1 - i) == m_own_cell_type) skip = true;

    if (!skip) {
        bw_diag_cnt=0;
        for (int i=0; i<PlayArea::FieldRowSize; ++i) {
            if (area.get_value(i, PlayArea::FieldRowSize - 1 - i) == m_opp_cell_type) bw_diag_cnt++;
        }
    }
    //std::cout << "+++++" << max_row_cnt << ", " << max_col_cnt << ", " << fw_diag_cnt<< ", " << bw_diag_cnt << std::endl;

    // Find the right coordinate for our next step, in order to block the opponent
    bool success = false;
    if (max_row_cnt >= max_col_cnt && max_row_cnt >= fw_diag_cnt && max_row_cnt >= bw_diag_cnt) {
        for (int x=0; x<PlayArea::FieldRowSize; ++x) {
            if(!area.is_coord_taken(x, max_row)) { area.set_value(x, max_row, m_own_cell_type); success=true; break;}
            //if(set_coord(x, max_row)) { success=true; break;}
        }
    } else if (max_col_cnt >= max_row_cnt && max_col_cnt >= fw_diag_cnt && max_col_cnt >= bw_diag_cnt) {
        for (int y=0; y<PlayArea::FieldRowSize; ++y) {
            if(!area.is_coord_taken(max_column, y)) { area.set_value(max_column, y, m_own_cell_type); success=true; break;}
           //if(set_coord(max_column, y)) { success=true; break;}
        }
    } else if (fw_diag_cnt >= max_row_cnt && fw_diag_cnt >= max_col_cnt && fw_diag_cnt >= bw_diag_cnt) {
        for (int i=0; i<PlayArea::FieldRowSize; ++i) {
            if(!area.is_coord_taken(i, i)) { area.set_value(i, i, m_own_cell_type); success=true; break;}
            //if(set_coord(i, i)) { success=true; break;}
        }
    } else if (bw_diag_cnt >= max_row_cnt && bw_diag_cnt >= max_col_cnt && bw_diag_cnt >= fw_diag_cnt) {
        for (int i=0; i<PlayArea::FieldRowSize; ++i) {
            if(!area.is_coord_taken(i, PlayArea::FieldRowSize-1-i)) { area.set_value(i, PlayArea::FieldRowSize-1-i, m_own_cell_type); success=true; break;}
            //if(set_coord(i, PlayArea::FieldRowSize-1-i)) { success=true; break;}
        }
    }
    else {
        std::cout << "WARN: unable to find right coord for the next step!" << std::endl;
    }

    if (!success) {
        for (int y=0; y<PlayArea::FieldRowSize; ++y) {
            for (int x=0; x<PlayArea::FieldRowSize; ++x) {
                if (!area.is_coord_taken(x,y) ) {area.set_value(x, y, m_own_cell_type); return;}
            }
        }
    }
}

}

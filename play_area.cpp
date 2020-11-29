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

    for(int i = 0; i < FieldRowSize; ++i) {
         for(int j = 0; j < FieldRowSize; ++j)  set_value(j, i, ' ');
    }
    initscr();
    clear();
    noecho();
    cbreak();	/* Line buffering disabled. pass on everything */
    int heigth = FieldRowSize + yMargin * 2;
    int width = FieldRowSize * 3 + xMargin * 2;

    m_window_p = newwin(heigth, width, (InfoMsgPositionY - heigth) / 2, (80 - width) / 2);  //newwin(HEIGHT, WIDTH, starty, startx);
    keypad(m_window_p, TRUE);
    refresh();
    // Move cursor to start position
    wmove(m_window_p, yMargin, xMargin +1);
    render();
}

PlayArea::~PlayArea() {
    clrtoeol();
    refresh();
    endwin();
}

void PlayArea::start_game() {
    int cur_x, cur_y;

    while (!is_game_over()) {
        getyx(m_window_p, cur_y, cur_x);
        clear_info_str();
        mvprintw(InfoMsgPositionY, 0, "[Player 1 - %c] Do your Step:", m_player_1->get_cell_type());
        wmove(m_window_p, cur_y, cur_x);
        refresh();
        m_player_1->do_step(*this);
        render();

        if (has_winner(m_player_1->get_cell_type())) {
            clear_info_str();
            mvprintw(InfoMsgPositionY, 0, "Player 1 is winner!\n");
            break;
        }
        if (is_game_over()) break;

        getyx(m_window_p, cur_y, cur_x);
        clear_info_str();
        mvprintw(InfoMsgPositionY, 0, "[Player 2 - %c] Do your Step:", m_player_2->get_cell_type());
        wmove(m_window_p, cur_y, cur_x);
        refresh();
        m_player_2->do_step(*this);
        render();

        if (has_winner(m_player_2->get_cell_type())) {
            clear_info_str();
            mvprintw(InfoMsgPositionY, 0, "Player 2 is winner!\n");
            break;
        }
    }

    if (!has_winner()) mvprintw(InfoMsgPositionY, 0, "Nobody has won this time\n");
    refresh();
    getch();
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
        int x = xMargin, y = yMargin;
        box(m_window_p, 0, 0);

        int cur_x, cur_y;
        getyx(m_window_p, cur_y, cur_x);

        for(int i = 0; i<FieldRowSize; ++i) {
             for(int j = 0; j<FieldRowSize; ++j) {
                mvwprintw(m_window_p, y+i, x+j*3, "[%c]", get_value(j, i));
             }
        }
        wmove(m_window_p, cur_y, cur_x);
        wrefresh(m_window_p);
}

// Returns true if game is over
bool PlayArea::is_game_over () {
    for (const auto& row: m_area)
        for (const auto& entry: row) if (entry == ' ') return false;
    return true;
}

bool PlayArea::is_field_empty() {
    for (int i = 0; i<FieldRowSize; ++i){
        for (int j = 0; j<FieldRowSize; ++j){
            if (get_value(j,i) != ' ') return false;
        }
    }
    return true;
}

void PlayArea::clear_info_str() {
    mvprintw(InfoMsgPositionY, 0, "                                                ");
}

}

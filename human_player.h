#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H
#include "player_base.h"

//
// CPP course, task 2 - OX game
// (c) Oleksiy Svynchuk
//

namespace ox_game {

class human_player : public player_base {
public:
    human_player(char cell_type) : player_base(cell_type) {};
    void do_step (PlayArea& area) override;
};

}
#endif // HUMAN_PLAYER_H

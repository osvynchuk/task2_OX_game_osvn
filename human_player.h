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
    human_player() = default;
    void do_step () override;
};

}
#endif // HUMAN_PLAYER_H

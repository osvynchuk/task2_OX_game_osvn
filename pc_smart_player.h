#ifndef PC_SMART_PLAYER_H
#define PC_SMART_PLAYER_H
#include "pc_trivial_player.h"

//
// CPP course, task 2 - OX game
// (c) Oleksiy Svynchuk
//

namespace ox_game {

//
// Smart player encapsulates more advanced algorithm
// than its base trivial player
//

class pc_smart_player : public pc_trivial_player
{
public:
    pc_smart_player(char cell_type);
    void do_step (PlayArea& area) override;
private:
    char m_opp_cell_type = '\0';
};

}

#endif // PC_SMART_PLAYER_H

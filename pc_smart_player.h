#ifndef PC_SMART_PLAYER_H
#define PC_SMART_PLAYER_H
#include "pc_dumb_player.h"

namespace ox_game {

class pc_smart_player : public pc_dumb_player
{
public:
    pc_smart_player() = default;
    void do_step () override;
};

}

#endif // PC_SMART_PLAYER_H

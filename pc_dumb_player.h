#ifndef PC_DUMB_PLAYER_H
#define PC_DUMB_PLAYER_H
#include "player_base.h"
#include <random>

namespace ox_game {

class pc_dumb_player : public player_base {
public:
    pc_dumb_player();
    void do_step () override;

private:
    std::mt19937 m_gen;
    std::uniform_int_distribution<> distrib {0,FieldRowSize-1};
};

}
#endif // PC_DUMB_PLAYER_H

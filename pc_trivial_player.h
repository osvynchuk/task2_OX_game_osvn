#ifndef PC_DUMB_PLAYER_H
#define PC_DUMB_PLAYER_H
#include "player_base.h"
#include <random>
#include "play_area.h"

//
// CPP course, task 2 - OX game
// (c) Oleksiy Svynchuk
//

namespace ox_game {

//
// Trivial player encapsulates simple algorithm
// based on random generatoio of a coordinate for the naxt step
//

class pc_trivial_player : public player_base {
public:
    pc_trivial_player(char cell_type);
    void do_step (PlayArea& area) override;

private:
    std::mt19937 m_gen;
    std::uniform_int_distribution<> distrib {0, PlayArea::FieldRowSize-1};
};

}
#endif // PC_DUMB_PLAYER_H

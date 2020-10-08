#ifndef PLAYER_FACTORY_H
#define PLAYER_FACTORY_H
#include "human_player.h"
#include "pc_trivial_player.h"
#include "pc_smart_player.h"
#include <memory>
#include <stdexcept>

//
// CPP course, task 2 - OX game
// (c) Oleksiy Svynchuk
//

namespace ox_game {

// Creates a concrete player and returns it
// as a pointer to the abstract player (sitting in the top of players hierarchy)

class player_factory
{
    player_factory() = delete;
    enum { HUMAN = 1, PC_DUMB, PC_SMART };
public:
    static std::shared_ptr<player_base> create(int palyer_type_id) {
        switch (palyer_type_id) {
        case HUMAN:
            return std::make_shared<human_player>();
        case PC_DUMB:
            return std::make_shared<pc_trivial_player>();
        case PC_SMART:
            return std::make_shared<pc_smart_player>();
        default:
            throw std::runtime_error("Invalid player id");
        }
    }
};

}

#endif // PLAYER_FACTORY_H

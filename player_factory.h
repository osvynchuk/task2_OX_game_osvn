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
    //static std::shared_ptr<player_base> create(int palyer_type_id, char cell_type) {
    static std::unique_ptr<player_base> create(int palyer_type_id, char cell_type) {
        switch (palyer_type_id) {
        case HUMAN:
            return std::make_unique<human_player>(cell_type);
        case PC_DUMB:
            return std::make_unique<pc_trivial_player>(cell_type);
        case PC_SMART:
            return std::make_unique<pc_smart_player>(cell_type);
        default:
            throw std::runtime_error("Invalid player id");
        }
    }
};

}

#endif // PLAYER_FACTORY_H

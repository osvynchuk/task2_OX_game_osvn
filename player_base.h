#ifndef IPLAYER_H
#define IPLAYER_H
#include <array>
#include "defines.h"
#include <memory>

//
// CPP course, task 2 - OX game
// (c) Oleksiy Svynchuk
//

namespace ox_game {

// Abstract player
//
// do_step() is a pure virtual method,
// which encapsulates specific behavior
// of any concrete player in our hierarchy

class player_base {
    friend class GameContext;
public:
    player_base();
    virtual ~player_base() = default;
    virtual void do_step () = 0;
    void set_opponent(const std::shared_ptr<player_base> opponent_p);
    bool is_winner() const;

    const std::array<std::array<bool, FieldRowSize>, FieldRowSize>& get_coords();
protected:
    bool set_coord(int x, int y);
    bool can_set_coord(int x, int y) const;
    int m_x = 0, m_y = 0;
    std::shared_ptr<player_base> m_opponent_p;
    std::array<std::array<bool, FieldRowSize>, FieldRowSize> m_coords;
};

}


#endif // IPLAYER_H

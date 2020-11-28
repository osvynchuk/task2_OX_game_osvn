#ifndef IPLAYER_H
#define IPLAYER_H
#include <array>
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

class PlayArea;

class player_base {
public:
    player_base(char cell_type);
    virtual ~player_base() = default;
    virtual void do_step (PlayArea& area) = 0;
    char get_cell_type() { return m_own_cell_type; }

protected:
    char m_own_cell_type;
};

}


#endif // IPLAYER_H

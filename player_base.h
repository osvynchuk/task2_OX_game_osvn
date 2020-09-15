#ifndef IPLAYER_H
#define IPLAYER_H
#include <array>
#include "defines.h"
#include <memory>

namespace ox_game {

class player_base {
public:
    player_base();
    virtual void do_step () = 0;
    virtual ~player_base() {}
    void set_opponent(const std::shared_ptr<player_base> opponent_p);
    bool is_winner() const;
    bool can_set_coord(int x, int y) const;
    const std::array<std::array<bool, FieldRowSize>, FieldRowSize>& get_coords();

protected:
    bool set_coord(int x, int y);
    int m_x = 0, m_y = 0;
    std::shared_ptr<player_base> m_opponent_p;
    std::array<std::array<bool, FieldRowSize>, FieldRowSize> m_coords;
};

}


#endif // IPLAYER_H

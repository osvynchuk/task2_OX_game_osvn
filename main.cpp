// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "player_factory.h"
#include <iostream>

//
// CPP course, task 2 - OX game
// (c) Oleksiy Svynchuk
//

namespace ox_game {

class GameContext {
public:
    GameContext(const GameContext&) = delete;
    GameContext& operator = (const GameContext&) = delete;
    GameContext(std::shared_ptr<player_base> pl1, std::shared_ptr<player_base> pl2)
        : m_player_1(pl1), m_player_2(pl2)  {
        m_player_1->set_opponent(m_player_2);
        m_player_2->set_opponent(m_player_1);
    }

    void run() {
        while (!is_over()) {
            std::cout << "\n[Player 1] Do your Step:"<< std::endl;
            m_player_1->do_step();
            render_area();
            if (m_player_1->is_winner()) {
                std::cout << "Player 1 is winner!" << std::endl;
                break;
            }
            if (is_over()) break;

            std::cout << "\n[Player 2] Do your Step:"<< std::endl;
            m_player_2->do_step();
            render_area();
            if (m_player_2->is_winner()) {
                std::cout << "Player 2 is winner!" << std::endl;
                break;
            }
        }

        if (!m_player_1->is_winner() && !m_player_2->is_winner()) std::cout << "Nobody has won this time" << std::endl;
    }

private:
    void render_area() {
        for (std::size_t i =0; i<FieldRowSize; ++i) {
            for (std::size_t j =0; j<FieldRowSize; ++j) {
                std::cout << (m_player_1->get_coords()[i][j] ? "X" : m_player_2->get_coords()[i][j] ? "O" : "_" );
            }
            std::cout << std::endl;
        }
    }

    // Returns true if game is over
    bool is_over () {
        int cnt = 0;
        for (auto& entries: m_player_1->get_coords())
            for (auto& entry: entries) if (entry) cnt++;
        for (auto& entries: m_player_2->get_coords())
            for (auto& entry: entries) if (entry) cnt++;
        return cnt == FieldRowSize * FieldRowSize;
    }

    std::shared_ptr<player_base> m_player_1;
    std::shared_ptr<player_base> m_player_2;
};
}

int main() {
    using namespace ox_game;
    std::cout << "OX Game, (c) Oleksiy Svynchuk" << std::endl;

    try {
        //
        // Creating players
        //

        int player_type = 0;
        std::cout << "Select first player [X] {1 - Human; 2 - PC_dumb; 3 - PC_smart}: ";
        std::cin >> player_type;
        if (!std::cin) throw std::invalid_argument("Incorrect input format");

        auto player1_p = player_factory::create(player_type);

        std::cout << "Select second player [O] {1 - Human; 2 - PC_dumb; 3 - PC_smart}: ";
        std::cin >> player_type;
        if (!std::cin) throw std::invalid_argument("Incorrect input format");

        auto player2_p = player_factory::create(player_type);

        //
        // Starting game
        //
        GameContext game(player1_p, player2_p);

        game.run();

    } catch(std::exception& ex) {
        std::cout << "Error occured: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}

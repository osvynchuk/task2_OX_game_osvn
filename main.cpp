// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "player_factory.h"
#include <iostream>

using namespace ox_game;
bool is_over (std::shared_ptr<player_base> pl1, std::shared_ptr<player_base> pl2);
void render(std::shared_ptr<player_base> pl1, std::shared_ptr<player_base> pl2);

int main() {
    try {
        std::cout << "OX Game, (c) Oleksiy Svynchuk" << std::endl;

        std::cout << "Select first player [X] {1 - Human; 2 - PC_dumb; 3 - PC_smart}: ";
        int player_type = 0;
        std::cin >> player_type;
        if (!std::cin) throw std::invalid_argument("Incorrect input format");
        auto player1_p = player_factory::create(player_type);

        std::cout << "Select second player [O] {1 - Human; 2 - PC_dumb; 3 - PC_smart}: ";
        std::cin >> player_type;
        if (!std::cin) throw std::invalid_argument("Incorrect input format");
        auto player2_p = player_factory::create(player_type);

        player1_p->set_opponent(player2_p);
        player2_p->set_opponent(player1_p);

        std::cout << "Starting game..." << std::endl;

        while (!is_over(player1_p, player2_p)) {
            std::cout << "\n[Player 1] Do your Step:"<< std::endl;
            player1_p->do_step();
            render(player1_p, player2_p);
            if (player1_p->is_winner()) {
                std::cout << "Player 1 is winner!" << std::endl;
                break;
            }
            if (is_over(player1_p, player2_p)) break;

            std::cout << "\n[Player 2] Do your Step:"<< std::endl;
            player2_p->do_step();
            render(player1_p, player2_p);
            if (player2_p->is_winner()) {
                std::cout << "Player 2 is winner!" << std::endl;
                break;
            }
        }

        if (!player1_p->is_winner() && !player2_p->is_winner()) std::cout << "Nobody has won this time" << std::endl;

    } catch(std::exception& ex) {
        std::cout << "Error occured: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}

// Renders the playing area
void render(std::shared_ptr<player_base> pl1, std::shared_ptr<player_base> pl2) {
    for (std::size_t i =0; i<FieldRowSize; ++i) {
        for (std::size_t j =0; j<FieldRowSize; ++j) {
            std::cout << (pl1->get_coords()[i][j] ? "X" : pl2->get_coords()[i][j] ? "O" : "_" );
        }
        std::cout << std::endl;
    }
}


// Returns true if game is over
bool is_over (std::shared_ptr<player_base> pl1, std::shared_ptr<player_base> pl2) {
    int cnt = 0;
    for (auto& entries: pl1->get_coords())
        for (auto& entry: entries) if (entry) cnt++;
    for (auto& entries: pl2->get_coords())
        for (auto& entry: entries) if (entry) cnt++;
    return cnt == FieldRowSize * FieldRowSize;
}

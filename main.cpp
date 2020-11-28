// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "player_factory.h"
#include <iostream>

//
// CPP course, task 2 - OX game
// (c) Oleksiy Svynchuk
//
int main() {
    using namespace ox_game;
    std::cout << "OX Game, (c) Oleksiy Svynchuk" << std::endl;

    try {
        //
        // Creating players
        //
        int player_type = 0;
        std::cout << "Select first player [X] {1 - Human; 2 - PC_trivial; 3 - PC_smart}: ";
        std::cin >> player_type;
        if (!std::cin) throw std::invalid_argument("Incorrect input format");
        auto player1_p = player_factory::create(player_type, 'X');

        std::cout << "Select second player [O] {1 - Human; 2 - PC_trivial; 3 - PC_smart}: ";
        std::cin >> player_type;
        if (!std::cin) throw std::invalid_argument("Incorrect input format");
        auto player2_p = player_factory::create(player_type, 'O');

        //
        // Creating playing area
        //
        PlayArea area(player1_p, player2_p);

        area.start_game();

    } catch(std::exception& ex) {
        std::cout << "Error occured: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}



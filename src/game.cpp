#include <array>
#include <iostream>

#include "game.h"

void Game::play() {
    std::pair<unsigned short, unsigned short> position;
    char move_sign = 'X';
    GameState state;

    for (;;) {
        print_field();
        
        // receiving position where user wants to go while until it will legal
        do {
            position = get_move_position();
        } while (get_sign(position) != ' ');

        make_move(position, move_sign);
        state = check_win(position);
        switch (state) {
            case X_WIN : x_win(); break;
            case O_WIN : o_win(); break;
            case DRAW : draw(); break;
            case UNKNOWN : break;
        }

        /*
         * swaps the players
         */
        if (move_sign == 'X') {
            move_sign = 'O';
        } else {
            move_sign = 'X';
        }
    }
}

void Game::print_field() {
    for (unsigned short i = 0; i < 3; ++i) {
        std::cout << '|';
        for (unsigned short j = 0; j < 3; ++j) {
            std::cout << get_sign(i, j);
            std::cout << '|';
        }
        std::cout << '\n';
    }
}

GameState Game::check_win(std::pair<unsigned short, unsigned short> moved_position) {
    GameState result = DRAW;
    bool win_state = false;

    /*
     * checks:
     * for horizontal line
     * for vertical line
     * for diagonal line
     */
    if (
            (get_sign(moved_position) == get_sign((moved_position.first + 1) % 3, moved_position.second) && get_sign(moved_position) == get_sign((moved_position.first + 2) % 3, moved_position.second)) ||
            (get_sign(moved_position) == get_sign(moved_position.first, (moved_position.second + 1) % 3) && get_sign(moved_position) == get_sign(moved_position.first, (moved_position.second + 2) % 3)) ||
            (get_sign(moved_position) == get_sign((moved_position.first + 1) % 3, (moved_position.second + 1) % 3) && get_sign(moved_position) == get_sign((moved_position.first + 2) % 3, (moved_position.second + 2) % 3))
       ) {
        win_state = true;
    }

    if (win_state) {
        if (get_sign(moved_position) == 'X') result = X_WIN;
        else result = O_WIN;
    } else {
        /*
         * checks if there is a blank field to continue the game
         */
        for (auto pos = field.begin(); pos != field.end(); ++pos) {
            if (*pos == ' ') {
                result = UNKNOWN;
                break;
            }
        }
    }

    return result;
}

std::pair<unsigned short, unsigned short> Game::get_move_position() {
    std::pair<unsigned short, unsigned short> coords;
    do {
        std::cout << "Enter the coords where you want to place your figure:" << std::endl;
        std::cin >> coords.first >> coords.second;
    } while (coords.first < 1 || coords.first > 4 || coords.second < 1 || coords.second > 4);

    coords.first -= 1;
    coords.second -= 1;

    return coords;
}

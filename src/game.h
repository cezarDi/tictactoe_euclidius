#include <array>
#include <iostream>

/*
 * State of the tame:
 * X_WIN - win of the first player
 * Y_WIN - win of the second player
 * DRAW - the field is full and nobody wins
 * UNKNOWN - the game is not ended yet
 */

enum GameState {
    X_WIN,
    O_WIN,
    DRAW,
    UNKNOWN,
};

class Game {
public:
    Game(): 
        field(std::array<char, 9>())
    {
        for (auto pos = field.begin(); pos != field.end(); ++pos) {
            *pos = ' ';
        }

        play();
    };

    char get_sign(std::pair<unsigned short, unsigned short> coords) {
        return field[coords.first * 3 + coords.second];
    }

    char get_sign(unsigned short x, unsigned short y) {
        return field[x * 3 + y];
    }

    void set_sign(std::pair<unsigned short, unsigned short> coords, char sign) {
        field[coords.first * 3 + coords.second] = sign;
    }


private:
    std::array<char, 9> field;

    void print_field() {
        for (unsigned short i = 0; i < 3; ++i) {
            std::cout << '|';
            for (unsigned short j = 0; j < 3; ++j) {
                std::cout << get_sign(i, j);
                std::cout << '|';
            }
            std::cout << '\n';
        }
    }

    void play() {
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

    //tmp
    void draw() {
        std::cout << "draw";
    }

    //tmp
    void o_win() {
        std::cout << "o win";
    }

    //tmp
    void x_win() {
        std::cout << "x win";
    }

    /*
     * Gets the pair (x, y) to move
     * 1 <= x, y <= 4
     */
    std::pair<unsigned short, unsigned short> get_move_position() {
        std::pair<unsigned short, unsigned short> coords;
        do {
            std::cout << "Enter the coords where you want to place your figure:" << std::endl;
            std::cin >> coords.first >> coords.second;
        } while (coords.first < 1 || coords.first > 4 || coords.second < 1 || coords.second > 4);

        coords.first -= 1;
        coords.second -= 1;

        return coords;
    }
    

    /*
     * field[postion] garantees to bee free
     */
    void make_move(std::pair<unsigned short, unsigned short>position, char move_sign) {
        set_sign(position, move_sign);
    }

    /*
     * checks the game state
     * moved_position used to optimise the checking
     */
    GameState check_win(std::pair<unsigned short, unsigned short> moved_position) {
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

};

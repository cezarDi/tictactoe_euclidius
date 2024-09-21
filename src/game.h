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
        play();
    };

private:
    std::array<char, 9> field;

    void print_field() {
        for (int i = 0; i < 3; ++i) {
            std::cout << '|';
            for (int j = 0; j < 3; ++j) {
                std::cout << field[i * 2 + j];
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
            position = get_move_position();
            make_move(position, move_sign);
            state = check_win();
            switch (state) {
                case X_WIN : x_win(); break;
                case O_WIN : o_win(); break;
                case DRAW : draw(); break;
                case UNKNOWN : continue;
            }
        }
    }

    void draw() {

    }

    void o_win() {

    }

    void x_win() {

    }

    std::pair<unsigned short, unsigned short> get_move_position() {

    }
    

    void make_move(std::pair<unsigned short, unsigned short>position, char move_sign) {

    }

    GameState check_win() {

    }

};

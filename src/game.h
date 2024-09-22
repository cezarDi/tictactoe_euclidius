#include <array>
#include <iostream>

/**
 * !!!
 * there is a bug: when u send string instead of a number everything falls
 */




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


    void print_field();
    void play();

    //tmp
    void draw() {
        std::cout << "draw" << '\n';
    }

    //tmp
    void o_win() {
        std::cout << "o win" << '\n';
    }

    //tmp
    void x_win() {
        std::cout << "x win" << '\n';
    }

    /*
     * Gets the pair (x, y) to move
     * 1 <= x, y <= 4
     */
    std::pair<unsigned short, unsigned short> get_move_position();
   

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
    GameState check_win(std::pair<unsigned short, unsigned short> moved_position);
};

#ifndef GIVEN_H
#define GIVEN_H

/*
 * This file contains a selection of the code that your colleagues have written
 * for your Pacman-project. It's just enough for you to finish your part of the
 * code.
 *
 * Tip: You may extend this file with things you need to make your program
 * compile. It's okay to extend Point with more operators if needed.
 */

#include <iostream>
#include <stdexcept>

/*
 * Global variables for the size of the game board.
 */
extern int WIDTH;
extern int HEIGHT;

/*
 * An aggregate used to represent points and directions on the game board. The
 * aggregate also have some helpful operators defined that may help you create
 * your implementation.
 */
struct Point {
    int x;
    int y;
};
bool operator==(Point const &lhs, Point const &rhs);
std::istream &operator>>(std::istream &is, Point &rhs);
//
Point operator+(Point const &lhs, Point const &rhs);
Point operator-(Point const &lhs, Point const &rhs);
Point operator*(Point const &lhs, int rhs);
//

/*
 * A class used to represent the player character. This is a down-scaled version
 * compared to what is in the actual game. Note that you code should not need
 * to be modified to work with the full Pacman-class.
 */
class Pacman {
  public:
    Pacman();

    Point get_position() const;
    void set_position(Point const &p);

    Point get_direction() const;
    void set_direction(Point const &p);

  private:
    Point pos{};
    Point dir{};
};

#endif

#ifndef GHOST_H
#define GHOST_H

#include "../given.h"
#include <string>

// Abstract Base Class
class Ghost {
  public:
    // Constructor required by game.cc
    Ghost(const Pacman &pacman, Point pos, Point scatter_target);

    virtual ~Ghost() = default;

    // Common Interface
    virtual Point get_chase_point() = 0;
    virtual Point get_scatter_point(); // Not pure virtual anymore, we can implement default here
    virtual std::string get_color() const = 0;

    void set_position(Point p);
    Point get_position() const;

  protected:
    // Store reference to Pacman so we can access position/direction later
    const Pacman &pacman_;
    Point position_;
    Point scatter_target_;
};

class Blinky : public Ghost {
  public:
    // Inherit constructor structure
    Blinky(const Pacman &pacman, Point pos, Point scatter_target);

    Point get_chase_point() override;
    Point get_scatter_point() override; // Blinky overrides to handle angry logic
    std::string get_color() const override;

    bool is_angry() const;
    void set_angry(bool angry);

  private:
    bool angry_{false};
};

class Pinky : public Ghost {
  public:
    Pinky(const Pacman &pacman, Point pos, Point scatter_target);

    Point get_chase_point() override;
    std::string get_color() const override;
};

class Clyde : public Ghost {
  public:
    // Clyde needs an extra argument for the distance threshold 'n'
    Clyde(const Pacman &pacman, Point pos, Point scatter_target, int n);

    Point get_chase_point() override;
    std::string get_color() const override;

  private:
    int n_;
};

#endif

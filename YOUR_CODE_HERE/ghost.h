#ifndef GHOST_H
#define GHOST_H

#include "given.h" // Provides Point and Pacman
#include <string>
#include <stdexcept>

// --- Abstract Base Class ---
class Ghost {
public:
    // Pacman is passed by const reference (polymorphism requirement) [cite: 354, 355]
    Ghost(const Pacman& pacman, Point pos, Point scatter_target);
    
    // Virtual destructor for inheritance [cite: 352]
    virtual ~Ghost() = default;

    // Interface methods (polymorphic) [cite: 253, 353]
    virtual Point get_chase_point() = 0;
    virtual Point get_scatter_point(); 
    virtual std::string get_color() const = 0;

    // Helper methods [cite: 259, 260]
    void set_position(Point p);
    Point get_position() const;

protected:
    const Pacman& pacman_; 
    Point position_;
    Point scatter_target_;
};

class Blinky : public Ghost {
public:
    Blinky(const Pacman& pacman, Point pos, Point scatter_target);

    Point get_chase_point() override;
    // Overrides scatter to check 'angry' status 
    Point get_scatter_point() override; 
    std::string get_color() const override;

    // Blinky-specific methods [cite: 261, 262]
    bool is_angry() const;
    void set_angry(bool angry);

private:
    bool angry_ {false};
};

class Pinky : public Ghost {
public:
    Pinky(const Pacman& pacman, Point pos, Point scatter_target);

    Point get_chase_point() override;
    std::string get_color() const override;
};

class Clyde : public Ghost {
public:
    // Requires special argument 'n' for distance threshold
    Clyde(const Pacman& pacman, Point pos, Point scatter_target, int n);

    Point get_chase_point() override;
    std::string get_color() const override;

private:
    int n_;
};

#endif
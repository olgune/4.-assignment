#include "ghost.h"
#include <cmath>
#include <algorithm>

// --- Ghost Base Class Implementation ---
Ghost::Ghost(const Pacman& pacman, Point pos, Point scatter_target)
    : pacman_(pacman), position_(pos), scatter_target_(scatter_target) 
{}

void Ghost::set_position(Point p) {
    // The simplified Pacman class already validates the position, but we can do a quick check
    if (p.x < 0 || p.y < 0 || p.x >= WIDTH || p.y >= HEIGHT) {
         throw std::runtime_error("ghost position outside valid range");
    }
    position_ = p;
}

Point Ghost::get_position() const {
    return position_;
}

// Default scatter point for all ghosts is their predetermined corner
Point Ghost::get_scatter_point() {
    return scatter_target_;
}

// --- Blinky Implementation (Red) ---
Blinky::Blinky(const Pacman& pacman, Point pos, Point scatter_target)
    : Ghost(pacman, pos, scatter_target) 
{}

Point Blinky::get_chase_point() {
    // Target: Pacman's position 
    return pacman_.get_position();
}

Point Blinky::get_scatter_point() {
    // Target: Scatter point, OR chase point if angry 
    if (angry_) {
        return get_chase_point();
    }
    return scatter_target_;
}

std::string Blinky::get_color() const {
    return "red"; // 
}

bool Blinky::is_angry() const {
    return angry_;
}

void Blinky::set_angry(bool angry) {
    angry_ = angry;
}

// --- Pinky Implementation (Pink) ---
Pinky::Pinky(const Pacman& pacman, Point pos, Point scatter_target)
    : Ghost(pacman, pos, scatter_target) 
{}

Point Pinky::get_chase_point() {
    // Target: Two steps in front of Pacman 
    Point target = pacman_.get_position() + (pacman_.get_direction() * 2);
    return target;
}

std::string Pinky::get_color() const {
    return "pink"; // 
}

// --- Clyde Implementation (Orange) ---
Clyde::Clyde(const Pacman& pacman, Point pos, Point scatter_target, int n)
    : Ghost(pacman, pos, scatter_target), n_(n) 
{}

Point Clyde::get_chase_point() {
    Point pac_pos = pacman_.get_position();
    
    // Calculate distance (Euclidean distance: sqrt(dx^2 + dy^2))
    int dx = pac_pos.x - position_.x;
    int dy = pac_pos.y - position_.y;
    double distance = std::sqrt(dx*dx + dy*dy);

    // If far away (> n), chase Pacman. If close (<= n), scatter. 
    if (distance > n_) {
        return pac_pos;
    } else {
        return scatter_target_;
    }
}

std::string Clyde::get_color() const {
    return "orange"; // 
}
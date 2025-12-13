#include "ghost.h"
#include <cmath>

// --- Ghost Base Class ---
Ghost::Ghost(const Pacman &pacman, Point pos, Point scatter_target)
    : pacman_(pacman), position_(pos), scatter_target_(scatter_target) {
}

void Ghost::set_position(Point p) {
    position_ = p;
}

Point Ghost::get_position() const {
    return position_;
}

// Default scatter behavior: return the target stored in constructor
Point Ghost::get_scatter_point() {
    return scatter_target_;
}

// --- Blinky ---
Blinky::Blinky(const Pacman &pacman, Point pos, Point scatter_target)
    : Ghost(pacman, pos, scatter_target) {
}

Point Blinky::get_chase_point() {
    // Blinky chases Pacman directly
    return pacman_.get_position();
}

Point Blinky::get_scatter_point() {
    // If angry, behavior changes to chase target
    if (angry_) {
        return get_chase_point();
    }
    return scatter_target_;
}

std::string Blinky::get_color() const {
    return "red";
}

bool Blinky::is_angry() const {
    return angry_;
}

void Blinky::set_angry(bool angry) {
    angry_ = angry;
}

// --- Pinky ---
Pinky::Pinky(const Pacman &pacman, Point pos, Point scatter_target)
    : Ghost(pacman, pos, scatter_target) {
}

Point Pinky::get_chase_point() {
    // Target: 2 steps in front of Pacman
    Point target = pacman_.get_position() + (pacman_.get_direction() * 2);
    return target;
}

std::string Pinky::get_color() const {
    return "pink";
}

// --- Clyde ---
Clyde::Clyde(const Pacman &pacman, Point pos, Point scatter_target, int n)
    : Ghost(pacman, pos, scatter_target), n_(n) {
}

Point Clyde::get_chase_point() {
    Point pac_pos = pacman_.get_position();

    // Distance check
    int dx = pac_pos.x - position_.x;
    int dy = pac_pos.y - position_.y;
    double distance = std::sqrt(dx * dx + dy * dy);

    // If far away (> n), chase Pacman. If close, scatter.
    if (distance > n_) {
        return pac_pos;
    } else {
        return scatter_target_; // Use stored scatter target
    }
}

std::string Clyde::get_color() const {
    return "orange";
}

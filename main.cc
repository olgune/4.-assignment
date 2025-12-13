#include "YOUR_CODE_HERE/ghost.h"
#include <algorithm> // for toupper
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Ghost_Tester {
  public:
    Ghost_Tester()
        : pacman{} {
        // Initialize ghosts with: (pacman_ref, start_pos, scatter_target)
        // We match the targets from the table/game instructions

        // Blinky: Scatter Top Right (WIDTH-1, HEIGHT-1)
        ghosts.push_back(new Blinky(pacman, {8, 8}, {WIDTH - 1, HEIGHT - 1}));

        // Pinky: Scatter Top Left (0, HEIGHT-1)
        ghosts.push_back(new Pinky(pacman, {2, 7}, {0, HEIGHT - 1}));

        // Clyde: Scatter Bottom Left (0, 0), n=8 (as per game.cc)
        ghosts.push_back(new Clyde(pacman, {4, 2}, {0, 0}, 8));
    }

    ~Ghost_Tester() {
        for (auto g : ghosts)
            delete g;
    }

    void run() {
        while (true) {
            draw_map();
            cout << "> ";

            string line{};
            getline(cin, line);
            istringstream iss{line};

            string command{};
            iss >> command;

            if (command == "pos") {
                Point new_pos{};
                iss >> new_pos.x >> new_pos.y;
                try {
                    pacman.set_position(new_pos);
                } catch (...) {
                }
            } else if (command == "dir") {
                Point new_dir{};
                iss >> new_dir.x >> new_dir.y;
                try {
                    pacman.set_direction(new_dir);
                } catch (...) {
                }
            } else if (command == "chase") {
                current_state = "chase";
            } else if (command == "scatter") {
                current_state = "scatter";
            } else if (command == "anger") {
                for (auto g : ghosts) {
                    if (auto b = dynamic_cast<Blinky *>(g))
                        b->set_angry(true);
                }
            } else if (command == "quit") {
                break;
            } else {
                // Move specific ghost: <color> <x> <y>
                for (auto g : ghosts) {
                    if (g->get_color() == command) {
                        Point p;
                        if (iss >> p.x >> p.y)
                            g->set_position(p);
                    }
                }
            }
        }
    }

  private:
    Pacman pacman;
    vector<Ghost *> ghosts;
    string current_state = "chase";

    string to_draw(Point const &curr_pos) {
        string to_draw{"  "};

        // 1. Draw Player
        if (pacman.get_position() == curr_pos)
            to_draw[1] = '@';

        // 2. Draw Ghosts and Targets
        for (auto g : ghosts) {
            // Draw Ghost (Uppercase first letter)
            if (g->get_position() == curr_pos) {
                to_draw[0] = toupper(g->get_color()[0]);
            }

            // Calculate Target
            Point target;
            if (current_state == "chase")
                target = g->get_chase_point();
            else
                target = g->get_scatter_point();

            // Draw Target (Lowercase first letter) if slot is empty
            if (target == curr_pos) {
                char t = tolower(g->get_color()[0]);
                if (to_draw[0] == ' ')
                    to_draw[0] = t;
                else if (to_draw[1] == ' ')
                    to_draw[1] = t;
            }
        }
        return to_draw;
    }

    void draw_map() {
        cout << "+" << setfill('-') << setw(WIDTH * 2) << "-" << "+\n";
        for (int y{HEIGHT - 1}; y >= 0; --y) {
            cout << "|";
            for (int x{}; x < WIDTH; ++x)
                cout << to_draw(Point{x, y});
            cout << "|\n";
        }
        cout << "+" << setfill('-') << setw(WIDTH * 2) << "-" << "+" << endl;
    }
};

int main() {
    Ghost_Tester gt{};
    gt.run();
    return 0;
}


#include <SFML/Graphics.hpp>
#include <iostream>

#include "game.h" 

using namespace std;

int main()
{
    cout << "Weclome to Pacman!\nPress 'Enter' to start";
    cin.get();

    Game game {};
    game.run();

    cout << "You got " << game.get_score() << " points" << std::endl;
    cout << "Press 'Enter' to quit" << std::endl;
    cin.get();
}

#include <cstdio>
#include <vector>
#include <SFML/Graphics.hpp>



sf::RenderWindow Init(int width, int height, char *title) {
    sf::RenderWindow window(sf::VideoMode(width, height), title);
    return window;
}

void Update(sf::RenderWindow window) {

}


int main()
{

    if (!sf::RenderWindow window = Init()) return 1;

    while(window.isOpen) {

    }
    return 0;
}

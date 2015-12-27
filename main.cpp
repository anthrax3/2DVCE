/**
    Copyright 2015 Ricky LeDew

    This file is part of 2DVCE.

    2DVCE is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    2DVCE is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with 2DVCE.  If not, see <http://www.gnu.org/licenses/>.
**/
#include <cstdio>
#include <vector>
#include <SFML/Graphics.hpp>
#include <ctime>
#include "objects.h"
#include "config.h"
Clock c(3)
Dynamic n1(0,0,Bounds(Point(-1,-1),Point(1,1)),0.5,10);
Dynamic n2(6,6,Bounds(Point(5,5),Point(7,7)),0.5,10);
Muscle m(n1,n2,0.5,1,0.5,0.5,c)
void Update(sf::RenderWindow &window) {
m.update();
n1.update();
n2.update();
}

void Event(sf::RenderWindow &window) {
    sf::Event e;
    while (window.pollEvent(e)) {
        if(e.type == sf::Event::Closed) {
            window.close();
        }
    }
}

void Render(sf::RenderWindow &window) {
    window.clear(sf::Color::Black);
    //Draw stuff here
    window.display();

}

int main() {
    sf::RenderWindow window(sf::VideoMode(GAME_WIDTH, GAME_HEIGHT), GAME_TITLE);
    while(window.isOpen()) {
        Update(window);
        Event(window);
        Render(window);
        //wait for a bit
        clock_t temp;
        temp = clock () + CLOCKS_PER_SEC/GAME_FPS;
        while (clock() < temp) {}
    }
    return 0;
}

/**
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
#ifndef OBJECTS_H_INCLUDED
#define OBJECTS_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <cmath>
#include <random>
#include "config.h"

class Point {
    public:
        float x;
        float y;
        Point(float x, float y) {
            this->x = x;
            this->y = y;
        }
};

class Bounds {
    public:
        Point min;
        Point max;
        Bounds(Point min, Point max) {
            this->min = min;
            this->max = max;
        }

};
class Object {
    private:
        Point offset_min;
        Point offset_max;
    public:
        Point pos;
        Bounds bounds;
        Object(Point pos, Bounds bounds) {
            this->pos = pos;
            this->bounds = bounds;
            this->offset_min = Point(bounds.min.x - pos.x, bounds.min.y - pos.y);
            this->offset_min = Point(bounds.max.x - pos.x, bounds.max.y - pos.y);
        }
        void updateBounds() {
            bounds = Bounds(pos + offset_min, pos + offset_max);
        }


};

//TODO add static objects

class Dynamic : Object {
    public:
        Dynamic(float x, float y, Bounds bounds, float friction, float mass) : Object(x, y, bounds){
        }
        float friction;
        float mass;
        struct vel {
            float magnitude;
            float angle;
        };

        int collide(Object o) {
            if (o.bounds.max.x >= bounds.min.x && o.bounds.min.x <= bounds.max.x &&
            o.bounds.max.y >= bounds.min.y && o.bounds.min.y <= bounds.max.y) {
                return 1;
            } else {
                return 0;
            }
        }

        void applyForce(float magnitude, float angle) {
            //Oh god why did i even try to make this
            float x = magnitude * std::cos(angle);
            float y = magnitude * std::sin(angle);
            float thisx = vel.magnitude * std::cos(vel.angle);
            float thisy = vel.magnitude * std::sin(vel.angle);
            float rx = x + thisx;
            float ry = y + thisy;
            vel.magnitude += std::sqrt(std::pow(rx, 2) + std::pow(ry, 2));
            vel.angle += std::atan2(ry, rx);
        }

        void update() {
            pos.x += (vel.magnitude * std:cos(vel.angle))/GAME_FPS
            pos.y += (vel.magnitude * std:sin(vel.angle))/GAME_FPS
            updateBounds();
        }
};

class Clock {
    public:
        float length;
        float tick;
        Clock(float _length) {
            length = std::floor(GAME_FPS*_length)/GAME_FPS;

        }
        void setclock() {
            tick = 0;
        }
        void tick() {
            if(tick<length)
                tick+=(1/GAME_FPS)
            else
                setclock();
        }
};

class Muscle {
    public:
        Dynamic n1; // First node, i tink iz supposd 2 hav lower valu on x/y coords... i tiinnkkk
        Dynamic n2; // Second node, honestly i dont know :/
        float strength; // 0 = No strength // 1 = Will extend/contract completly in 1 second // -1 = Problems // 89147209370479 = God help you if you do this.
        float length; // Current length
        float contracted; // Contracted target length
        float extended; // Extended target length
        float ctdtime; // Expressed as a fractional amount. ie if the length of the clock was 2 seconds and this was 0.25, it would contract at 0.5 seconds.
        float exttime;
        int phase; //0 = Contracting; 1 = Extending
        float angle; // Angle of the muscle
        Clock clock;
        Muscle(Dynamic _n1, Dynamic _n2, float _strength, int _phase, float _ctdtime, float _exttime, Clock _clock) {
            n1 = node1;
            n2 = node2;
            strength = std::floor(GAME_FPS*_strength)/GAME_FPS
            length = std::sqrt(std::pow(n2.pos.x - n1.pos.x, 2) + std::pow(n2.pos.y - n1.pos.y, 2));
            angle = std::atan2(n2.pos.y - n1.pos.y, n2.pos.x - n1.pos.x);
            clock = _clock;
            ctdtime = _ctdtime;
            exttime = _exttime;
        }

        void contract() {
            if (length > contracted && phase == 0) {
                n1.applyForce(strength*std::cos(angle), strength*std::sin(angle));
                n2.applyForce(-(strength*std::cos(angle)), -(strength*std::sin(angle)));
            }
            length = std::sqrt(std::pow(n2.pos.x - n1.pos.x, 2 + std::pow(n2.pos.y - n1.pos.y, 2));
        }
        void extend() {
            if (length > extended && phase == 1) {
                n1.applyForce(-(strength*std::cos(angle)), -(strength*std::sin(angle)));
                n2.applyForce(strength*std::cos(angle), strength*std::sin(angle));
            }
            length = std::sqrt(std::pow(n2.pos.x - n1.pos.x, 2) + std::pow(n2.pos.y - n1.pos.y, 2));
        }

        void Update() {
            if(clock.tick == clock.length*ctdtime)
                phase = 0;
            else if (clock.tick == clock.length*ctdtime)
                phase = 1;
            clock.tick();
            contract();
            extend();
        }
};

//TODO add muscles I DID NOW GO AWAY
//oh... i cant get rid of it by telling it to go?
//meh, i'm too busy to get rid of it right now *leaves it forever*

#endif // OBJECTS_H_INCLUDED

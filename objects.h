#ifndef OBJECTS_H_INCLUDED
#define OBJECTS_H_INCLUDED
#include <SFML/Graphics.hpp>
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
            float x;
            float y;
        };

        int collide(Object o) {
            if (o.bounds.max.x >= bounds.min.x && o.bounds.min.x <= bounds.max.x &&
            o.bounds.max.y >= bounds.min.y && o.bounds.min.y <= bounds.max.y) {
                return 1;
            } else {
                return 0;
            }
        }


};

//TODO add muscles

#endif // OBJECTS_H_INCLUDED

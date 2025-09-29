#include "object.hpp"

Object::Object() : Object(-1, 0, 0, 0) {};

Object::Object(int _id, double _x, double _y, double _width) : id(_id), x(_x), y(_y), width(_width) {};

int Object::get_id(){
    return id;
}

double Object::get_y() {
    return y;
}

double Object::get_max_x() {
    return x + width/2;
}

double Object::get_min_x() {
    return x - width/2;
}

double Object::get_width() {
    return width;
}

void Object::move(double newX, double newY) {
    x = newX;
    y = newY;
}

bool Object::operator < (const Object& otherObject) const{
    if(y < otherObject.y)
        return true;
    else if(y == otherObject.y){
        if((x - width/2) < (otherObject.x - otherObject.width/2))
            return true;
        else if((x - width/2) == (otherObject.x - otherObject.width/2))
            return id < otherObject.id;
        else
            return false;
    }
    else
        return false;
}

bool Object::operator > (const Object& otherObject) const{
    if(y > otherObject.y)
        return true;
    else if(y == otherObject.y){
        if((x - width/2) > (otherObject.x - otherObject.width/2))
            return true;
        else if((x - width/2) == (otherObject.x - otherObject.width/2))
            return id > otherObject.id;
        else
            return false;
    }
    else
        return false;
}

bool Object::intersects_interval(double min, double max) {
    double minX = x - width/2;
    double maxX = x + width/2;

    if((min < minX && minX < max) || (min < maxX && maxX < max) || (minX < min && min < maxX) || (minX < max && max < maxX))
        return true;

    return false;
}

bool Object::is_inside(double min, double max){
    double minX = x - width/2;
    double maxX = x + width/2;

    if(min < minX && maxX < max)
        return true;

    return false;
}
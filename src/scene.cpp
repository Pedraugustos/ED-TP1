#include "scene.hpp"

Scene::Scene() : Scene(-1, 0, 0, 0) {};

Scene::Scene(int _time, int _objectId, double _posX, double _posY) : time(_time), objectId(_objectId), posX(_posX), posY(_posY) {};

int Scene::get_time() {
    return time;
}

int Scene::get_objectId() {
    return objectId;
}

double Scene::get_posX() {
    return posX;
}

double Scene::get_posY() {
    return posY;
}
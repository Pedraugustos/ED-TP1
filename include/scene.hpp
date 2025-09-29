#ifndef SCENE_HPP
#define SCENE_HPP

using namespace std;

class Scene {
    private:
        int time;
        int objectId;
        double posX, posY;

    public:
        Scene();
        Scene(int, int, double, double);
        
        int get_time();
        int get_objectId();
        double get_posX();
        double get_posY();
};

#endif
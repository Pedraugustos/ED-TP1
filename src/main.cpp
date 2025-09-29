#include <iostream>
#include <stdexcept>
#include "object.hpp"
#include "scene.hpp"
#include "utils.hpp"

using namespace std;

int main(int argc, char* argv[]){
    if(argc < 2)
        throw out_of_range("Too few arguments.");

    int o = 0, m = 0, c = 0;
    string file = argv[1];

    count_o_m_c(o, m, c, file);

    Object* objects = new Object[o];
    Scene* scenes = new Scene[m];
    int* creations = new int[c];

    initialize_objects_scenes_creations(file, objects, scenes, creations);

    for(int i = 0; i < c; i++) {
        place_objects(creations[i], o, objects, m, scenes);
        selection_sort(objects, o);
        printt_objects(creations[i], o, objects);
    }
    
    delete[] objects;
    delete[] scenes;
    delete[] creations;

    return 0;
}
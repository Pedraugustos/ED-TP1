#include "utils.hpp"

void count_o_m_c(int &o, int &m, int &c, string filename) {
    ifstream file(filename);
    if (!file.is_open()) // ROBUSTEZ: excecao
        throw runtime_error("count_o_m_c: Can not open the file " + filename);

    string line;

    while(getline(file, line)) {
        if(line[0] == 'O'){
            o++;
            m++;
        }
        else if(line[0] == 'M')
            m++;
        else if(line[0] == 'C')
            c++;

    }
    file.close();
}

void initialize_objects_scenes_creations(string filename, Object objects[], Scene scenes[], int creations[]) {
    ifstream file(filename);
    if (!file.is_open()) // ROBUSTEZ: excecao
        throw runtime_error("initialize_objects_scenes_creations: Can not open the file: " + filename);

    string line;
    int indexOS = 0;
    int indexC = 0;

    char _;
    int _id;
    int _time;
    double _x, _y;
    double _width;

    while(getline(file, line)) {
        stringstream ss(line);
        ss >> _;
        if(_ == 'O') {
            ss >> _id >> _x >> _y >> _width;

            if(_id < 0) // ROBUSTEZ: excecao
                throw out_of_range("initialize_objects_scenes_creations: Object identification value in file must be greater or equal than 0.");

            if(_width < 0) // ROBUSTEZ: excecao
                throw out_of_range("initialize_objects_scenes_creations: Width value in file must be greater or equal than 0.");

            Object _object(_id, _x, _y, _width);
            Scene _scene(0, _id, _x, _y);
            objects[indexOS] = _object;
            scenes[indexOS] = _scene;

            indexOS++;
        }
        else if(_ == 'M') {
            ss >> _time >> _id >> _x >> _y;

            if(_time < 0) // ROBUSTEZ: excecao
                throw out_of_range("initialize_objects_scenes_creations: Time value in file must be greater or equal than 0.");

            if(_id < 0) // ROBUSTEZ: excecao
                throw out_of_range("initialize_objects_scenes_creations: Object identification value in file must be greater or equal than 0.");

            Scene _scene(_time, _id, _x, _y);
            scenes[indexOS] = _scene;

            indexOS++;
        }
        else if(_ == 'C') {
            ss >> _time;

            if(_time < 0) // ROBUSTEZ: excecao
                throw out_of_range("initialize_objects_scenes_creations: Time value in file must be greater or equal than 0.");

            creations[indexC] = _time;

            indexC++;
        }
    }
}

void place_objects(int moment, int o, Object objects[], int m, Scene scenes[]) {
    int time = 0;
    int index = 0;
    int id = -1;
    int pos = 0;
    double newX = 0, newY = 0;

    if(moment < 0)
        throw out_of_range("place_objects: Time value must be greater or equal than 0.");

    while(time <= moment) {
        id = scenes[index].get_objectId();
        newX = scenes[index].get_posX();
        newY = scenes[index].get_posY();
        pos = object_index_in_object_array(id, o, objects);
        objects[pos].move(newX, newY);

        if((index + 1) >= m)
            break;
        else {
            index++;
            time = scenes[index].get_time();
        }
    }
}

int object_index_in_object_array(int objectId, int o, Object objects[]) {
    int index = -1;

    if(objectId < 0)
        throw out_of_range("object_index_in_object_array: Object identification value must be greater or equal than 0.");

    for(int i = 0; i < o; i++) {
        if(objectId == objects[i].get_id()) {
            index = i;
            break;
        }
    }

    return index;
}

void print_objects(int moment, int id, double inf, double sup) {
    cout << "S " << moment << " " << id << " ";
    cout << fixed << setprecision(2) << inf << " " << sup << endl;
}

void printt_objects(int moment, int o, Object orderedObjects[]) {
    for(int i = 0; i < o; i++) {
        int index = object_index_in_object_array(i, o, orderedObjects);
        Object object = orderedObjects[index];
        double inf = object.get_min_x(); // infimum of the interval
        double sup = object.get_max_x(); // supremum of the interval

        while(inf < sup){ // A CONDICIONAL INF < SUP GARANTE A LÓGICA E FUNCIONA COMO DEFENSIVO PARA EVITAR PROBLEMAS
            for(int j = 0; j < index; j++) { // look at the objects in front of object i (in array, they come after)
                Object jthObject = orderedObjects[j];

                if(jthObject.intersects_interval(inf, sup)) {

                    if(jthObject.get_min_x() <= inf) {
                        inf = jthObject.get_max_x();
                        j = -1; 

                        if(inf >= sup)
                            break;
                    }
                    /*
                    if(jthObject.get_max_x() >= sup) {
                        sup = jthObject.get_min_x();
                        j = -1;

                        if(inf >= sup)
                            break;
                    }
                    */
                }
            }
            // if inf >= sup, then the object is not visible
            if(inf < sup) {
                for(int j = 0; j < index; j++) {
                    Object jthObject = orderedObjects[j];
                    
                    if(jthObject.intersects_interval(inf, sup) && jthObject.get_min_x() < sup) {
                        sup = jthObject.get_min_x();
                        
                        if(inf >= sup)
                            break;
                    }
                }

                print_objects(moment, i, inf, sup);

                inf = sup;
                sup = object.get_max_x();
            }
        }
    }
}

void selection_sort(Object* objects, int n){
    for(int i = 0; i < n-1; i++) {
        int min = i;
        for(int j = i+1; j < n; j++) {
            if(objects[min]>objects[j]) {
                min = j;
            }
        }
        Object tempObject = objects[i];
        objects[i] = objects[min];
        objects[min] = tempObject;
    }
}
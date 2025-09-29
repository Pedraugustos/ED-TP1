#ifndef UTILS_HPP
#define UTILS_HPP

#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <string>
#include <typeinfo>
#include <stdexcept>
#include <iomanip>
#include "object.hpp"
#include "scene.hpp"

using namespace std;

void count_o_m_c(int &, int &, int&, string);

void initialize_objects_scenes_creations(string, Object*, Scene*, int*);

void place_objects(int, int, Object*, int, Scene*);

int object_index_in_object_array(int, int, Object*);

void print_objects(int, int, double, double);

void printt_objects(int, int, Object*);

void selection_sort(Object*, int);

#endif
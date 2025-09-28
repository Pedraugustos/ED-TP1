#ifndef OBJECT_HPP
#define OBJECT_HPP

using namespace std;

class Object {
    private:
        int id;
        double x, y;
        double width;
        
    public:
        Object();
        Object(int, double, double, double);

        bool operator < (const Object&) const;
        bool operator > (const Object&) const;

        int get_id();
        double get_y();
        double get_min_x();
        double get_max_x();
        double get_width();

        void move(double, double);
        bool intersects_interval(double, double);
        bool is_inside(double, double);
};

#endif
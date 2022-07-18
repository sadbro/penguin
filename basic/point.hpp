
#include "../core.hpp"

#ifndef __POINT_H
#define __POINT_H

#define db double

class point{

    public:

        db x, y, z;

        point(db a1 = 0, db a2 = 0, db a3 = 0){

            x = a1;
            y = a2;
            z = a3;
        }

        friend std::ostream &operator<<( std::ostream &output, const point& p){

            output << p.x << ", " << p.y << ", " << p.z;
            return output;
        }

        void getXYZ(db* a1, db* a2, db* a3){

            *a1 = x;
            *a2 = y;
            *a3 = z;

        }

        void print(){

            printf("x: %.3lf, y: %.3lf, z: %.3lf\n", x, y, z);
        }

        db getDistance(point const& p1){

            return sqrt( pow(p1.x-x, 2) + pow(p1.y-y, 2) + pow(p1.z-z, 2) );
        }

        point copy(){

            return point(this->x, this->y, this->z);
        }

};

#endif


#ifndef __VECTOR_H
#define __VECTOR_H

class vector : public point {

    public:

        double d;

        vector(db a1 = 0, db a2 = 0, db a3 = 0){

            x = a1;
            y = a2;
            z = a3;

            d = getDistance(point(0, 0, 0));
        }

        vector operator + (vector const& v1){

            return vector(  x+v1.x,
                            y+v1.y,
                            z+v1.z
                        );
        }

        void operator += (vector const& v1){

            *this = (*this) + v1;
        }

        vector operator - (vector const& v1){

            return vector(  x-v1.x,
                            y-v1.y,
                            z-v1.z
                        );
        }

        void operator -= (vector const& v1){

            *this = (*this) - v1;
        }

        vector operator * (double k){

            return vector(  x*k,
                            y*k,
                            z*k
                        );
        }

        void operator *= (double k){

            *this = (*this) * k;
        }

        vector operator / (double const k){

            if(k == 0){

                std::cerr << "Invalid denominator: " << k << std::endl;
                exit(-1);
            }
            else{

                return (*this) * (1/k);
            }
        }

        void operator /= (double const k){

            *this = (*this) / k;
        }

        bool isPositive(){

            return (x > 0 && y > 0 && z > 0);
        }

        int dot(vector const& v1){

            return (x*v1.x) + (y*v1.y) + (z*v1.z);
        }

        vector cross(vector const& v1){

            return vector( y*v1.z - z*v1.y,
                           z*v1.x - x*v1.z,
                           x*v1.y - y*v1.x );
        }
};

#endif

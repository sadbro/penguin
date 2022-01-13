
#include "all.hpp"

#ifndef __OBJECT_H
#define __OBJECT_H

class Object {

    private:

        int ID;

    public:

        double mass;
        int size;
        vector color;
        std::map<std::string, vector> kinetics;
        std::vector<vector> info;

        Object( double m = 0,
                vector c = vector(1, 1, 1),
                int s = 10,
                std::map<std::string, vector> d = default_kinetics() ){

            mass = m;
            size = s;
            color = c;
            kinetics = d;
        }

        void SetPos(vector v){

            kinetics["position"] = v;
        }

        void SetSize(int s){

            size = s;
        }

        void SetColor(vector c){

            color = c;
        }

        void GetMass(double* m){

            *m = mass;
        }

        void UpdateMass(double m){

            mass = m;
        }

        void UpdateVelocity(vector v){

            kinetics["velocity"] = v;
        }

        void AddForce(vector F){

            if(mass == 0){

                std::cerr << "Mass not initialised" << std::endl;
                exit(-1);
            }

            else{

                kinetics["acceleration"] += F/mass;
            }
        }

        void Print(std::string prefix = "", std::string suffix = ""){

            std::cout << prefix;

            std::cout << "MASS:         " << mass << std::endl;
            std::cout << "POSITION:     "; kinetics["position"].print();
            std::cout << "VELOCITY:     "; kinetics["velocity"].print();
            std::cout << "ACCELERATION: "; kinetics["acceleration"].print();

            std::cout << suffix;
        }

        void UpdateK(double dT = 0){

            kinetics["position"] += kinetics["velocity"]*dT;
            kinetics["velocity"] += kinetics["acceleration"]*dT;
        }

        void Resist(double k = 1){

            if (kinetics["acceleration"].isPositive()){

                vector rf = kinetics["velocity"] * -k;
                AddForce(rf);
            }
        }

        void Gravity(Object* o, double G = 1, int debug = 0){

            double r = kinetics["position"].getDistance(o->kinetics["position"]);
            double F = (G*mass*o->mass)/pow(r, 3);
            vector dir = o->kinetics["position"] - kinetics["position"];

            kinetics["acceleration"] = (dir*F)/mass;
            o->kinetics["acceleration"] = (dir*-F)/o->mass;

            //  DEBUG

            if (debug){
                printf("\nSEPARATION : %lf\n", r);

                std::cout << "Mass 1       = " << mass << std::endl;

                std::cout << "Velocity     = ";
                kinetics["velocity"].print();

                std::cout << "Acceleration = ";
                kinetics["acceleration"].print();

                std::cout << "Mass 2       = " << o->mass << std::endl;

                std::cout << "Velocity     = ";
                o->kinetics["velocity"].print();

                std::cout << "Acceleration = ";
                o->kinetics["acceleration"].print();

                std::cout << std::endl;

                std::cout << "Force        = " << F << std::endl;
                std::cout << "Direction    = ";
                dir.print();
                }

        }

};

#endif

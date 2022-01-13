
#include "all.hpp"

#ifndef __WORLD_H
#define __WORLD_H

class World{

    private:

        unsigned int ID;

    public:

        int Height, Width, Length, tmp;
        int HL, WL, LL;

        std::string name;
        bool started;

        std::vector<Object*> system;
        std::map<std::string, vector> val;

        GLFWwindow* window;

        World(int W = 640, int H = 480, int L = -1, std::string s = "Penguin", int m = 1){

            Width = W;
            Height = H;
            Length = L;

            HL = WL = LL = -1e6;

            name = s;
            tmp = m;
            val = default_map();

            started = 1;

            glfwInit();
        }

        ~World(){

            glfwTerminate();
        }

        void init(){

            window = glfwCreateWindow(Width, Height, name.c_str(), nullptr, nullptr);
            glfwMakeContextCurrent(window);
        }

        static void fbs_callback(GLFWwindow* win, int w, int h){

            glViewport(0, 0, w, h);
        }

        void Normalize(double* a, double* b, double* c){

            *a = (*a/Width)*2*tmp;
            *b = (*b/Height)*2*tmp;
            *c = (*c/Length)*2*tmp;
        }

        void LimitX(int h){

            WL = h;
        }

        void LimitY(int k){

            HL = k;
        }

        void LimitZ(int s){

            LL = s;
        }

        void GridInit(){

            glPointSize(1);

            glBegin(GL_LINES);
            glColor3f(1, 1, 1);

            glVertex3f(-1, 0, 0);
            glVertex3f(1, 0, 0);

            glVertex3f(0, -1, 0);
            glVertex3f(0, 1, 0);

            glEnd();
        }

        void Render(double step , double r, double G){

            for(int i=0;i<system.size();i++){

                double t1, t2, t3;
                double c1, c2, c3;

                glPointSize(system[i]->size);
                glBegin(GL_POINTS);

                system[i]->kinetics["position"].getXYZ(&t1, &t2, &t3);
                system[i]->color.getXYZ(&c1, &c2, &c3);

                Normalize(&t1, &t2, &t3);
                glColor3f(c1, c2, c3);
                glVertex3f(t1, t2, t3);

                if (t1 >= WL && t2 >= HL && t3 >= LL){

                    for(int j=i+1;j<system.size();j++){

                        system[i]->Gravity(system[j], G);
                        //system[j]->Gravity(system[i], G);
                    }

                    system[i]->UpdateK(step);
                    system[i]->Resist(r);
                }

                glEnd();
            }
        }

        void Run(double step, double resistance = 0, double G = 1, int grid = 0){

            glfwSetFramebufferSizeCallback(window, fbs_callback);

            while (!glfwWindowShouldClose(window)){

                glfwGetWindowSize(window, &Width, &Height);

                glClear(GL_COLOR_BUFFER_BIT);

                if (grid){GridInit();}

                Render(step, resistance, G);

                glfwSwapBuffers(window);
                glfwPollEvents();

            }

        }

        void AddObject(Object* o){

            system.push_back(o);
        }

        void AddDefaultVelocity(vector v){

            val["velocity"] += v;

            for(int i=0;i<system.size();i++){

                system[i]->kinetics["velocity"] += v;
            }
        }

        void AddDefaultAcceleration(vector a){

            val["acceleration"] += a;

            for(int i=0;i<system.size();i++){

                system[i]->kinetics["acceleration"] += a;
            }
        }

        void AddForce(vector f){

            for(int i=0;i<system.size();i++){

                system[i]->AddForce(f);
            }
        }

};

#endif

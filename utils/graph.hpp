
#include "../all.hpp"

#ifndef __GRAPH_H
#define __GRAPH_H

class graph {

    private:

        unsigned int ID;

    public:

        std::vector<double> domain;
        double (*member)(double);
        int w, h, limX, limY;

        GLFWwindow* g_window;

        graph(double (*fn)(double), int lx = 10, int ly = 10){

            member = fn;
            limX = lx;
            limY = ly;
        }

        void N(double* x, double* y){

            glfwGetWindowSize(g_window, &w, &h);

            if (!g_window){

                std::cerr << "Window not started."
                             "Please initialise by calling init()" << std::endl;
            }

            else{

                *x /= limX;
                *y /= limY;
            }
        }

        void init(int w = 640, int h = 480, std::string name = "penguin-graph"){

            glfwInit();

            g_window = glfwCreateWindow(w, h, name.c_str(), nullptr, nullptr);
            glfwMakeContextCurrent(g_window);
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

        void render(int size){

            glPointSize(size);
            glBegin(GL_POINTS);

            double yi;

            for (int i = 0;i < domain.size(); i++){

                yi = member(domain[i]);

                N(&domain[i], &yi);

                glColor3f(0.1, 0.3, 0.6);
                glVertex3f(domain[i], yi, 0);
            }

            glEnd();
        }

        void run(std::vector<double> d, int s = 2){

            domain = d;

            glClear(GL_COLOR_BUFFER_BIT);

            while(!glfwWindowShouldClose(g_window)){

                GridInit();
                render(s);

                glfwSwapBuffers(g_window);
                glfwPollEvents();
            }
        }

};

#endif


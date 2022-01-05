
#include "all.hpp"

class Object {

    private:

        int ID;

    public:

        double mass;
        std::map<std::string, vector> kinetics;

    Object( double m = 0,
            std::map<std::string, vector> d = default_kinetics() ){

        mass = m;
        kinetics = d;
    }

    void SetPos(vector v){

        kinetics["position"] = v;
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

    void UpdateK(double dT){

        kinetics["position"] += kinetics["velocity"]*dT;
        kinetics["velocity"] += kinetics["acceleration"]*dT;
    }

};

class World{

    private:

        unsigned int ID;

    public:

        int Height, Width, Length;
        std::string name;
        bool started;

        std::vector<Object*> system;
        std::map<std::string, vector> val;

        GLFWwindow* window;

        World(int W = 640, int H = 480, int L = -1, std::string s = "Penguin"){

            Height = H;
            Width = W;
            Length = L;
            name = s;

            val = default_map();

            started = 1;

            glfwInit();
        }

        void init(){

            window = glfwCreateWindow(Width, Height, name.c_str(), nullptr, nullptr);
            glfwMakeContextCurrent(window);
        }

        void Normalize(double* a, double* b, double* c, int m = 1){

            *a = (*a/Width)*m;
            *b = (*b/Height)*m;
            *c = (*c/Length)*m;
        }

        void GridInit(){

            glPointSize(1);

            glClear(GL_COLOR_BUFFER_BIT);
            glBegin(GL_LINES);

            glVertex3f(-1, 0, 0);
            glVertex3f(1, 0, 0);

            glVertex3f(0, -1, 0);
            glVertex3f(0, 1, 0);

            glEnd();
        }

        void Render(){

            glPointSize(7);

            glBegin(GL_POINTS);

            for(int i=0;i<system.size();i++){

                double t1, t2, t3;

                system[i]->kinetics["position"].getXYZ(&t1, &t2, &t3);
                Normalize(&t1, &t2, &t3, 2);

                glVertex3f(t1, t2, t3);

                system[i]->UpdateK(0.05);
            }

            glEnd();
        }

        void Run(){

            while (!glfwWindowShouldClose(window)){

                GridInit();

                Render();

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

int main(){

	return 0;
}


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

        int Height, Width;
        std::string name;
        bool started;

        std::vector<Object*> system;

        GLFWwindow* window;

        World(int W = 640, int H = 480, std::string s = "Penguin"){

            Height = H;
            Width = W;
            name = s;

            started = 1;

            glfwInit();
        }

        void init(){

            window = glfwCreateWindow(Width, Height, name.c_str(), nullptr, nullptr);
            glfwMakeContextCurrent(window);
        }

        void Update(){

            while (!glfwWindowShouldClose(window)){

                glfwSwapBuffers(window);
                glfwPollEvents();
            }
        }

};


int main(){

    World w = World();
    w.init();

    w.Update();

	return 0;
}

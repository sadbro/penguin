
#include "all.hpp"

class Object {

    private:

        int ID;

    public:

        double mass;
        int size;
        vector color;
        std::map<std::string, vector> kinetics;

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

        void Gravity(Object* o, double G = 1){

            double r = kinetics["position"].getDistance(o->kinetics["position"]);
            double F = (G*mass*o->mass)/pow(r, 3);
            vector dir = o->kinetics["position"] - kinetics["position"];

            kinetics["acceleration"] = (dir*F)/mass;
            o->kinetics["acceleration"] = (dir*-F)/o->mass;

            //  DEBUG

            printf("\nSEPARATION : %lf\n", r);

            std::cout << "Mass 1   = " << mass << std::endl;
            std::cout << "Velocity = ";
            kinetics["velocity"].print();

            std::cout << "Mass 2   = " << o->mass << std::endl;
            std::cout << "Velocity = ";
            o->kinetics["velocity"].print();

            //std::cout << "Acceleration = ";
            //o->kinetics["acceleration"].print();
        }

};

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

            Height = H;
            Width = W;
            Length = L;

            HL = WL = LL = -1e6;

            name = s;
            tmp = m;
            val = default_map();

            started = 1;

            glfwInit();
        }

        void init(){

            window = glfwCreateWindow(Width, Height, name.c_str(), nullptr, nullptr);
            glfwMakeContextCurrent(window);
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

        void Render(double step , double r){

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

                    system[i]->UpdateK(step);
                    system[i]->Resist(r);
                }

                glEnd();
            }
        }

        void Run(double step, double resistance = 0){

            while (!glfwWindowShouldClose(window)){

                glClear(GL_COLOR_BUFFER_BIT);

                GridInit();

                for(int i=0;i<system.size();i++){

                    for(int j=i+1;j<system.size();j++){

                        system[i]->Gravity(system[j]);
                    }
                }

                Render(step, resistance);

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

    Object earth = Object(1);
    Object sun = Object(100);

    sun.SetSize(20);
    earth.SetSize(5);

    sun.SetPos(vector(0, 0, 0));
    earth.SetPos(vector(-150, 0, 0));

    sun.SetColor(vector(1, 0.9, 0.2));
    earth.SetColor(vector(0.1, 0.9, 1));

    earth.UpdateVelocity(vector(0, 0.5, 0));

    World w = World(640, 480, -1, "Penguin");

    w.init();

    w.AddObject(&sun);
    w.AddObject(&earth);

    w.Run(0.5, 1);

	return 0;
}

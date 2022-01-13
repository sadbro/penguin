
/*

    ------------
      TEST - 1
    ------------

            -- @sadbro

MOON ROTATING AROUND EARTH



        (not to scale)

!![ install GLFW3 before testing ]!!

Linkers :

    -L/usr/local/lib
    -lglfw3
    -lrt
    -lm
    -ldl
    -lX11
    -lpthread
    -lxcb
    -lXau
    -lXdmcp
    -lGL
    -lGLU
    -lglut

*/

#include "all.hpp"

int main(){

    Object earth = Object(100);
    Object moon = Object(1);

    earth.SetSize(13);
    earth.SetColor(vector(0.1, 0.3, 0.8));

    moon.SetSize(5);
    moon.SetPos(vector(-70, 0, 0));

    moon.UpdateVelocity(vector(0, 1, 0));

    World w = World(800, 600);

    w.AddObject(&earth);
    w.AddObject(&moon);

    w.init();

    w.Run(0.5, 0, 1);

	return 0;
}

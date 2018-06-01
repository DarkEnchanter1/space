#include <iostream>
#include <thread>
#include <sys/time.h>
#include "physics.hpp"
#include <unistd.h>
#include "rendering/renderer.hpp"
#include <GLFW/glfw3.h>

float fRand(float fMin, float fMax)
{
    float f = (float)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

render::RenderEngine rdr;
bool running = true;
int physicsLoop() {
	Physics::Factory f(&rdr);
	Physics::Vector v;
	v.dir = {2.0f,4.0f,6.0f};	
	Physics::Object o = f.create_object("resources/untitled.obj");
	o.set_speed(v);
	Physics::Force thrust = f.create_force(v, &o);

	 v.dir = {0.0f,3.0f,6.0f};	
	 Physics::Object o2 = f.create_object("resources/untitled.obj");
	 o2.set_speed(v);
	 Physics::Force thrust2 = f.create_force(v, &o2);

	 v.dir = {-5.0f,-2.0f,-3.0f};	
	 Physics::Object o3 = f.create_object("resources/untitled.obj");
	 o3.set_speed(v);
	 Physics::Force thrust3 = f.create_force(v, &o3);
	timespec ts;
	timespec res;
	clock_getres(CLOCK_REALTIME, &res);
	clock_gettime(CLOCK_REALTIME, &ts);
	double factor = res.tv_nsec/1000000000.0;
	double oldTime = ((double)ts.tv_sec) + (ts.tv_nsec * factor);
	while (running) {
		clock_gettime(CLOCK_REALTIME, &ts);
		double newTime = ((double)ts.tv_sec) + (ts.tv_nsec * factor);
		double delta = newTime - oldTime;
		if (delta > 0.4) delta = 0.4; //Restrict the amount of time skip that's possible - To prevent things like an object fazing through a wall it's flying towards
		oldTime = newTime;
		f.update(delta);
	}
	
}
int
main(void)
{
	std::cout << "Hello Wrold!()\n";
	std::thread thr(physicsLoop); //The physics loop is on a seperate thread to prevent either the physics or rendering from freezing each other.
	rdr.loop();       //The render loop *must* be run on the thread the renderer was created in, otherwise it will throw many errors.
	running = false;  //This line tells the physics thread that the render engine is dead (so it should die too)
	thr.detach();     //This line seperates the physics thread to allow it to shut down when it's ready. 
	                  //(Otherwise, it would shut down when this thread died (the reference goes out of scope))
	std::cout << std::endl; //For my sanity, prevents the terminal from overwriting the position log
	return 0;
}

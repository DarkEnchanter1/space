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
	//v.dir = {0.0f,50.0f,0.0f};
	Physics::Object o = f.create_object("resources/untitled.obj");
	o.set_speed(v);
	Physics::Force thrust = f.create_force(v, &o);
	timespec ts;
	timespec res;
	clock_getres(CLOCK_REALTIME, &res);
	clock_gettime(CLOCK_REALTIME, &ts);
	float factor = res.tv_nsec/1000000000.0f;
	float oldTime = ts.tv_nsec * factor;
	while (running) {
		clock_gettime(CLOCK_REALTIME, &ts);
		float newTime = ts.tv_nsec * factor;
		float delta = newTime - oldTime;
		if (delta > 0.4) delta = 0.4; 
		if (delta < 0) delta = 0; //? What?! TODO: Figure out what causes this
		oldTime = newTime;
		f.update(delta);
	}
	
}
int
main(void)
{
	std::cout << "Hello Wrold!()\n";
	std::thread thr(physicsLoop); //The physics loop is on a seperate thread to prevent either the physics or rendering from freezing each other.
	rdr.loop();       //The render loop *must* be run on the thread it was created in, otherwise it will throw many errors.
	running = false;  //This line tells the physics thread that the render engine is dead (so it should die too)
	thr.detach();     //This line seperates the physics thread to allow it to shut down when it's ready. 
	                  //(Otherwise, it would shut down when this thread died (the reference goes out of scope))
	std::cout << std::endl; //For my sanity, prevents the terminal from overwriting the position log
	return 0;
}

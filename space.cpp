#include <iostream>
#include <thread>
#include "physics.hpp"
#include <unistd.h>
#include "rendering/renderer.hpp"
#include <GLFW/glfw3.h>
render::RenderEngine rdr;
bool stop = false;
int renderLoop() {
}
int physicsLoop() {
	Physics::Factory f(&rdr);
	Physics::Vector v;
	v.dir = {0,0,0};
	Physics::Object o = f.create_object("resources/cube.obj");
	o.set_speed(v);
	v.dir = {0.0f, 0.0f, 0.0f};
	Physics::Force thrust = f.create_force(v, &o);

	const timespec t = {0, 75000000};
	for (;;) {
		f.update();
		nanosleep(&t, NULL);
	}
	
}
int
main(void)
{
	std::cout << "Hello Wrold!()\n";
	std::thread thr(physicsLoop);
	rdr.loop();
	std::terminate();
	return 0;
}

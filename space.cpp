#include <iostream>
#include <thread>
#include "physics.hpp"
#include <unistd.h>
#include "rendering/renderer.hpp"
render::RenderEngine render;
int renderLoop() {
	while (true)
		render.render();
}
int
main(void)
{
	std::cout << "Hello World!()\n";
	std::thread thr(renderLoop);
	Physics::Factory f;
	Physics::Vector v;
	v.dir = new float[3] {5,5,5};
	Physics::Object o = f.create_object("resources/cube.obj");
	o.set_speed(v);
	v.dir = new float[3] {-4.0f, -2.0f, 4.0f};
	Physics::Force thrust = f.create_force(v, &o);

	const timespec t = {0, 75000000};
	for(;;) { //Seriously?
		f.update();
		o.print();
		nanosleep(&t, NULL);
	}
	
	return 0;
}

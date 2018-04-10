#include <iostream>
#include "physics.hpp"
#include <unistd.h>

int
main(void)
{
	std::cout << "Hello Wrold!()\n";

	Physics::Factory f;
	Physics::Object o = f.create_object();

	for(;;) {
		f.update();
		o.print();
		sleep(1);
	}
	
	return 0;
}

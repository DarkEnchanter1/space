#include "physics.hpp"
#include <iostream>

namespace Physics
{
Vector::Vector(Coord a, unsigned int b) : dir(a), mag(b) { };

Object::Object() : speed(Coord(), 0), mass(0), dir(Angle())
{
	speed.dir.x = 1;
	speed.mag = 10; 

	std::cout << this << ": speed.dir.x=" << speed.dir.x << "\t speed.dir.inate[0]=" << speed.dir.inate[0] << std::endl;
}

void
Object::update()
{
	std::cout << "Update! " << this << std::endl;
	for(int i=0; i<3; i++) {
		std::cout << pos.inate[i] << " : " << speed.dir.inate[i] << " : " << speed.mag << std::endl;
		pos.inate[i] = pos.inate[i] + (speed.dir.inate[i] * speed.mag);
	}
}

void
Object::print()
{
	std::cout << this << ": mass:" << mass << " speed: " << speed.mag << std::endl;
	std::cout << "speed\tpos\n";
	std::cout << speed.dir.x << "\t" << pos.x << "\n";
	std::cout << speed.dir.y << "\t" << pos.y << "\n";
	std::cout << speed.dir.z << "\t" << pos.z << "\n";

}

Object
Factory::create_object()
{
	Object ret = Object();
	std::cout << &ret << " added to list\n";
	objs.push_back(&ret);
	return ret;
}

void
Factory::update()
{
	for ( auto &i : objs)
		i->update();	
}
}

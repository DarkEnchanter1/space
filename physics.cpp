#include "physics.hpp"
#include <iostream>
#include <cmath>

namespace Physics
{
Vector::Vector() { };

Coord::Coord() 
{
	for (int i=0; i<3; i++)
		inate[i] = 0.0f;
}

float
Vector::get_mag()
{
	return sqrt((dir.inate[0]*dir.inate[0])+(dir.inate[1]*dir.inate[1])+(dir.inate[2]*dir.inate[2]));
}

Object::Object() : speed(), mass(0), dir(Angle())
{
	speed.dir.x = 1.0f;
	speed.dir.y = 2.0f;
	speed.dir.z = 5.0f;
}

void
Object::update()
{
	//std::cout << "Update! " << this << std::endl;
	for(int i=0; i<3; i++)
		pos.inate[i] = pos.inate[i] + speed.dir.inate[i];
}

void
Object::print()
{
	if (speed.dir.x!=1.0f)
	std::cout << this << ": mass:" << mass << " speed: " << speed.get_mag() << std::endl;
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

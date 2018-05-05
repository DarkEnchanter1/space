#include "physics.hpp"
#include <iostream>
#include <cmath>

namespace Physics
{
Vector::Vector() { };

Vector::Vector(Angle a, float mag)
{
	dir.x = 0;
	dir.y = 0;
	dir.z = 0;
}

void
Vector::normalize()
{
	dir = (this->dir)*(1/this->get_mag());
}


Coord
Coord::operator*(const float& f)
{
	Coord c = *this;
	for (int i=0; i<3; i++)
		c.inate[i] *= f;
	return *this;
}

Coord
Coord::operator=(const Coord& c)
{
	for (int i=0; i<3; i++)
		this->inate[i] = c.inate[i];
	return *this;
}

Coord
Coord::operator=(const float f[3])
{
	for (int i=0; i<3; i++)
		this->inate[i] = f[i];
	
	return *this;
}

Coord
Coord::cross(const Coord& c)
{
	return *this;
}

Matrix::Matrix(float theta, Axis a)
{
	switch(a)
	{
		case x:
		{

		}
		case y:
		{
		}
		case z:
		{
		}
	}
}

float
Vector::get_mag()
{
	return sqrt((dir.inate[0]*dir.inate[0])+(dir.inate[1]*dir.inate[1])+(dir.inate[2]*dir.inate[2]));
}

float
Vector::get_sqrmag()
{
	return (dir.inate[0]*dir.inate[0])+(dir.inate[1]*dir.inate[1])+(dir.inate[2]*dir.inate[2]);
}

Object::Object(const char* modelid) : speed(), mass(0), model(modelid) 
{
	speed.dir.x = 1.0f;
	speed.dir.y = 2.0f;
	speed.dir.z = 5.0f;

	float tmp[3] = {0.0f,0.0f,0.0f};
	pos = tmp;

	tmp[0] = 1.0f;
	dir.dir = tmp;
	tmp[0] = 0; tmp[2] = 1.0f;
	upv.dir = tmp;
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
	std::cout << this << ": mass:" << mass << " speed: " << sqrt(speed.get_sqrmag()) << std::endl;
	std::cout << "speed\tpos\n";
	std::cout << speed.dir.x << "\t" << pos.x << "\n";
	std::cout << speed.dir.y << "\t" << pos.y << "\n";
	std::cout << speed.dir.z << "\t" << pos.z << "\n";

}

void
Object::set_speed(int index, float val)
{
	speed.dir.inate[index] = val;
}

void
Object::set_speed(Vector v)
{
	speed = v;
}

float
Object::get_speed(int index)
{
	return speed.dir.inate[index];
}

Object
Factory::create_object(const char* modelid)
{
	Object ret = Object(modelid);
	std::cout << &ret << " added to list\n";
	objs.push_back(&ret);
	return ret;
}

Force
Factory::create_force(Vector f, Physics::Object* o)
{
	Force ret(f, o);
	fors.push_back(&ret);
	return ret;
}

void
Factory::update()
{
	for ( auto &i : fors)
		i->update();
	for ( auto &i : objs)
		i->update();
}

Force::Force(Vector f, Object* o) : o(o), v(f)
{
	v.normalize();
};

void
Force::update()
{
	for(int i=0; i<3; i++)
		o->set_speed(i, (o->get_speed(i)+v.dir.inate[i]));
}
}

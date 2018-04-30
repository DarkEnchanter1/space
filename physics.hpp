#ifndef PHYSICS_HPP
#define PHYSICS_HPP
#include <vector>
#include "rendering/renderer.hpp"
namespace Physics
{
class Factory;
class Angle;
class Vector;
class Object;
class Force;

class Factory
{
	std::vector<Object*> objs;
	std::vector<Force*>  fors;
public:
	Object create_object(const char* modelid);
	Force  create_force(Vector f, Object* o);
	void update();
};

struct Coord
{
	Coord();
	float inate[3] = {0,0,0};
	float& x = inate[0];
	float& y = inate[1];
	float& z = inate[2];
	Coord operator*(const float&);
	Coord operator=(const Coord&);
	Coord operator=(const float[3]);
	Coord dot(const Coord& c);
	Coord cross(const Coord& c);
};

struct Matrix
{
private:
	float mat[3][3];
public:
	typedef enum {x, y, z}Axis;
	Matrix(float theta, Axis a);
};

class Angle
{
	unsigned int yaw, pitch, roll;
};

class Vector
{
public:
	Vector();
	Vector(Angle a, float mag);
	Coord dir;
	float get_sqrmag();
	float get_mag();
	void  normalize();
};

class Object
{
protected:
	unsigned int mass; // kg
	Vector speed;      // m/s
	Coord  pos;        // m
	Vector dir;
	Vector upv;
	render::Model model;
	Object(const char* modelid);
	friend Object Factory::create_object(const char* modelid);
public:
	void update(void);
	void print(void);
	void set_speed(int index, float val);
	void set_speed(Vector v);
	float get_speed(int index);
	void orient(const Vector& d, const Vector& u);
};

class Force
{
	Vector v;		// N
	Object* o;
	Force(Vector f, Object* o);	// N(component)
	//Force(Angle a, float mag, Object* o);	// theta, N(net)
public:

	void update();
	friend Force Factory::create_force(Vector f, Object* o);
};

}
#endif
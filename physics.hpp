#ifndef PHYSICS_HPP
#define PHYSICS_HPP
#include <vector>
#include <mutex>
namespace Physics
{
class Factory;
class Coord;
class Matrix;
class Angle;
class Vector;
class Object;
class Force;
}
#include "rendering/renderer.hpp"


class Physics::Factory
{
	std::vector<Object*> objs;
	std::mutex           objs_mutex;
	std::vector<Force*>  fors;
	render::RenderEngine* rend = 0;
public:
	Factory(render::RenderEngine* _r);
	Object create_object(const char* modelid);
	Force  create_force(Vector f, Object* o);
	void update(double delta);
	void sendAllModels();
	friend render::RenderEngine;
};

struct Physics::Coord
{
	union {
		double inate[3] = {0,0,0};
		double x, y, z;
	};
	Coord operator*(const double&);
	Coord operator=(const Coord&);
	Coord operator=(const double[3]);
	Coord dot(const Coord& c);
	Coord cross(const Coord& c);
};

struct Physics::Matrix
{
private:
	float mat[3][3];
public:
	typedef enum {x, y, z}Axis;
	Matrix(float theta, Axis a);
};

class Physics::Angle
{
	unsigned int yaw, pitch, roll;
};

class Physics::Vector
{
public:
	Vector();
	Vector(Angle a, float mag);
	Coord dir;
	float get_sqrmag();
	float get_mag();
	void  normalize();
};

class Physics::Object
{
protected:
	unsigned int mass; // kg
	Vector speed;      // m/s
	Coord  pos;        // m
	Vector dir;
	Vector upv;
	render::Model model;
	glm::mat4 Model;
	GLuint vertexbuffer, uvbuffer, normalbuffer;
//	std::vector<glm::vec4> triangles;
	Object(const char* modelid);
	friend Physics::Object Factory::create_object(const char* modelid);
public:
	void pushModel(/*std::vector<glm::vec4>* triangles, std::vector<glm::vec2>* uvdata, std::vector<glm::vec4>* normals*/);
	void update(double delta);
	void preRender();
	void render(GLuint ModelID);
	void print(void);
	void set_speed(int index, float val);
	void set_speed(Vector v);
	float get_speed(int index);
	void orient(const Vector& d, const Vector& u);
};

class Physics::Force
{
	Vector v;		// N
	Object* o = 0;
	Force(Vector f, Object* o);	// N(component)
	//Force(Angle a, float mag, Object* o);	// theta, N(net)
public:

	void update(double delta);
	friend Physics::Force Factory::create_force(Vector f, Object* o);
};

#endif

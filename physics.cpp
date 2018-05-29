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
Coord::operator*(const double& f)
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
Coord::operator=(const double f[3])
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
	speed.dir.x = 0.0f;
	speed.dir.y = 0.0f;
	speed.dir.z = 0.0f;

	double tmp[3] = {0.0,0.0,0.0};
	pos = tmp;

	tmp[0] = 1.0;
	dir.dir = tmp;
	tmp[0] = 0; 
	tmp[2] = 1.0;
	upv.dir = tmp;
}

void
Object::update(double delta)
{
	for(int i=0; i<3; i++) {
		pos.inate[i] = pos.inate[i] + (speed.dir.inate[i] * (delta*100));
		//std::cout << pos.inate[i]; //For some reason this makes things work...
		//! THIS IS NOT THREAD SAFE. MUCH SYNCHRONISATION NEEDS TO BE DONE
		//? More accurately, this code doesn't work for god knows what reason unless this method takes a while to return.
	}
	//std::cout << std::endl;
	Model = glm::translate(glm::mat4(), glm::vec3((float)pos.inate[0], (float)pos.inate[1], (float)pos.inate[2]));
	// for (int x = 0; x < 4; x++) {
	// 	for (int y = 0; y < 4; y++)
	// 		std::cout << Model[x][y] << ", ";
	// 	std::cout << std::endl;
	// } 
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
/*
	Like the initializer, but on the render thread.
*/
void Object::preRender() {
}
void
Object::render(GLuint ModelID) {
	//Sets the model transformation matrix
	glUniformMatrix4fv(ModelID, 1, GL_FALSE, &Model[0][0]);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * model.triangles.size(), &model.triangles[0], GL_STATIC_DRAW);
	glVertexAttribPointer(
		0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
		4,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * model.uvdata.size(), &model.uvdata[0], GL_STATIC_DRAW);	
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);
	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, model.triangles.size()); // Dynamic triangle count.

}
void
Object::pushModel(/*std::vector<glm::vec4>* triangleBuf, std::vector<glm::vec2>* uvBuf, std::vector<glm::vec4>* normalBuf*/)
{
	glGenBuffers(1, &vertexbuffer);
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * model.triangles.size(), &model.triangles[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * model.uvdata.size(), &model.uvdata[0], GL_STATIC_DRAW);
//	triangleBuf->insert(triangleBuf->end(), model.triangles.begin(), model.triangles.end());
//	uvBuf->insert(uvBuf->end(), model.uvdata.begin(), model.uvdata.end());
//	normalBuf->insert(normalBuf->end(), model.normals.begin(), model.normals.end());
}

Factory::Factory(render::RenderEngine* _r) {
	rend = _r; //TODO: Stop this double initialization
	if (_r != 0)
	_r->physics = this;
}

Object
Factory::create_object(const char* modelid)
{
	Object ret = Object(modelid);
    std::lock_guard<std::mutex> lock(objs_mutex);
	objs.push_back(&ret);
	if (rend != 0)
	rend->dataHasUpdated = true;
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
Factory::update(double delta)
{
	for ( auto &i : fors)
		i->update(delta);
    std::lock_guard<std::mutex> lock(objs_mutex);
	for ( auto &i : objs) {
		i->update(delta);
	}
}
void
Factory::sendAllModels() {
//	std::vector<glm::vec4> triangleBuf;
//	std::vector<glm::vec2> uvBuf;
//	std::vector<glm::vec4> normalBuf;
    std::lock_guard<std::mutex> lock(objs_mutex);
	for (int i = 0; i < objs.size(); i++) {
		if (objs[i] != 0)
			objs[i]->pushModel(/*&triangleBuf, &uvBuf, &normalBuf*/);
	}
	//rend->triangles = triangleBuf;
	//rend->uvdata = uvBuf;
	//rend->normals = normalBuf;
	if (rend != 0)
	rend->dataHasUpdated = true;
}

Force::Force(Vector f, Object* o) : o(o), v(f)
{
	v.normalize();
};

void
Force::update(double delta)
{
	for(int i=0; i<3; i++)
		o->set_speed(i, (o->get_speed(i)+v.dir.inate[i]) * delta);
}
}

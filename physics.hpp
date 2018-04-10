#include <vector>

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
	Object create_object();
	void update();
};

struct Coord
{
	float inate[3] = {0,0,0};
	float& x = inate[0];
	float& y = inate[1];
	float& z = inate[2];
};

class Angle
{
	unsigned int yaw, pitch, roll;
};

class Vector
{
public:
        Vector();
        Coord dir;
	float get_mag();
};

class Object
{
protected:
        unsigned int mass;
        Vector speed;
        Coord  pos;
	Angle  dir;
	Object();
	friend Object Factory::create_object();
public:
	void update(void);
	void print(void);
};

class Force
{
	Vector v;
	std::vector<Object*> units;
	Force();
};

}

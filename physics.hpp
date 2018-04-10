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
        int inate[3] = {0,0,0};
        int& x = inate[0];
        int& y = inate[1];
        int& z = inate[2];
};

class Angle
{
	unsigned int yaw, pitch, roll;
};

class Vector
{
public:
        Vector(Coord a, unsigned int b);
        Coord dir;
        unsigned int mag;
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

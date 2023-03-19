#include <iostream>
#include <string>
#include <cmath>
using namespace std;
namespace oj
{
	class Shape3D
	{	
		double volume;

	public:
		double getVolume();
	
	protected:
		void setVolume(double volume);
	};

	class Sphere : public Shape3D
	{
		double radius;
		double pi;
	
	public:
		Sphere(double, double);
	};

	class Cone : public Shape3D
	{
		double radius;
		double height;
		double pi;

	public:
		Cone(double, double, double);
	};

	class Cuboid : public Shape3D
	{
		double length;
		double width;
		double height;
	
	public:
		Cuboid(double, double, double);
	};

	class Cube : public Cuboid
	{
	public:
		Cube(double);
	};
}

namespace oj
{   
    void Shape3D::setVolume(double v)
    {
        volume = v;
    }

    double Shape3D::getVolume()
    {
        return volume;
    }
}

namespace oj
{
	Sphere::Sphere(double r, double pi):radius(r),pi(pi){
		double v = 0.0;
		if(r > 0 && pi > 0){
			v = (4.0 * pi * pow(r, 3)) / 3.0;
		}
		setVolume(v);
	}
	Cone::Cone(double radius, double h, double pi):radius(radius), height(h), pi(pi){
		double v = 0.0;
		if(radius > 0 && pi > 0 && h > 0){
			v = (h * pi * pow(radius, 2)) / 3.0;
		}
		setVolume(v);
	}
	Cuboid::Cuboid(double length, double width, double height):height(height), width(width), length(length){
		double v = 0.0;
		if(length > 0 && width > 0 && height > 0){
			v = length * width * height;
		}
		setVolume(v);
	}
	Cube::Cube(double length):Cuboid(length, length, length){
		if(length < 0) setVolume(0);
	}
}


int main(void)
{   
    using namespace oj;

    string s;
    double a, b, c;
    double totalVolume = 0.0, totalPerimeter = 0.0;

    while(cin >> s) {
        if(s == "Sphere") {
            cin >> a >> b;
            Sphere sphere(a, b);
            totalVolume += sphere.getVolume();
            //cout << "Ball: " << sphere.getVolume() << endl;
        }
        if(s == "Cone") {
            cin >> a >> b >> c;
            Cone cone(a, b, c);
            totalVolume += cone.getVolume();
            //cout << "Cone: " << cone.getVolume() << endl;
        }
        if(s == "Cuboid") {
            cin >> a >> b >> c;
            Cuboid cuboid(a, b, c);
            totalVolume += cuboid.getVolume();
            //cout << "Cuboid: " << cuboid.getVolume() << endl;
        }
        if(s == "Cube") {
            cin >> a;
            Cube cube(a);
            totalVolume += cube.getVolume();
            //cout << "Cube: " << cube.getVolume() << endl;
        }
    }

    cout << totalVolume << endl;

    return 0;
}
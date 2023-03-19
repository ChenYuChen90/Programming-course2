#ifndef SHAPE_H
#define SHAPE_H

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
#include <cmath>
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

#endif

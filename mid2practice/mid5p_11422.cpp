#include <iostream>
#include <string>
#include <cmath>
using namespace std;
namespace oj
{
	class Shape 
	{	
	public:
		double getArea();
		double getPerimeter();
	
	protected:
		void setArea(double a);
		void setPerimeter(double p);
			
	private:
		double area;
		double perimeter;
	};
	class Triangle : public Shape
	{
	public:
		Triangle(double edge1, double edge2, double edge3);
		
	private:
		double edge1;
		double edge2;
		double edge3;
		
	};

	class Rectangle : public Shape
	{
	public:
		Rectangle(double width, double height);
		
	private:
		double width;
		double height;
	};

	class Circle : public Shape
	{
	public:
		Circle(double radius, double pi);
		
	private:
		double radius;
		double pi;
	};
}
namespace oj
{
    Triangle::Triangle(double edge1, double edge2, double edge3){
        double a = 0, s = (edge1 + edge2 + edge3) / 2, per = 0;
		if(edge3 >= 0 && edge2 >= 0 && edge1 >= 0 && edge1 + edge2 > edge3 && edge1 + edge3 > edge2 && edge2 + edge3 > edge1){
        	a = sqrt(s * (s - edge1) * (s - edge2) * (s - edge3));
			per = 2 * s;
		}
		setArea(a);
        setPerimeter(per);
    }
	Rectangle::Rectangle(double width, double height){
		double a = 0, per = 0;
		if(width >= 0 && height >= 0){
			a = width * height, per = 2 * (width + height);
		}
		setArea(a);
		setPerimeter(per);
	}
	Circle::Circle(double radius, double pi){
		double a = 0, per = 0;
		if(radius >= 0 && pi >= 0){
			a = pi * radius * radius, per = 2 * pi * radius;
		}
		setPerimeter(per);
		setArea(a);
	}
}


namespace oj
{   
    void Shape::setArea(double a)
    {
        area = a;
    }

    void Shape::setPerimeter(double p)
    {
        perimeter = p;
    }

    double Shape::getArea()
    {
        return area;
    }

    double Shape::getPerimeter()
    {
        return perimeter;
    }
}


int main(void)
{   
    using namespace oj;

    string s;
    double a, b, c;
    double totalArea = 0.0, totalPerimeter = 0.0;

    while(cin >> s) {
        if(s == "Triangle") {
            cin >> a >> b >> c;
            Triangle T(a, b, c);
            totalArea += T.getArea();
            totalPerimeter += T.getPerimeter();
        }
        if(s == "Rectangle") {
            cin >> a >> b;
            Rectangle R(a, b);
            totalArea += R.getArea();
            totalPerimeter += R.getPerimeter();
        }
        if(s == "Circle") {
            cin >> a >> b;
            Circle C(a, b);
            totalArea += C.getArea();
            totalPerimeter += C.getPerimeter();
        }
    }

    cout << totalArea << endl;
    cout << totalPerimeter << endl;


    return 0;
}
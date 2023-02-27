
#include "Shape.h"

Shape::Shape()
{
	cout << "Shape Ctor" << endl;
}

Shape::~Shape()
{
	cout << "Shape Dtor" << endl;
}

void Shape::SetVertexCnt(int points)
{
	_points = points;
}

int Shape::GetVertexCnt()
{
	return _points;
}

void Shape::ShowShapeInfo()
{
	cout << "Show Shape" << endl;
}

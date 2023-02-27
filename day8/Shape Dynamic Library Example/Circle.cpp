#include "pch.h"
#include "Circle.h"

Circle::Circle()
{
	cout << "Circle Ctor" << endl;
}

Circle::~Circle()
{
	cout << "Circle Dtor" << endl;
}

void Circle::ShowShapeInfo()
{
	cout << "Show Circle" << endl;
}
//class* p = new classname()
//int * p = new int[]();
DLL_DECLSPEC Shape* lib_Circle_Create()
{
	//return nullptr;
	return new Circle();
}

DLL_DECLSPEC void lib_Circle_Release(Shape* obj)
{
	if (obj != nullptr) { delete obj; obj = nullptr; }
	//return DLL_DECLSPEC void();
}

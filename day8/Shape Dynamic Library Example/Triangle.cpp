#include "pch.h"
#include "Triangle.h"

Triangle::Triangle()
{
	cout << "Triangle Ctor" << endl;
}

Triangle::~Triangle()
{
	cout << "Triangle Dtor" << endl;
}

void Triangle::ShowShapeInfo()
{
	cout << "Show Triangle" << endl;
}
//class* p = new classname()
//int * p = new int[]();
DLL_DECLSPEC Shape* lib_Triangle_Create()
{
	//return nullptr;
	return new Triangle();
}

DLL_DECLSPEC void lib_Triangle_Release(Shape* obj)
{
	if (obj != nullptr) { delete obj; obj = nullptr; }
	//return DLL_DECLSPEC void();
}


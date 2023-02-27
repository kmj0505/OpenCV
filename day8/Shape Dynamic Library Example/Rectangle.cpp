#include "pch.h"
#include "Rectangle.h"

RectangleMJ::RectangleMJ()
{
	cout << "RectangleMJ Ctor" << endl;
}

RectangleMJ::~RectangleMJ()
{
	cout << "RectangleMJ Dtor" << endl;
}

void RectangleMJ::ShowShapeInfo()
{
	cout << "Show RectangleMJ" << endl;
}
//class* p = new classname()
//int * p = new int[]();
DLL_DECLSPEC Shape* lib_RectangleMJ_Create()
{
	//return nullptr;
	return new RectangleMJ();
}

DLL_DECLSPEC void lib_RectangleMJ_Release(Shape* obj)
{
	if (obj != nullptr) { delete obj; obj = nullptr; }
	//return DLL_DECLSPEC void();
}

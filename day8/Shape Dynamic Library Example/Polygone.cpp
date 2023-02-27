#include "pch.h"
#include "Polygone.h"

Polygone::Polygone()
{
	cout << "Polygone Ctor" << endl;
}

Polygone::~Polygone()
{
	cout << "Polygone Dtor" << endl;
}

void Polygone::ShowShapeInfo()
{
	cout << "Show Polygone" << endl;
}
//class* p = new classname()
//int * p = new int[]();
DLL_DECLSPEC Shape* lib_Polygone_Create()
{
	//return nullptr;
	return new Polygone();
}

DLL_DECLSPEC void lib_Polygone_Release(Shape* obj)
{
	if (obj != nullptr) { delete obj; obj = nullptr; }
	//return DLL_DECLSPEC void();
}
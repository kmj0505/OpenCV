#pragma once

#include <iostream>
#include <string>

#ifdef DLL_EXPORTS
#define DLL_DECLSPEC __declspec(dllexport)
#else     //RELEASE
#define DLL_DECLSPEC __declspec(dllimport)
#endif
//#include "common.h"
//#include "../OpenCVApp/common.h"
//#include "Shape.h"
#include "../OpenCVApp/Shape.h"


class DLL_DECLSPEC Circle : public Shape //상속관계
{
public:
	Circle();
	~Circle();
	void ShowShapeInfo();

protected:

private:

};

extern "C"
{
	DLL_DECLSPEC Shape* lib_Circle_Create();
	DLL_DECLSPEC void lib_Circle_Release(Shape* obj);
}
#include <Windows.h>
#include "common.h"
#include "../Lib_Circle/Circle.h"
#include "../Lib_Triangle/Triangle.h"
#include "../Lib_Rectangle/Rectangle.h"
#include "../Lib_Polygone/Polygone.h"


#ifdef _DEBUG
#pragma comment(lib,"Lib_Circled.lib")
#else	//RELEASE
#pragma comment(lib,"Lib_Circle.lib")
#endif
#ifdef _DEBUG
#pragma comment(lib,"Lib_Triangled.lib")
#else	//RELEASE
#pragma comment(lib,"Lib_Triangle.lib")
#endif
#ifdef _DEBUG
#pragma comment(lib,"Lib_Rectangled.lib")
#else	//RELEASE
#pragma comment(lib,"Lib_Rectangle.lib")
#endif
#ifdef _DEBUG
#pragma comment(lib,"Lib_Polygoned.lib")
#else	//RELEASE
#pragma comment(lib,"Lib_Polygone.lib")
#endif


//function pointer type
typedef Shape* (*fpnCreate)(); //Shape* lib_Circle_Create()
typedef void (*fpRelease)(Shape* obj); //void lib_Circle_Release(Shape* obj);

int main()
{
	//function() 메모리에 올라간다
	//function() 가리키는 pointer도 있다
	//int* func() pfn

	Shape* pShape = nullptr;
	//loading dll windows lib Loadlibrary("");
	bool dynamic_loading_dll = false;
	if (dynamic_loading_dll)
	{
		HINSTANCE hModule = LoadLibrary("Lib_Circle.dll");
		if (hModule != NULL)//포인터
		{
			fpnCreate _fpCreate = (fpnCreate)GetProcAddress(hModule, "lib_Circle_Create");
			if (_fpCreate)
			{
				pShape = dynamic_cast<Circle*>(_fpCreate());
			}

			pShape->ShowShapeInfo();

			fpRelease _fpRelease = (fpRelease)GetProcAddress(hModule, "lib_Circle_Release");

			if (_fpRelease)
			{
				_fpRelease(pShape);
			}

			FreeLibrary(hModule);
		}
		

		hModule = LoadLibrary("Lib_Triangle.dll");
		if (hModule != NULL)//포인터
		{
			fpnCreate _fpCreate = (fpnCreate)GetProcAddress(hModule, "lib_Triangle_Create");
			if (_fpCreate)
			{
				pShape = dynamic_cast<Triangle*>(_fpCreate());
			}

			pShape->ShowShapeInfo();

			fpRelease _fpRelease = (fpRelease)GetProcAddress(hModule, "lib_Triangle_Release");

			if (_fpRelease)
			{
				_fpRelease(pShape);
			}

			FreeLibrary(hModule);
		}

		hModule = LoadLibrary("Lib_Rectangle.dll");
		if (hModule != NULL)//포인터
		{
			fpnCreate _fpCreate = (fpnCreate)GetProcAddress(hModule, "lib_Rectangle_Create");
			if (_fpCreate)
			{
				pShape = dynamic_cast<RectangleMJ*>(_fpCreate());
			}

			pShape->ShowShapeInfo();

			fpRelease _fpRelease = (fpRelease)GetProcAddress(hModule, "lib_Rectangle_Release");

			if (_fpRelease)
			{
				_fpRelease(pShape);
			}

			FreeLibrary(hModule);
		}

		hModule = LoadLibrary("Lib_Polygone.dll");
		if (hModule != NULL)//포인터
		{
			fpnCreate _fpCreate = (fpnCreate)GetProcAddress(hModule, "lib_Polygone_Create");
			if (_fpCreate)
			{
				pShape = dynamic_cast<Polygone*>(_fpCreate());
			}

			pShape->ShowShapeInfo();

			fpRelease _fpRelease = (fpRelease)GetProcAddress(hModule, "lib_Polygone_Release");

			if (_fpRelease)
			{
				_fpRelease(pShape);
			}

			FreeLibrary(hModule);
		}

	}
	else
	{
		//Shape* pShape = new Circle();
		//Shape* pShape = new Triangle();
		//Shape* pShape = new RectangleMJ();
		Shape* pShape = new Polygone();
		pShape->ShowShapeInfo();
		if (pShape != nullptr)
		{
			delete pShape;
			pShape = nullptr;
		}

	}
	

	return 1;
}
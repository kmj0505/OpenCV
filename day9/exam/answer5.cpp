#include <iostream>
#include <string>

using namespace std;
class IShape
{
public:
	IShape() { cout << "IShape::Ctor" << endl; }
	virtual ~IShape() { cout << "IShape::Dtor" << endl; }
	virtual int GetShape() = 0; //circle-1, rect-2
private:

};

class Circle :public IShape
{
public:
	Circle() { cout << "Circle::Ctor" << endl; }
	~Circle() { cout << "Circle::Dtor" << endl; }
	int GetShape() override { return 1; }
};

class Rect : public IShape
{
public:
	Rect() { cout << "Rect::Ctor" << endl; }
	~Rect() { cout << "Rect::Dtor" << endl; }
	int GetShape() override { return 2; }
};

int main()
{
	Circle* pCircle = new Circle;
	Rect* pRect = new Rect;
	IShape* pIShape[2] = {
		dynamic_cast<Circle*>(pCircle),
		dynamic_cast<Rect*>(pRect),
	};
	for (size_t i = 0; i < 2; i++)
	{
		cout << pIShape[i]->GetShape() << endl;
	}

	for (size_t i = 0; i < 2; i++)
	{
		if (pIShape[i] != nullptr)
		{
			delete pIShape[i];
			pIShape[i] = nullptr;
		}
	}

	return 1;
}
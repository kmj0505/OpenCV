//Quiz 4. 아래 클래스의 문제점을 고치고 정상 출력하시오
//출력
//Shape::Ctor
//Circle::Ctor
//Shape Circle
//Circle::Dtor
//Shape::Dtor

#include <iostream>
#include <string>

using namespace std;
class Shape
{
public:
	Shape() { cout << "Shape::Ctor" << endl; }//생성자
	virtual ~Shape() { cout << "Shape::Dtor" << endl; }//소멸자
	virtual void show() { cout << "Shape Default" << endl; }
	void SetValue(string str) { value = str; }
	string GetValue() { return value; }
	
private:
	string value = "Shape Circle";

};

class Circle : public Shape
{
public:
	Circle() { cout << "Circle::Ctor" << endl; }
	~Circle() { cout << "Circle::Dtor" << endl; }
	void show() override { cout << GetValue() << endl; }

private:

};

int main()
{
	Shape* pShape = new Circle();
	pShape->show();
	
	if (pShape != nullptr)
	{
		delete pShape;
		pShape = nullptr;
	}
	
	return 1;
}

//원래 문제
/*
class Shape
{
	//생성자
	//소멸자
	virtual show() { cout << "Shape Default" << endl; }
};
class Circle : public []
{
	Circle() { cout << "Circle::Ctor" << endl; }
	~Circle() { cout << "Circle::Dtor" << endl; }
	show() { cout << "Shape Circle" << endl; }
}
Circle* pShape = new Circle();
pShape->show();
delete pShape;
*/
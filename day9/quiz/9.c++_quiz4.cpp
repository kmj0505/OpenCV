//Quiz 4. �Ʒ� Ŭ������ �������� ��ġ�� ���� ����Ͻÿ�
//���
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
	Shape() { cout << "Shape::Ctor" << endl; }//������
	virtual ~Shape() { cout << "Shape::Dtor" << endl; }//�Ҹ���
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

//���� ����
/*
class Shape
{
	//������
	//�Ҹ���
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
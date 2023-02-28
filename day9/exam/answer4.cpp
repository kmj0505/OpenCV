#include <iostream>
#include <string>

using namespace std;
class Base
{
public:
	Base() {}
	virtual ~Base() {}
	virtual void Show() = 0;
};

class ChildA : public Base
{
public:
	ChildA() {}
	~ChildA() {}
	void Show() { cout << "ChildA" << endl; }

private:

};

class ChildB : public Base
{
public:
	ChildB() {}
	~ChildB() {}
	void Show() { cout << "ChildB" << endl; }

private:

};

int main()
{
	Base* pBase = dynamic_cast<Base*>(new ChildA);
	pBase->Show();
	if (pBase != nullptr)
	{
		delete pBase;
		pBase = nullptr;
	}

	pBase = dynamic_cast<Base*>(new ChildB);
	pBase->Show();

	if (pBase != nullptr)
	{
		delete pBase;
		pBase = nullptr;
	}

	return 1;
}
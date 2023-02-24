#include "Employee.h"

Employee::Employee()
{
	cout << "Employee::Ctor" << endl;
}

Employee::Employee(string name, string address,
	string phoneNum, CDate joinDate)
{
	cout << "Employee::Ctor" << endl;
	this->name = name;
	this->address = address;
	this->phoneNum = phoneNum;
	this->joinDate = joinDate;
}

void Employee::DisplayEmployee()
{
	cout << "name : " << name << endl;
	cout << "address : " << address << endl;
	cout << "phoneNum : " << phoneNum << endl;
}

Employee::~Employee()
{
	cout << "Employee::Dtor" << endl;
}

void Employee::DoWork()
{
	cout << "Employee::DoWork" << endl;
}

RegularEmployee::RegularEmployee()
{
	
}

RegularEmployee::RegularEmployee(string name, string address,
	string phoneNum, CDate joinDate, int salary)
	:Employee(name, address, phoneNum, joinDate)
{
	cout << "RegularEmployee::Ctor" << endl;
	this->salary = salary;
}

RegularEmployee::~RegularEmployee()
{
	cout << "RegularEmployee::Dtor" << endl;
}

void RegularEmployee::DoWork()
{
	cout << "RegularEmployee::DoWork" << endl;
}

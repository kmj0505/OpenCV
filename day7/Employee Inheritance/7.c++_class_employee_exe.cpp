#include "Employee.h"

int main()
{
	CDate date(2023, 2, 24);
	{
		Employee e("Parent", "Here", "000-0000-0000", date);
		e.DisplayEmployee();
		e.DoWork();
	}
	
	{
		RegularEmployee re("KCCI", "Here", "010-1234-5678",
			date, 1000);
		re.DisplayEmployee(); //?? where are you from? -> 부모 클래스에서 옴
		re.DoWork();
	
	}
	

	//parent class pointer
	//derived class pointer
	//Employee* pEmployee = &e; //int* pA = &a;
	//RegularEmployee* pReEmployee = &re;
	////Down-Casting, 다운캐스팅 -> 기본 클래스가 파생 클래스를 가리킨다.
	//pEmployee = &re;
	//pEmployee->DisplayEmployee();

	return 1;
}
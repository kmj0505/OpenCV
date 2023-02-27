#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
using namespace std;

class Shape
{
public:
	Shape(); //생성자
	virtual ~Shape(); //소멸자

	//메소드(Action function)
	void SetVertexCnt(int points);
	int GetVertexCnt();
	//순수가상함수
	//virtual void ShowShapeInfo() = 0;
	//가상함수
	virtual void ShowShapeInfo();

private:
	//멤버변수(Variables)
	int _points = 0;

};


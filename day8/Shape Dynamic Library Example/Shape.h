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
	Shape(); //������
	virtual ~Shape(); //�Ҹ���

	//�޼ҵ�(Action function)
	void SetVertexCnt(int points);
	int GetVertexCnt();
	//���������Լ�
	//virtual void ShowShapeInfo() = 0;
	//�����Լ�
	virtual void ShowShapeInfo();

private:
	//�������(Variables)
	int _points = 0;

};


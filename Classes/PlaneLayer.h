#pragma once
#include "cocos2d.h"
USING_NS_CC;

enum Enum_Plane
{
	AIRPLANE = 1,
};

class PlaneLayer : public Layer
{
public:
	PlaneLayer();

	~PlaneLayer();

	static PlaneLayer* create(); // ʵ�ִ���

	virtual bool init(); 

public:
	void checkBorder(float dt); // �߽���
	void keyBoardEvent(float dt);
	void blowUp();				// �ɻ���ը
	void removePlane();			// �Ƴ��ɻ�


public:
	static PlaneLayer* sharedPlane; // �ṩȫ�ֵ�ָ�� ���Ƶ���
	bool isAlive; // �ɻ��Ƿ����
};
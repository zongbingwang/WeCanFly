#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC; // �����ռ� using namespace cocos2d;

class HelloWorld : public cocos2d::Layer
{
public:
	// ����һ��������Ȼ��ѱ�Layer������뵽������ȥ
    static cocos2d::Scene* createScene();

    // ��Layer������Ӿ���Ԫ��
    virtual bool init();  
    
    // a selector callback �˳���ť�ص�
    void menuCloseCallback(cocos2d::Ref* pSender);
    
	// ���ľ���ʵ����ʵ����HelloWorld::create()�������CREATE_FUNC�궨����Կ���
    CREATE_FUNC(HelloWorld);

public:
	void loadingDone(Node* pNode); // �ӿ�ʼ���� ������Ϸ����
	void PreloadMusicAndPicture(); // Ԥ�������ֺ�ͼƬ

};

#endif // __HELLOWORLD_SCENE_H__

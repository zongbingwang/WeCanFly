#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC; // 命名空间 using namespace cocos2d;

class HelloWorld : public cocos2d::Layer
{
public:
	// 产生一个场景，然后把本Layer层类加入到场景中去
    static cocos2d::Scene* createScene();

    // 在Layer层中添加精灵元素
    virtual bool init();  
    
    // a selector callback 退出按钮回调
    void menuCloseCallback(cocos2d::Ref* pSender);
    
	// 它的具体实现其实就是HelloWorld::create()，你进入CREATE_FUNC宏定义可以看到
    CREATE_FUNC(HelloWorld);

public:
	void loadingDone(Node* pNode); // 从开始界面 跳到游戏界面
	void PreloadMusicAndPicture(); // 预加载音乐和图片

};

#endif // __HELLOWORLD_SCENE_H__

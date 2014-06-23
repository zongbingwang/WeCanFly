#include "AppDelegate.h"
#include "GameDirector.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director 导演
    auto director = Director::getInstance();

	// 窗体框架
    auto glview = director->getOpenGLView();
    if(!glview) {
        //glview = GLView::createWithRect("PlayerThePlane", Rect(0, 0, 480, 800)); // 窗体名 + 宽高规格
		glview = GLView::createWithFullScreen("PlayerThePlane");
		director->setOpenGLView(glview);

		// 1.LOOK 该函数会自动按设计宽高和缩放方式适应手机屏幕，设置游戏分辨率 （设计宽，设计高，缩放方式）。
		//glview->setDesignResolutionSize(480, 800, ResolutionPolicy::NO_BORDER);
    }

    // turn on display FPS 打印帧率，不希望左下角三行出现的 就注释掉 或者设置false
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this 一秒60帧
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object 创建场景
	GameDirector::Main();
  
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

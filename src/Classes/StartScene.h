#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#define TEST_OVER_SCENE 0

#if (TEST_OVER_SCENE == 1) 
#include "OverScene.h"
#endif 

#include "cocos2d.h"
#include "MainScene.h"
#include "Resouce.h"
#include "MyString.h"
#include "SimpleAudioEngine.h"

class StartScene : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

    void menuStartCallback(cocos2d::Ref * pSender);

#if (TEST_OVER_SCENE == 1)
    void overSceneCallback(cocos2d::Ref * pSender);
#endif

	// implement the "static create()" method manually
	CREATE_FUNC(StartScene);

private:
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event);
    virtual void onEnter();

	void update(float dt) override;
};

#undef TEST_OVER_SCENE

#endif // __HELLOWORLD_SCENE_H__
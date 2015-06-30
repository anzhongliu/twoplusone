#ifndef _MENU_SCENE_H_
#define _MENU_SCENE_H_

#include <iostream>
#include "cocos2d.h"
#include "MainScene.h"
#include "StartScene.h"
#include "MyString.h"
#include "Resouce.h"
#include "SimpleAudioEngine.h"

class MenuScene:public	cocos2d::Layer
{
public:

	static cocos2d::Scene* createScene();

	virtual bool init();
    

	CREATE_FUNC(MenuScene);

private:
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event);

    virtual void onEnter();

	void menuBackCallback(cocos2d::Ref* pSender);

	void menuRestartCallback(cocos2d::Ref* pSender);

	void menuBackMainCallback(cocos2d::Ref* pSender);

    void voiceSettingCallback(cocos2d::Ref * pSender);

    void initMenu(cocos2d::Node *);
    void initVioceSettingLayer(Size);

    void voiceToggleCallback(cocos2d::Ref * pSender);
    void musicToggleCallback(cocos2d::Ref * pSender);

    int nowLayer;
};

#endif // !_MENU_SCENE_H_

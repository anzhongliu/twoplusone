#ifndef __OVER_SCENE__
#define __OVER_SCENE__

#include "cocos2d.h"
#include "StartScene.h"
#include "MainScene.h"
#include "Resouce.h"
#include "SimpleAudioEngine.h"

class OverScene : public cocos2d::Layer {
public:
    static cocos2d::Scene * createScene();
    bool init();
    static void setScore(int score);

    CREATE_FUNC(OverScene);

private:
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event);

    virtual void onEnter();

    void menuRestartCallback(cocos2d::Ref * pScene);
    void menuBackToMainMenuItemCallback(cocos2d::Ref * pScene);
    void menuCloseCallback(cocos2d::Ref * pScene);
    static int _score;
};

#endif
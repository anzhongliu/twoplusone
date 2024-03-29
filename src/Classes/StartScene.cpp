﻿#include "StartScene.h"
#include "CardSprite.h"

#define TEST_OVER_SCENE 0

USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;

Scene* StartScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = StartScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	return scene;
}

// on "init" you need to initialize your instance
bool StartScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
    if (!UserDefault::getInstance()->getBoolForKey("init")) {
        UserDefault::getInstance()->setBoolForKey("init", true);
        UserDefault::getInstance()->setBoolForKey("isMusic", true);
        UserDefault::getInstance()->setBoolForKey("isVoice", true);     
    }
    Config::SoundConfig::isMusic =  UserDefault::getInstance()->getBoolForKey("isMusic");
    Config::SoundConfig::isVoice = UserDefault::getInstance()->getBoolForKey("isVoice");
    UserDefault::getInstance()->flush();
    log("%d %d", Config::SoundConfig::isMusic, Config::SoundConfig::isVoice);
	//启动音乐
    if (Config::SoundConfig::isMusic)
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic(Resource::music_bg.c_str(), true);
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//  设置背景场景
	auto bgLayer = Scale9Sprite::create(Resource::menu_bg, Rect(0, 0, 320, 480), Rect(0, 0, 320, 480));
	bgLayer->setAnchorPoint(Vec2(0, 0));
	bgLayer->setPosition(0, 0);
	bgLayer->setContentSize(Size(visibleSize.width, visibleSize.height));
	this->addChild(bgLayer);

    Vector<MenuItem *> pMenuItems;
	
	// 设置菜单
	auto pStartButton = Scale9Sprite::create(Resource::button_start, Rect(0, 0, 150, 150), Rect(5, 5, 140, 140));
	pStartButton->setContentSize(Size(visibleSize.width * Config::buttonWidthScale, visibleSize.height * Config::buttonHeightScale));
	auto pStartButtonClicked = Scale9Sprite::create(Resource::button_start_clicked, Rect(0, 0, 150, 150), Rect(5, 5, 140, 140));
	pStartButtonClicked->setContentSize(Size(visibleSize.width * Config::buttonWidthScale, visibleSize.height * Config::buttonHeightScale));
	auto pStartItem = MenuItemSprite::create(pStartButton,
		pStartButtonClicked,
		NULL,
		this,
        menu_selector(StartScene::menuStartCallback));
	// pStartItem->setContentSize(Size(120, 40));
	auto startItemLabel = Label::createWithTTF(MyString::START_MENU_START_ITEM_NAME, Config::fontStyle, visibleSize.height * Config::menuFontSizeScale);
	startItemLabel->setColor(Config::menuLabelColor);
	pStartItem->addChild(startItemLabel);
	startItemLabel->setPosition(pStartItem->getContentSize() / 2);
    pMenuItems.pushBack(pStartItem);

	auto pCloseButton = Scale9Sprite::create(Resource::button_exit, Rect(0, 0, 150, 150), Rect(5, 5, 140, 140));
	pCloseButton->setContentSize(Size(visibleSize.width * Config::buttonWidthScale, visibleSize.height * Config::buttonHeightScale));
	auto pCloseButtonClicked = Scale9Sprite::create(Resource::button_exit_clicked, Rect(0, 0, 150, 150), Rect(5, 5, 140, 140));
	pCloseButtonClicked->setContentSize(Size(visibleSize.width * Config::buttonWidthScale, visibleSize.height * Config::buttonHeightScale));
	auto pCloseItem = MenuItemSprite::create(pCloseButton,
		pCloseButtonClicked,
		NULL,
        this,
        menu_selector(StartScene::menuCloseCallback));
    auto closeItemLabel = Label::createWithTTF(MyString::START_MENU_EXIT_ITEM_NAME, Config::fontStyle, visibleSize.height * Config::menuFontSizeScale);
	pCloseItem->addChild(closeItemLabel);
	closeItemLabel->setColor(Config::menuLabelColor);
	closeItemLabel->setPosition(pCloseItem->getContentSize() / 2);
    pMenuItems.pushBack(pCloseItem);

    // 用于测试登陆按钮
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
	int flag = 0;
    bool isHave = JniHelper::getStaticMethodInfo(minfo,"org/cocos2dx/cpp/AppActivity","getLogin_flag", "()I");
       if (!isHave) {
            log("jni:login is null");
        }else{
            //调用此函数
            flag = minfo.env->CallStaticIntMethod(minfo.classID, minfo.methodID);
     }
//        auto pEditButton = Scale9Sprite::create(Resource::button_exit, Rect(0, 0, 150, 150), Rect(5, 5, 140, 140));
//                      	pEditButton->setContentSize(Size(visibleSize.width * Config::buttonWidthScale, visibleSize.height * Config::buttonHeightScale));
//                      	auto pEditButtonClicked = Scale9Sprite::create(Resource::button_exit_clicked, Rect(0, 0, 150, 150), Rect(5, 5, 140, 140));
//                      	pEditButtonClicked->setContentSize(Size(visibleSize.width * Config::buttonWidthScale, visibleSize.height * Config::buttonHeightScale));
//                      	auto pEditItem = MenuItemSprite::create(pEditButton,
//                      		pEditButtonClicked,
//                      		NULL,
//                              this,
//                              menu_selector(StartScene::menuEditCallback));
//                          auto editItemLabel = Label::createWithTTF("EDIT", Config::fontStyle, visibleSize.height * Config::menuFontSizeScale);
//                      	pEditItem->addChild(editItemLabel);
//                      	editItemLabel->setColor(Config::menuLabelColor);
//                      	editItemLabel->setPosition(pEditItem->getContentSize() / 2);
//
//              auto pLogoutButton = Scale9Sprite::create(Resource::button_exit, Rect(0, 0, 150, 150), Rect(5, 5, 140, 140));
//                       	pLogoutButton->setContentSize(Size(visibleSize.width * Config::buttonWidthScale, visibleSize.height * Config::buttonHeightScale));
//                       	auto pLogoutButtonClicked = Scale9Sprite::create(Resource::button_exit_clicked, Rect(0, 0, 150, 150), Rect(5, 5, 140, 140));
//                       	pLogoutButtonClicked->setContentSize(Size(visibleSize.width * Config::buttonWidthScale, visibleSize.height * Config::buttonHeightScale));
//                       	auto pLogoutItem = MenuItemSprite::create(pLogoutButton,
//                       		pLogoutButtonClicked,
//                       		NULL,
//                               this,
//                               menu_selector(StartScene::menuLogoutCallback));
//                           auto logoutItemLabel = Label::createWithTTF("LOGOUT", Config::fontStyle, visibleSize.height * Config::menuFontSizeScale);
//                       	pLogoutItem->addChild(logoutItemLabel);
//                       	logoutItemLabel->setColor(Config::menuLabelColor);
//                       	logoutItemLabel->setPosition(pLogoutItem->getContentSize() / 2);


      auto pLoginButton = Scale9Sprite::create(Resource::button_exit, Rect(0, 0, 150, 150), Rect(5, 5, 140, 140));
              	pLoginButton->setContentSize(Size(visibleSize.width * Config::buttonWidthScale, visibleSize.height * Config::buttonHeightScale));
              	auto pLoginButtonClicked = Scale9Sprite::create(Resource::button_exit_clicked, Rect(0, 0, 150, 150), Rect(5, 5, 140, 140));
              	pLoginButtonClicked->setContentSize(Size(visibleSize.width * Config::buttonWidthScale, visibleSize.height * Config::buttonHeightScale));
              	auto pLoginItem = MenuItemSprite::create(pLoginButton,
              		pLoginButtonClicked,
              		NULL,
                      this,
                      menu_selector(StartScene::menuLoginCallback));
                  auto loginItemLabel = Label::createWithTTF("LOGIN", Config::fontStyle, visibleSize.height * Config::menuFontSizeScale);
              	pLoginItem->addChild(loginItemLabel);
              	loginItemLabel->setColor(Config::menuLabelColor);
              	loginItemLabel->setPosition(pLoginItem->getContentSize() / 2);
              	pMenuItems.pushBack(pLoginItem);

 #endif

#if (TEST_OVER_SCENE == 1) 
    auto pOverSceneButton = Scale9Sprite::create(Resource::button_exit, Rect(0, 0, 150, 150), Rect(5, 5, 140, 140));
    pOverSceneButton->setContentSize(Size(visibleSize.width * Config::buttonWidthScale, visibleSize.height * Config::buttonHeightScale));
    auto pOverSceneButtonClicked = Scale9Sprite::create(Resource::button_exit_clicked, Rect(0, 0, 150, 150), Rect(5, 5, 140, 140));
    pOverSceneButtonClicked->setContentSize(Size(visibleSize.width * Config::buttonWidthScale, visibleSize.height * Config::buttonHeightScale));
    auto pOverItem = MenuItemSprite::create(pOverSceneButton,
        pOverSceneButtonClicked,
        NULL,
        this,
        menu_selector(StartScene::overSceneCallback));

    auto overItemLabel = Label::createWithTTF("OVER SCENE", Config::fontStyle, visibleSize.height * Config::menuFontSizeScale);
    pOverItem->addChild(overItemLabel);
    overItemLabel->setColor(Config::menuLabelColor);
    overItemLabel->setPosition(pOverItem->getContentSize() / 2);
    pMenuItems.pushBack(pOverItem);
#endif

	auto pMenu = Menu::createWithArray(pMenuItems);
	pMenu->alignItemsVerticallyWithPadding(visibleSize.height * Config::menuPaddingScale);
	bgLayer->addChild(pMenu, 1);
	// scheduleUpdate();

//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//    if(flag == 1){
//         pMenu->removeChild(pLoginItem,true);
//         pMenu->addChild(pLogoutItem);
//         pMenu->addChild(pEditItem);
//    }
//
//#endif

	return true;
}

void StartScene::update(float dt) {
	
}

void StartScene::menuCloseCallback(Ref* pSender)
{
    if (Config::SoundConfig::isVoice){
		SimpleAudioEngine::getInstance()->playEffect(Resource::effect_button.c_str(), false);
	}

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void StartScene::menuStartCallback(Ref * pSender) {
    if (Config::SoundConfig::isVoice){
		SimpleAudioEngine::getInstance()->playEffect(Resource::effect_startButton.c_str(), false);
	}
    auto mainScene = MainScene::createScene();
    // auto translate = TransitionCrossFade::create(1.0f, mainScene);
    auto translate = TransitionFlipAngular::create(1.0f, mainScene);
    Director::getInstance()->replaceScene(translate);
}

#if (TEST_OVER_SCENE == 1)
void StartScene::overSceneCallback(Ref * pSender) {
    if (Config::SoundConfig::isVoice){
		SimpleAudioEngine::getInstance()->playEffect(Resource::effect_button.c_str(), false);
	}
    auto overScene = OverScene::createScene();
    auto translate = TransitionFadeDown::create(1.0f, overScene);
    Director::getInstance()->replaceScene(translate);
}
#endif

#undef TEST_OVER_SCENE

void StartScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event) {
    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_BACKSPACE:
    case EventKeyboard::KeyCode::KEY_ESCAPE: {
        Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
#endif
        break;
    }
    }
    
}

void StartScene::onEnter() {
    Layer::onEnter();
    _eventDispatcher->removeEventListenersForType(EventListener::Type::KEYBOARD);
    auto keyListener = EventListenerKeyboard::create();
    keyListener->onKeyReleased = CC_CALLBACK_2(StartScene::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
    keyListener->setEnabled(true);
}

void StartScene::menuLoginCallback(Ref * pSender){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台
    JniMethodInfo minfo;

    bool isHave = JniHelper::getStaticMethodInfo(minfo,"org/cocos2dx/cpp/AppActivity","login", "()V");

    if (!isHave) {
        log("jni:login is null");
    }else{
        //调用此函数
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
#endif
}

void StartScene::menuEditCallback(Ref * pSender){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台
    JniMethodInfo minfo;

    bool isHave = JniHelper::getStaticMethodInfo(minfo,"org/cocos2dx/cpp/AppActivity","edit", "()V");

    if (!isHave) {
        log("jni:login is null");
    }else{
        //调用此函数
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
#endif
}

void StartScene::menuLogoutCallback(Ref * pSender){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台
    JniMethodInfo minfo;

    bool isHave = JniHelper::getStaticMethodInfo(minfo,"org/cocos2dx/cpp/AppActivity","logout", "()V");

    if (!isHave) {
        log("jni:login is null");
    }else{
        //调用此函数
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
#endif
}

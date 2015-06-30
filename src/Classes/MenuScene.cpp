#include "MenuScene.h"
#include "CardSprite.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;

Scene* MenuScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MenuScene::create();
	
	scene->addChild(layer);
	
	return scene;
}

bool MenuScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//获取可使区域尺寸大小
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto menuLayer = Scale9Sprite::create(Resource::menu_bg, Rect(0, 0, 320, 480), Rect(0, 0, 320, 480));
	menuLayer->setContentSize(visibleSize);
	menuLayer->setAnchorPoint(Vec2(0, 0));
	menuLayer->setPosition(0, 0);
	this->addChild(menuLayer);

    initMenu(menuLayer);

    _eventDispatcher->removeEventListenersForType(EventListener::Type::KEYBOARD);
    auto keyListener = EventListenerKeyboard::create();
    keyListener->onKeyReleased = CC_CALLBACK_2(MenuScene::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithFixedPriority(keyListener, 1);
    keyListener->setEnabled(true);

    initVioceSettingLayer(visibleSize);
    nowLayer = 0;
	return true;
}

void MenuScene::initMenu(Node * menuLayer) {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vector<MenuItem*> menuItems;

    auto backButton = Scale9Sprite::create(Resource::button_back, Rect(0, 0, 150, 150), Rect(5, 5, 140, 140));
    backButton->setContentSize(Size(visibleSize.width * Config::buttonWidthScale, visibleSize.height * Config::buttonHeightScale));
    auto backButtonClicked = Scale9Sprite::create(Resource::button_back_clicked, Rect(0, 0, 150, 150), Rect(5, 5, 140, 140));
    backButtonClicked->setContentSize(Size(visibleSize.width * Config::buttonWidthScale, visibleSize.height * Config::buttonHeightScale));
    auto backItem = MenuItemSprite::create(backButton,
        backButtonClicked,
        NULL,
        this,
        menu_selector(MenuScene::menuBackCallback));

    auto backItemLabel = Label::createWithTTF(MyString::MENU_SCENE_BACK_ITEM_NAME, Config::fontStyle, visibleSize.height * Config::menuFontSizeScale);
    backItemLabel->setColor(Config::menuLabelColor);
    backItem->addChild(backItemLabel);
    backItemLabel->setPosition(backItem->getContentSize() / 2);
    menuItems.pushBack(backItem);

    auto voiceButton = Scale9Sprite::create(Resource::button_voice_setting, Rect(0, 0, 150, 150), Rect(5, 5, 140, 140));
    voiceButton->setContentSize(Size(visibleSize.width * Config::buttonWidthScale, visibleSize.height * Config::buttonHeightScale));
    auto voiceButtonClicked = Scale9Sprite::create(Resource::button_voice_setting_clicked, Rect(0, 0, 150, 150), Rect(5, 5, 140, 140));
    voiceButtonClicked->setContentSize(Size(visibleSize.width * Config::buttonWidthScale, visibleSize.height * Config::buttonHeightScale));
    auto voiceItem = MenuItemSprite::create(voiceButton,
        voiceButtonClicked,
        NULL,
        this,
        menu_selector(MenuScene::voiceSettingCallback));

    auto voiceItemLabel = Label::createWithTTF(MyString::VOICE_SETTING_LAYER_BUTTON, Config::fontStyle, visibleSize.height * Config::menuFontSizeScale);
    voiceItemLabel->setColor(Config::menuLabelColor);
    voiceItem->addChild(voiceItemLabel);
    voiceItemLabel->setPosition(voiceItem->getContentSize() / 2);
    menuItems.pushBack(voiceItem);

    auto restartButton = Scale9Sprite::create(Resource::button_restart, Rect(0, 0, 150, 150), Rect(5, 5, 140, 140));
    restartButton->setContentSize(Size(visibleSize.width * Config::buttonWidthScale, visibleSize.height * Config::buttonHeightScale));
    auto restartButtonClicked = Scale9Sprite::create(Resource::button_restart_clicked, Rect(0, 0, 150, 150), Rect(5, 5, 140, 140));
    restartButtonClicked->setContentSize(Size(visibleSize.width * Config::buttonWidthScale, visibleSize.height * Config::buttonHeightScale));
    auto restartItem = MenuItemSprite::create(restartButton,
        restartButtonClicked,
        NULL,
        this,
        menu_selector(MenuScene::menuRestartCallback));

    auto restartItemLabel = Label::createWithTTF(MyString::MENU_SCENE_RESTART_ITEM_NAME, Config::fontStyle, visibleSize.height * Config::menuFontSizeScale);
    restartItemLabel->setColor(Config::menuLabelColor);
    restartItem->addChild(restartItemLabel);
    restartItemLabel->setPosition(restartItem->getContentSize() / 2);
    menuItems.pushBack(restartItem);

    auto backToMainButton = Scale9Sprite::create(Resource::button_back_to_main, Rect(0, 0, 150, 150), Rect(5, 5, 140, 140));
    backToMainButton->setContentSize(Size(visibleSize.width * Config::buttonWidthScale, visibleSize.height * Config::buttonHeightScale));
    auto backToMainButtonClicked = Scale9Sprite::create(Resource::button_back_to_main_clicked, Rect(0, 0, 150, 150), Rect(5, 5, 140, 140));
    backToMainButtonClicked->setContentSize(Size(visibleSize.width * Config::buttonWidthScale, visibleSize.height * Config::buttonHeightScale));
    auto backMainItem = MenuItemSprite::create(backToMainButton,
        backToMainButtonClicked,
        NULL,
        this,
        menu_selector(MenuScene::menuBackMainCallback));

    auto backMainItemLabel = Label::createWithTTF(MyString::MENU_SCENE_BACK_MAIN_ITEM_NAME, Config::fontStyle, visibleSize.height * Config::menuFontSizeScale);
    backMainItemLabel->setColor(Config::menuLabelColor);
    backMainItem->addChild(backMainItemLabel);
    backMainItemLabel->setPosition(backMainItem->getContentSize() / 2);
    menuItems.pushBack(backMainItem);

    auto menu = Menu::createWithArray(menuItems);
    menu->alignItemsVerticallyWithPadding(visibleSize.height * Config::menuPaddingScale);
    menuLayer->addChild(menu);
}

void MenuScene::initVioceSettingLayer(Size visibleSize) {
    auto voiceSettingLayer = Scale9Sprite::create(Resource::menu_bg, Rect(0, 0, 320, 480), Rect(0, 0, 320, 480));
    voiceSettingLayer->setContentSize(visibleSize);
    voiceSettingLayer->setAnchorPoint(Vec2(0, 0));
    voiceSettingLayer->setPosition(Vec2(visibleSize.width, 0));

    auto item = MenuItemLabel::create(Label::create("Voice On", Config::fontStyle, visibleSize.height * Config::menuFontSizeScale));
    auto item2 = MenuItemLabel::create(Label::create("Voice Off", Config::fontStyle, visibleSize.height * Config::menuFontSizeScale));
    item->setColor(Config::voiceLayerLabelColor);
    item2->setColor(Config::voiceLayerLabelColor);
    MenuItemToggle * toggleMenu;
    if (Config::SoundConfig::isVoice){
        toggleMenu = MenuItemToggle::createWithCallback(CC_CALLBACK_1(MenuScene::voiceToggleCallback, this), item, item2, NULL);
    }
    else {
        toggleMenu = MenuItemToggle::createWithCallback(CC_CALLBACK_1(MenuScene::voiceToggleCallback, this), item2, item, NULL);
    }
     
    auto item3 = MenuItemLabel::create(Label::create("Music On", Config::fontStyle, visibleSize.height * Config::menuFontSizeScale));
    auto item4 = MenuItemLabel::create(Label::create("Music Off", Config::fontStyle, visibleSize.height * Config::menuFontSizeScale));
    item3->setColor(Config::voiceLayerLabelColor);
    item4->setColor(Config::voiceLayerLabelColor);
    MenuItemToggle * toggleMenu1;
    if (Config::SoundConfig::isMusic){
        toggleMenu1 = MenuItemToggle::createWithCallback(CC_CALLBACK_1(MenuScene::musicToggleCallback, this), item3, item4, NULL);
    }
    else {
        toggleMenu1 = MenuItemToggle::createWithCallback(CC_CALLBACK_1(MenuScene::musicToggleCallback, this), item4, item3, NULL);
    }

    auto menuItem = MenuItemLabel::create(Label::create(MyString::MENU_SCENE_BACK_ITEM_NAME, Config::fontStyle, Config::menuFontSizeScale * visibleSize.height), CC_CALLBACK_1(MenuScene::voiceSettingCallback, this) );
    menuItem->setColor(Config::voiceLayerLabelColor);

    auto menu = Menu::create(menuItem, toggleMenu, toggleMenu1, NULL);
    
    menu->alignItemsVerticallyWithPadding(visibleSize.height * Config::menuPaddingScale);

    voiceSettingLayer->addChild(menu);

    this->addChild(voiceSettingLayer, 2, "voiceSettingLayer");
}

void MenuScene::voiceToggleCallback(Ref * pSender) {
    if (!Config::SoundConfig::isVoice){
		SimpleAudioEngine::getInstance()->playEffect(Resource::effect_toggleButton.c_str(), false);
	}
    if (Config::SoundConfig::isVoice) {
        Config::SoundConfig::isVoice = false;
        UserDefault::getInstance()->setBoolForKey("isVoice", false);
    }
    else {
        Config::SoundConfig::isVoice = true;
        UserDefault::getInstance()->setBoolForKey("isVoice", true);

    }
    UserDefault::getInstance()->flush();
}

void MenuScene::musicToggleCallback(Ref * pSender) {
    if (Config::SoundConfig::isVoice){
		SimpleAudioEngine::getInstance()->playEffect(Resource::effect_toggleButton.c_str(), false);
	}
    if (Config::SoundConfig::isMusic) {
        Config::SoundConfig::isMusic = false;
        SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        UserDefault::getInstance()->setBoolForKey("isMusic", false);
        
    }
    else {
        Config::SoundConfig::isMusic = true;
        SimpleAudioEngine::getInstance()->playBackgroundMusic(Resource::music_bg.c_str(), true);
        UserDefault::getInstance()->setBoolForKey("isMusic", true);

    }
    UserDefault::getInstance()->flush();
}

void MenuScene::menuBackCallback(Ref* pSender)
{
	//Director::getInstance()->popSceneWithTransition<TransitionSlideInT>(1.0);
    if (Config::SoundConfig::isVoice){
		SimpleAudioEngine::getInstance()->playEffect(Resource::effect_button.c_str(), false);
	}
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    this->runAction(Sequence::create(
        MoveTo::create(
        0.3f,
        Vec2(visibleSize.width, 0)
        ),
        CallFunc::create([](){
        Director::getInstance()->popScene();

    }),
        NULL
        ));
}

void MenuScene::menuRestartCallback(Ref* pSender)
{
    if (Config::SoundConfig::isVoice){
		SimpleAudioEngine::getInstance()->playEffect(Resource::effect_button.c_str(), false);
	}
	auto mainScene = MainScene::createScene();
	auto translate = TransitionFlipX::create(1.0f, mainScene);
	Director::getInstance()->replaceScene(translate);
}

void MenuScene::menuBackMainCallback(Ref* pSender)
{
    if (Config::SoundConfig::isVoice){
		SimpleAudioEngine::getInstance()->playEffect(Resource::effect_button.c_str(), false);
	}
	auto startScene = StartScene::createScene();
    auto translate = TransitionFlipAngular::create(1.0f, startScene);
	Director::getInstance()->replaceScene(translate);
}

void MenuScene::voiceSettingCallback(Ref * pSender) {
    if (Config::SoundConfig::isVoice){
		SimpleAudioEngine::getInstance()->playEffect(Resource::effect_button.c_str(), false);
	}
    Size visibleSize = Director::getInstance()->getVisibleSize();
    if (nowLayer == 0) {
        nowLayer = 1;
        this->stopAllActions();
        this->runAction(MoveTo::create(
            0.3f,
            Vec2(-visibleSize.width, 0)
            ));
    }
    else {
        nowLayer = 0;
        this->stopAllActions();
        this->runAction(MoveTo::create(
            0.3f,
            Vec2(0, 0)
            ));
    }
    
}

void MenuScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event) {
    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_BACKSPACE:
    case EventKeyboard::KeyCode::KEY_ESCAPE: {
        if (nowLayer == 1) {
            nowLayer = 0;
            this->stopAllActions();
            this->runAction(MoveTo::create(
                0.3f,
                Vec2(0, 0)
                ));
            return;
        }
        auto visibleSize = Director::getInstance()->getVisibleSize();

        this->runAction(Sequence::create(
            MoveTo::create(
                0.3f,
                Vec2(visibleSize.width, 0)
            ),
            CallFunc::create([](){
                MainScene::keyboardFlag = false;
                Director::getInstance()->popScene();
                
            }),
            NULL
            ));
        break;
    }
    }
}

void MenuScene::onEnter() {
    Layer::onEnter();
    _eventDispatcher->removeEventListenersForType(EventListener::Type::KEYBOARD);
    auto keyListener = EventListenerKeyboard::create();
    keyListener->onKeyPressed = CC_CALLBACK_2(MenuScene::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
    keyListener->setEnabled(true); 
}
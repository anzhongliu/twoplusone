#include "OverScene.h"
#include "CardSprite.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;

Scene * OverScene::createScene() {
    auto scene = Scene::create();
    auto layer = OverScene::create();
    
    scene->addChild(layer);
    return scene;
}

bool OverScene::init() {
    if (!Layer::init()) {
        return false;
    }
	
	if (Config::SoundConfig::isMusic){
		SimpleAudioEngine::getInstance()->playBackgroundMusic(Resource::music_bg_2.c_str(), true);
	}

    auto visibleSize = Director::getInstance()->getVisibleSize();

    //  设置背景场景
	auto bgLayer = Scale9Sprite::create(Resource::menu_bg, Rect(0, 0, 320, 480), Rect(0, 0, 320, 480));
	bgLayer->setContentSize(visibleSize);
	bgLayer->setAnchorPoint(Vec2(0, 0));
	bgLayer->setPosition(0, 0);
    this->addChild(bgLayer);
    
    auto scoreLabel = Label::createWithTTF(__String::createWithFormat("%d", _score)->getCString(), Config::fontStyle, visibleSize.height * Config::scoreFontSizeScale);
    scoreLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 5 * 4));
	scoreLabel->setColor(Config::scoreLabelColor);
    this->addChild(scoreLabel, 1, "scoreLabel");

	auto restartButton = Scale9Sprite::create(Resource::button_restart, Rect(0, 0, 150, 150), Rect(5, 5, 140, 140));
	restartButton->setContentSize(Size(visibleSize.width * Config::buttonWidthScale, visibleSize.height * Config::buttonHeightScale));
	auto restartButtonClicked = Scale9Sprite::create(Resource::button_restart_clicked, Rect(0, 0, 150, 150), Rect(5, 5, 140, 140));
	restartButtonClicked->setContentSize(Size(visibleSize.width * Config::buttonWidthScale, visibleSize.height * Config::buttonHeightScale));
	auto restartMenuItem = MenuItemSprite::create(restartButton,
		restartButtonClicked,
		NULL,
		this,
		menu_selector(OverScene::menuRestartCallback));
    auto restartItemLabel = Label::createWithTTF(MyString::MENU_SCENE_RESTART_ITEM_NAME, Config::fontStyle, visibleSize.height * Config::menuFontSizeScale);
	restartItemLabel->setColor(Config::menuLabelColor);
	restartMenuItem->addChild(restartItemLabel);
	restartItemLabel->setPosition(restartMenuItem->getContentSize() / 2);

	auto backToMainButton = Scale9Sprite::create(Resource::button_back_to_main, Rect(0, 0, 150, 150), Rect(5, 5, 140, 140));
	backToMainButton->setContentSize(Size(visibleSize.width * Config::buttonWidthScale, visibleSize.height * Config::buttonHeightScale));
	auto backToMainButtonClicked = Scale9Sprite::create(Resource::button_back_to_main_clicked, Rect(0, 0, 150, 150), Rect(5, 5, 140, 140));
	backToMainButtonClicked->setContentSize(Size(visibleSize.width * Config::buttonWidthScale, visibleSize.height * Config::buttonHeightScale));
	auto backToMainMenuItem = MenuItemSprite::create(backToMainButton,
		backToMainButtonClicked,
		NULL,
		this,
		menu_selector(OverScene::menuBackToMainMenuItemCallback));
    auto backToMainMenuItemLabel = Label::createWithTTF(MyString::MENU_SCENE_BACK_MAIN_ITEM_NAME, Config::fontStyle, visibleSize.height * Config::menuFontSizeScale);
	backToMainMenuItemLabel->setColor(Config::menuLabelColor);
	backToMainMenuItem->addChild(backToMainMenuItemLabel);
	backToMainMenuItemLabel->setPosition(backToMainMenuItem->getContentSize() / 2);

	auto exitButton = Scale9Sprite::create(Resource::button_exit, Rect(0, 0, 150, 150), Rect(5, 5, 140, 140));
	exitButton->setContentSize(Size(visibleSize.width * Config::buttonWidthScale, visibleSize.height * Config::buttonHeightScale));
	auto exitButtonClicked = Scale9Sprite::create(Resource::button_exit_clicked, Rect(0, 0, 150, 150), Rect(5, 5, 140, 140));
	exitButtonClicked->setContentSize(Size(visibleSize.width * Config::buttonWidthScale, visibleSize.height * Config::buttonHeightScale));
	auto pCloseItem = MenuItemSprite::create(exitButton,
		exitButtonClicked,
		NULL,
        this,
        menu_selector(StartScene::menuCloseCallback));
    auto closeItemLabel = Label::createWithTTF(MyString::START_MENU_EXIT_ITEM_NAME, Config::fontStyle, visibleSize.height * Config::menuFontSizeScale);
	closeItemLabel->setColor(Config::menuLabelColor);
	pCloseItem->addChild(closeItemLabel);
	closeItemLabel->setPosition(pCloseItem->getContentSize() / 2);

    auto menu = Menu::create(restartMenuItem, backToMainMenuItem, pCloseItem, NULL);
	menu->alignItemsVerticallyWithPadding(visibleSize.height * Config::menuPaddingScale);
    bgLayer->addChild(menu);

    _eventDispatcher->removeEventListenersForType(EventListener::Type::KEYBOARD);
    auto keyListener = EventListenerKeyboard::create();
    keyListener->onKeyReleased = CC_CALLBACK_2(OverScene::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithFixedPriority(keyListener, 1);
    keyListener->setEnabled(true);
    return true;
}

void OverScene::menuRestartCallback(Ref * pScene) {
    if (Config::SoundConfig::isVoice){
		SimpleAudioEngine::getInstance()->playEffect(Resource::effect_button.c_str(), false);
	}
    auto mainScene = MainScene::createScene();
    auto translate = TransitionFlipX::create(1.0f, mainScene);
    Director::getInstance()->replaceScene(translate);
}

void OverScene::menuBackToMainMenuItemCallback(Ref * pScene) {
    if (Config::SoundConfig::isVoice){
		SimpleAudioEngine::getInstance()->playEffect(Resource::effect_button.c_str(), false);
	}
    auto startScene = StartScene::createScene();
    auto translate = TransitionFlipAngular::create(1.0f, startScene);
    Director::getInstance()->replaceScene(translate);
}

int OverScene::_score = 0;

void OverScene::setScore(int score) {
    _score = score;
}

void OverScene::menuCloseCallback(Ref* pSender) {
    if (Config::SoundConfig::isVoice){
		SimpleAudioEngine::getInstance()->playEffect(Resource::effect_button.c_str(), false);
	}

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void OverScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event) {
    switch(keyCode) {
    case EventKeyboard::KeyCode::KEY_BACKSPACE:
    case EventKeyboard::KeyCode::KEY_ESCAPE: {
        auto startScene = StartScene::createScene();
        auto translate = TransitionFlipAngular::create(1.0f, startScene);
        Director::getInstance()->replaceScene(translate);
        return;
    }
    }
}

void OverScene::onEnter() {
    Layer::onEnter();
    _eventDispatcher->removeEventListenersForType(EventListener::Type::KEYBOARD);
    auto keyListener = EventListenerKeyboard::create();
    keyListener->onKeyPressed = CC_CALLBACK_2(OverScene::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
    keyListener->setEnabled(true);
    
}
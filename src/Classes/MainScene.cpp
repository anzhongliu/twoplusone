#include "MainScene.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;

Scene * MainScene::createScene() {
    auto scene = Scene::create();
    auto layer = MainScene::create();
    scene->addChild(layer);
    return scene;
}

bool MainScene::keyboardFlag = true;

bool MainScene::init() {
    if (!Layer::init()) {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    this->cardMoveOffset = visibleSize.height * Config::cardMoveOffsetScale;

    // 初始化游戏层
    initGameScene(visibleSize, origin);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            activeCardArr[i][j] = NULL;
        }
    }

	initPreviewCard(visibleSize);

	//设置种子
	srand(time(NULL));

    // 初始化卡片
    initCard(visibleSize, origin);

    this->isScrollable = true;

    // 设置触摸监听事件
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(MainScene::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(MainScene::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(MainScene::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    touchListener->setSwallowTouches(true);

    return true;
}

void MainScene::initPreviewCard(Size visibleSize) {
	preview_card_1 = Scale9Sprite::create(Resource::card_1, Rect(0, 0, 150, 150), Rect(5, 5, 140, 140));
	preview_card_2 = Scale9Sprite::create(Resource::card_2, Rect(0, 0, 150, 150), Rect(5, 5, 140, 140));
	preview_card_3 = Scale9Sprite::create(Resource::card_3, Rect(0, 0, 150, 150), Rect(5, 5, 140, 140));

	preview_card_1->setContentSize(Size(visibleSize.width * Config::menuButtonWidthScale, visibleSize.height * Config::menuButtonHeightScale));
	preview_card_2->setContentSize(Size(visibleSize.width * Config::menuButtonWidthScale, visibleSize.height * Config::menuButtonHeightScale));
	preview_card_3->setContentSize(Size(visibleSize.width * Config::menuButtonWidthScale, visibleSize.height * Config::menuButtonHeightScale));

	preview_card_1->setPosition(visibleSize.width / 2, visibleSize.height * (1 - Config::menuButtonTopScale) - preview_card_1->getContentSize().height / 2);
	preview_card_2->setPosition(visibleSize.width / 2, visibleSize.height * (1 - Config::menuButtonTopScale) - preview_card_2->getContentSize().height / 2);
	preview_card_3->setPosition(visibleSize.width / 2, visibleSize.height * (1 - Config::menuButtonTopScale) - preview_card_3->getContentSize().height / 2);

	preview_card_1->setVisible(false);
	preview_card_2->setVisible(false);
	preview_card_3->setVisible(false);

    auto label = Label::createWithTTF(MyString::NEXT_BUTTON, Config::fontStyle, visibleSize.height * Config::menuFontSizeScale);
	label->setPosition(visibleSize.width / 2, visibleSize.height * (1 - Config::menuButtonTopScale)  - preview_card_3->getContentSize().height / 2);
	label->setColor(Config::menuLabelColor);

	this->addChild(preview_card_1, 1);
	this->addChild(preview_card_2, 1);
	this->addChild(preview_card_3, 1);
	this->addChild(label, 1);
}

void MainScene::initGameScene(const Size & visibleSize, const Vec2 & origin) {
	
	auto background = Scale9Sprite::create(Resource::menu_bg, Rect(0, 0, 320, 480), Rect(0, 0, 320, 480));
	background->setContentSize(visibleSize);
	background->setAnchorPoint(Vec2(0, 0));
	background->setPosition(0, 0);
	this->addChild(background, 0);



	auto gameLayer = Scale9Sprite::create(Resource::gameLayer_bg, Rect(0, 0, 150, 150), Rect(5, 5, 140, 140));
    gameLayer->ignoreAnchorPointForPosition(false);
    gameLayer->setAnchorPoint(Vec2(0.5, 0));
	gameLayer->setContentSize(Size(visibleSize.width * Config::gameLayerSizeWidthScale, visibleSize.height * Config::gameLayerSizeHeightScale));
    gameLayer->setPosition(visibleSize.width / 2, visibleSize.height / 10);
    this->addChild(gameLayer, 1, "gameLayer");

	this->gameLayerSize = Vec2(visibleSize.width * Config::gameLayerSizeWidthScale, visibleSize.height * Config::gameLayerSizeHeightScale);
	this->cardWidth = gameLayerSize.x / 6;
	this->cardHeight = gameLayerSize.y / 6;
	this->cardWidthPadding = gameLayerSize.x * Config::GameLayerCardSpacingScale;
	this->cardHeightPadding = gameLayerSize.y * Config::GameLayerCardSpacingScale;

    Vec2 centerPos = gameLayerSize / 2 + gameLayer->getPosition();
    float widthSpace = (gameLayerSize.x - gameLayerSize.x * 4 * Config::cardSizeScale - gameLayerSize.x * Config::GameLayerCardSpacingScale * 3) / 2;
	float heightSpace = (gameLayerSize.y - gameLayerSize.y * 4 * Config::cardSizeScale - gameLayerSize.y * Config::GameLayerCardSpacingScale * 3) / 2;
    
	//菜单栏
	auto menuButton = Scale9Sprite::create(Resource::button_menu, Rect(0, 0, 150, 150), Rect(5, 5, 140, 140));
	menuButton->setContentSize(Size(visibleSize.width * Config::menuButtonWidthScale, visibleSize.height * Config::menuButtonHeightScale));
	auto menuButtonClicked = Scale9Sprite::create(Resource::button_menu_clicked, Rect(0, 0, 150, 150), Rect(5, 5, 140, 140));
	menuButtonClicked->setContentSize(Size(visibleSize.width * Config::menuButtonWidthScale, visibleSize.height * Config::menuButtonHeightScale));
	auto item = MenuItemSprite::create(
		menuButton,
		menuButtonClicked,
		NULL,
		this,
		menu_selector(MainScene::menuClickCallback));
	auto menuLabel = Label::create(MyString::MENU_BUTTON, Config::fontStyle, visibleSize.height * Config::menuFontSizeScale);
	menuLabel->setColor(Config::menuLabelColor);
	item->addChild(menuLabel);
	menuLabel->setPosition(item->getContentSize() / 2);
	auto menu = Menu::create(item, NULL);
	this->addChild(menu,1);
	menu->setAnchorPoint(Vec2(0, 0));
	menu->setPosition(0, 0);
	item->setAnchorPoint(Vec2(1, 1));
	item->setPosition(visibleSize.width - (visibleSize.width - this->gameLayerSize.x) / 2, visibleSize.height * (1 - Config::menuButtonTopScale));

	int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            auto card = CardSprite::createCardSprite(0,
                Vec2(widthSpace, heightSpace) + Vec2((gameLayerSize.x * Config::cardSizeScale + gameLayerSize.x * Config::GameLayerCardSpacingScale)* i,
				(gameLayerSize.y * Config::cardSizeScale + gameLayerSize.y * Config::GameLayerCardSpacingScale) * j),
                gameLayerSize * Config::cardSizeScale
                );
            staticCardArr[i][j] = card;
            gameLayer->addChild(card);
        }
    }
}

void MainScene::initCard(const Size & visibleSize, const Vec2 & origin) {
	int i;
    for (i = 0; i < 9; i++) {
        int random = CCRANDOM_0_1() * 16;
		setCard(random, visibleSize, origin);
    }
	duplicateLevel[0] = 0;
	duplicateLevel[1] = 0;
	updateCardArr();

}

void MainScene::setCard(int pos, const Size & visibleSize, const Vec2 & origin) {
    int i = pos / 4, j = pos % 4;
    if (activeCardArr[i][j] == NULL) {
        int num = CCRANDOM_0_1() * 3 + 1;
        // 处理锚点偏差
        auto card = CardSprite::createCardSprite(num, Vec2(0, 0), gameLayerSize * Config::cardSizeScale);
        card->setPosition(staticCardArr[i][j]->getPosition());
        activeCardArr[i][j] = card;
        this->getChildByName("gameLayer")->addChild(card, 1);
        return;
    }
    while (activeCardArr[i][j] != NULL) {
        if (pos < 15) {
            pos++;
        }
        else {
            pos = 0;
        }
        i = pos / 4;
        j = pos % 4;
    }
	int num = CCRANDOM_0_1() * 3 + 1;
	// 处理锚点偏差
	auto card = CardSprite::createCardSprite(num, Vec2(0, 0), gameLayerSize * Config::cardSizeScale);
    card->setPosition(staticCardArr[i][j]->getPosition());
	activeCardArr[i][j] = card;
	this->getChildByName("gameLayer")->addChild(card, 1);
}

bool MainScene::onTouchBegan(Touch * touch, Event * event) {
    if (isScrollable) {
		isScrollable = false;
		scroll = 0;
        return true;
    }
    return false;
}

void MainScene::onTouchEnded(Touch * touch, Event * event) {

    switch (scroll) {
    case Config::right:{
        if (rightcardarr.empty()){
            isScrollable = true;
            return;
        }
        {
            int i, j;
            i = rightcardarr.begin()->i;
            j = rightcardarr.begin()->j;
            if (activeCardArr[i][j]->getPositionX() < (staticCardArr[i + 1][j]->getPositionX() + staticCardArr[i][j]->getPositionX() ) / 2) {
                for (auto index : rightcardarr) {
                    activeCardArr[index.i][index.j]->runAction(MoveTo::create(0.3f, Vec2(staticCardArr[index.i][index.j]->getPosition())));
					
				}
				if (Config::SoundConfig::isVoice){
					SimpleAudioEngine::getInstance()->playEffect(Resource::effect_move_back.c_str(), false);
				}
                isScrollable = true;
                return;
            }
        }
        for (auto index : rightcardarr){
            activeCardArr[index.i][index.j]->stopActionByTag(1);
            if (activeCardArr[index.i + 1][index.j] != NULL){
                auto card = MainScene::operationPlus(index.i, index.j, Config::right);
                this->getChildByName("gameLayer")->removeChild(activeCardArr[index.i][index.j]);
                this->getChildByName("gameLayer")->removeChild(activeCardArr[index.i + 1][index.j]);
                activeCardArr[index.i + 1][index.j]->release();
                activeCardArr[index.i][index.j]->release();
                activeCardArr[index.i][index.j] = NULL;
                activeCardArr[index.i + 1][index.j] = card;

                this->getChildByName("gameLayer")->addChild(card, 1);
                card->setRotation3D(Vec3(0, 180, 0));
                card->runAction(RotateBy::create(0.3f, Vec3(0, 180, 0)));
            }
            else{
                activeCardArr[index.i + 1][index.j] = activeCardArr[index.i][index.j];
                auto moveTo = MoveTo::create(
                    0.3f,
                    staticCardArr[index.i + 1][index.j]->getPosition()
                    );
                moveTo->setTag(1);
                activeCardArr[index.i + 1][index.j]->runAction(moveTo);
                activeCardArr[index.i][index.j] = NULL;

            }
        }

        int j = CCRANDOM_0_1() * 4;
        while (activeCardArr[0][j] != NULL){
            if (j > 2)
            {
                j = 0;
            }
            else
                j++;
        }
        CardSprite* card = (CardSprite*)this->getChildByName("gameLayer")->getChildByName("newCard");
        card->setPosition(staticCardArr[0][j]->getPosition());
        card->setName("");
		card->setScaleX(0.1);
		card->setScaleY(0.1);
		auto scaleAction = ScaleTo::create(0.3, 1.0, 1.0, 0);
		card->setVisible(true);
		card->runAction(scaleAction);
        activeCardArr[0][j] = (CardSprite*)card;
        break;
    }
    case Config::left:{
        if (leftcardarr.empty()){
        	isScrollable = true;
        	return;
        }
        {
            int i, j;
            i = leftcardarr.begin()->i;
            j = leftcardarr.begin()->j;
            if (activeCardArr[i][j]->getPositionX() > (staticCardArr[i - 1][j]->getPositionX() + staticCardArr[i][j]->getPositionX()) / 2) {
				for (auto index : leftcardarr) {
					activeCardArr[index.i][index.j]->runAction(MoveTo::create(0.3f, Vec2(staticCardArr[index.i][index.j]->getPosition())));

				}
				if (Config::SoundConfig::isVoice){
					SimpleAudioEngine::getInstance()->playEffect(Resource::effect_move_back.c_str(), false);
				}
                isScrollable = true;
                return;
            }
        }
        for (auto index : leftcardarr){
            activeCardArr[index.i][index.j]->stopActionByTag(1);
        	if (activeCardArr[index.i - 1][index.j] != NULL){
        		auto card = MainScene::operationPlus(index.i, index.j, Config::left);
        		this->getChildByName("gameLayer")->removeChild(activeCardArr[index.i - 1][index.j]);
        		this->getChildByName("gameLayer")->removeChild(activeCardArr[index.i][index.j]);
        		activeCardArr[index.i - 1][index.j]->release();
        		activeCardArr[index.i][index.j]->release();
        		activeCardArr[index.i][index.j] = NULL;
        		activeCardArr[index.i - 1][index.j] = card;	
                card->setRotation3D(Vec3(0, 180, 0));
        		this->getChildByName("gameLayer")->addChild(card, 1);
                card->runAction(RotateBy::create(0.3f, Vec3(0, 180, 0)));
        	}
        	else{
                activeCardArr[index.i - 1][index.j] = activeCardArr[index.i][index.j];
                auto moveTo = MoveTo::create(
                    0.3f,
                    staticCardArr[index.i - 1][index.j]->getPosition()
                    );
                moveTo->setTag(1);
                activeCardArr[index.i - 1][index.j]->runAction(moveTo);
                activeCardArr[index.i][index.j] = NULL;
			}
        }

        int j = CCRANDOM_0_1() * 4;
        while (activeCardArr[3][j] != NULL){
        	if (j > 2)
        	{
        		j = 0;
        	}
        	else
        		j++;
        }
        CardSprite* card = (CardSprite*)this->getChildByName("gameLayer")->getChildByName("newCard");
        card->setPosition(staticCardArr[3][j]->getPosition());
        card->setName("");
		card->setScaleX(0.1);
		card->setScaleY(0.1);
		auto scaleAction = ScaleTo::create(0.3, 1.0, 1.0, 0);
		card->setVisible(true);
		card->runAction(scaleAction);
		activeCardArr[3][j] = (CardSprite*)card;
        break;
    }
    case Config::up:{
        if (upcardarr.empty()){
        	isScrollable = true;
        	return;
        }
        {
            int i, j;
            i = upcardarr.begin()->i;
            j = upcardarr.begin()->j;
            if (activeCardArr[i][j]->getPositionY() < (staticCardArr[i][j + 1]->getPositionY() + staticCardArr[i][j]->getPositionY()) / 2) {
                for (auto index : upcardarr) {
                    activeCardArr[index.i][index.j]->runAction(MoveTo::create(0.1f, Vec2(staticCardArr[index.i][index.j]->getPosition())));
                
				}
				if (Config::SoundConfig::isVoice){
					SimpleAudioEngine::getInstance()->playEffect(Resource::effect_move_back.c_str(), false);
				}
                isScrollable = true;
                return;
            }
        }
        for (auto index : upcardarr){
            activeCardArr[index.i][index.j]->stopActionByTag(1);
        	if (activeCardArr[index.i][index.j + 1] != NULL){
        		auto card = MainScene::operationPlus(index.i, index.j, Config::up);
        		this->getChildByName("gameLayer")->removeChild(activeCardArr[index.i][index.j + 1]);
        		this->getChildByName("gameLayer")->removeChild(activeCardArr[index.i][index.j]);
        		activeCardArr[index.i][index.j + 1]->release();
        		activeCardArr[index.i][index.j]->release();
        		activeCardArr[index.i][index.j] = NULL;
        		activeCardArr[index.i][index.j + 1] = card;
        		this->getChildByName("gameLayer")->addChild(card, 1);
                card->setRotation3D(Vec3(0, 180, 0));
                card->runAction(RotateBy::create(0.3f, Vec3(0, 180, 0)));
        	}
        	else{
                activeCardArr[index.i][index.j + 1] = activeCardArr[index.i][index.j];
                auto moveTo = MoveTo::create(
                    0.3f,
                    staticCardArr[index.i][index.j + 1]->getPosition()
                    );
                moveTo->setTag(1);
                activeCardArr[index.i][index.j + 1]->runAction(moveTo);
                activeCardArr[index.i][index.j] = NULL;

        	}
        }

        int i = CCRANDOM_0_1() * 4;
        while (activeCardArr[i][0] != NULL){
        	if (i > 2)
        	{
        		i = 0;
        	}
        	else
        		i++;
        }
        CardSprite* card = (CardSprite*)this->getChildByName("gameLayer")->getChildByName("newCard");
        card->setPosition(staticCardArr[i][0]->getPosition());
        card->setName("");
		card->setScaleX(0.1);
		card->setScaleY(0.1);
		auto scaleAction = ScaleTo::create(0.3, 1.0, 1.0, 0);
		card->setVisible(true);
		card->runAction(scaleAction);
		activeCardArr[i][0] = (CardSprite*)card;
        break;
    }
    case Config::down:{
        if (downcardarr.empty()){
            isScrollable = true;
            return;
        }
        {
            int i, j;
            i = downcardarr.begin()->i;
            j = downcardarr.begin()->j;
            if (activeCardArr[i][j]->getPositionY() > (staticCardArr[i][j - 1]->getPositionY() + staticCardArr[i][j]->getPositionY()) / 2) {
                for (auto index : downcardarr) {
                    activeCardArr[index.i][index.j]->runAction(MoveTo::create(0.3f, Vec2(staticCardArr[index.i][index.j]->getPosition())));
				}
				log("I am here");
				if (Config::SoundConfig::isVoice){
					SimpleAudioEngine::getInstance()->playEffect(Resource::effect_move_back.c_str(), false);
				}
                isScrollable = true;
                return;
            }
        }
        for (auto index : downcardarr){
            activeCardArr[index.i][index.j]->stopActionByTag(1);
            if (activeCardArr[index.i][index.j - 1] != NULL){	
            	auto card = MainScene::operationPlus(index.i, index.j, Config::down);
            	this->getChildByName("gameLayer")->removeChild(activeCardArr[index.i][index.j - 1]);
            	this->getChildByName("gameLayer")->removeChild(activeCardArr[index.i][index.j]);
                activeCardArr[index.i][index.j - 1]->release();
            	activeCardArr[index.i][index.j]->release();
            	activeCardArr[index.i][index.j] = NULL;
            	activeCardArr[index.i][index.j - 1] = card;
            	this->getChildByName("gameLayer")->addChild(card, 1);
                card->setRotation3D(Vec3(0, 180, 0));
                card->runAction(RotateBy::create(0.3f, Vec3(0, 180, 0)));
            }
            else{
                activeCardArr[index.i][index.j - 1] = activeCardArr[index.i][index.j];
                auto moveTo = MoveTo::create(
                    0.3f,
                    staticCardArr[index.i][index.j - 1]->getPosition()
                    );
                moveTo->setTag(1);
                activeCardArr[index.i][index.j - 1]->runAction(moveTo);
                activeCardArr[index.i][index.j] = NULL;

            }
        }

        int i = CCRANDOM_0_1() * 4;
        while (activeCardArr[i][3] != NULL){
        if (i > 2)
        {
            i = 0;
        }
        else 
            i++;
        }
        CardSprite* card = (CardSprite*)this->getChildByName("gameLayer")->getChildByName("newCard");
        card->setPosition(staticCardArr[i][3]->getPosition());
        card->setName("");
		card->setScaleX(0.1);
		card->setScaleY(0.1);
		auto scaleAction = ScaleTo::create(0.3,1.0, 1.0, 0);
        card->setVisible(true);
		card->runAction(scaleAction);
        activeCardArr[i][3] = (CardSprite*)card;
        break;
    }
	default:
		isScrollable = true;
		return;
    }
    log("%d", Config::SoundConfig::isVoice);
    if (Config::SoundConfig::isVoice){
        SimpleAudioEngine::getInstance()->playEffect(Resource::effect_move.c_str(), false);
    }
    updateCardArr();
    isScrollable = true;
}

void MainScene::onTouchMoved(Touch * touch, Event * event) {
    float offset;
	Vec2 dValue = (touch->getLocation() - touch->getPreviousLocation());
    if (!scroll) {
	    if (abs(dValue.x) > 3 || abs(dValue.y) > 3) {
			if (abs(dValue.x) > abs(dValue.y)) {
				if (dValue.x > 0) {
					scroll = Config::right;
				}
				else {
					scroll = Config::left;
				}
			}
			else {
				if (dValue.y > 0) {
					scroll = Config::up;
				}
				else {
					scroll = Config::down;
				}
			}
		}
	}
    else {
		switch (scroll) {
		case Config::right: {
            offset = cardMoveOffset;
            if (dValue.x < 0) {
                offset = -offset;
            }
			for (auto index : rightcardarr) {
				if (
					staticCardArr[index.i + 1][index.j]->getPositionX() - activeCardArr[index.i][index.j]->getPosition().x - offset >= 0  
                    && 
                    activeCardArr[index.i][index.j]->getPositionX() - staticCardArr[index.i][index.j]->getPosition().x + offset >= 0
				) {

                   // auto place = Place::create(Vec2(activeCardArr[index.i][index.j]->getPositionX() + offset, activeCardArr[index.i][index.j]->getPositionY()));
                    //activeCardArr[index.i][index.j]->runAction(place);
					activeCardArr[index.i][index.j]->setPosition(activeCardArr[index.i][index.j]->getPosition().x + dValue.x,
						activeCardArr[index.i][index.j]->getPosition().y);
				}
			}
			break;
		}
		case Config::left: {
            offset = cardMoveOffset;
            if (dValue.x < 0) {
                offset = -offset;
            }
            for (auto index : leftcardarr) {
                if (
                    staticCardArr[index.i][index.j]->getPositionX() - activeCardArr[index.i][index.j]->getPosition().x - offset >= 0
                    &&
                    activeCardArr[index.i][index.j]->getPositionX() - staticCardArr[index.i - 1][index.j]->getPosition().x + offset >= 0
                    ) {

                    //auto place = Place::create(Vec2(activeCardArr[index.i][index.j]->getPositionX() + offset, activeCardArr[index.i][index.j]->getPositionY()));
                    //activeCardArr[index.i][index.j]->runAction(place);
					activeCardArr[index.i][index.j]->setPosition(activeCardArr[index.i][index.j]->getPosition().x + dValue.x,
						activeCardArr[index.i][index.j]->getPosition().y);
				}
            }
			break;
		}
        case Config::up: {
            offset = cardMoveOffset;
            if (dValue.y < 0) {
                offset = -offset;
            }
            for (auto index : upcardarr) {
                if (
                    staticCardArr[index.i][index.j + 1]->getPositionY() - activeCardArr[index.i][index.j]->getPositionY() - offset >= 0
                    &&
                    activeCardArr[index.i][index.j]->getPositionY() - staticCardArr[index.i][index.j]->getPositionY() + offset >= 0
                    ) {

                    //auto place = Place::create(Vec2(activeCardArr[index.i][index.j]->getPositionX(), activeCardArr[index.i][index.j]->getPositionY() + offset));
                    //activeCardArr[index.i][index.j]->runAction(place);
					activeCardArr[index.i][index.j]->setPosition(activeCardArr[index.i][index.j]->getPosition().x,
						activeCardArr[index.i][index.j]->getPosition().y + dValue.y);
				}
            }
            break;
        }
        case Config::down: {
            offset = cardMoveOffset;
            if (dValue.y < 0) {
                offset = -offset;
            }
            for (auto index : downcardarr) {
                if (
                    staticCardArr[index.i][index.j]->getPositionY() - activeCardArr[index.i][index.j]->getPositionY() - offset >= 0
                    &&
                    activeCardArr[index.i][index.j]->getPositionY() - staticCardArr[index.i][index.j - 1]->getPositionY() + offset >= 0
                    ) {

                    //auto place = Place::create(Vec2(activeCardArr[index.i][index.j]->getPositionX(), activeCardArr[index.i][index.j]->getPositionY() + offset));
                    //activeCardArr[index.i][index.j]->runAction(place);
					activeCardArr[index.i][index.j]->setPosition(activeCardArr[index.i][index.j]->getPosition().x,
						activeCardArr[index.i][index.j]->getPosition().y + dValue.y);
				}
            }
            break;
        }
		}
	}

}

void MainScene::updateCardArr() {
	rightcardarr.clear();
	leftcardarr.clear();
	upcardarr.clear();
	downcardarr.clear();
	check();
	
	//如果四个方向数组都为空,则gameove
	if (rightcardarr.empty() && leftcardarr.empty() && upcardarr.empty() && downcardarr.empty()){
		log("game is over");
        gameOver();
        return;
	}

	//新增卡片
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			if (activeCardArr[i][j] != NULL){
				if (activeCardArr[i][j]->getNum() == 1){
					duplicateLevel[0] += 1;
				}
				if (activeCardArr[i][j]->getNum() == 2){
					duplicateLevel[1] += 1;
				}
			}
		}
	}
	int num = CCRANDOM_0_1() * 9;
	preview_card_1->setVisible(false);
	preview_card_2->setVisible(false);
	preview_card_3->setVisible(false);
	if (duplicateLevel[0] > duplicateLevel[1]){
		if (num >= 6){
			num = 3;
			preview_card_3->setVisible(true);
		}
		else if (num >= 1){
			num = 2;
			preview_card_2->setVisible(true);
		}
		else{
			num = 1;
			preview_card_1->setVisible(true);
		}
	}
	else if (duplicateLevel[1] > duplicateLevel[0]){
		if (num >= 6){
			num = 3;
			preview_card_3->setVisible(true);
		}
		else if (num <= 4){
			num = 1;
			preview_card_1->setVisible(true);
		}
		else{
			num = 2;
			preview_card_2->setVisible(true);

		}
	}
	else{
		if (num >= 6){
			num = 3;
			preview_card_3->setVisible(true);
		}
		else if (num >= 3){
			num = 2;
			preview_card_2->setVisible(true);

		}
		else{
			num = 1;
			preview_card_1->setVisible(true);
		}
	}
	duplicateLevel[0] = 0;
	duplicateLevel[1] = 0;

	auto card = CardSprite::createCardSprite(num, Vec2(0, 0), gameLayerSize * Config::cardSizeScale, 0);
	card->setVisible(false);
	this->getChildByName("gameLayer")->addChild(card, 1,"newCard");
}

void MainScene::check() {
    // 判断是否可以合并
    auto checkNum = [](int i, int j) {
        if (i >= 3 && j >= 3 && i == j) {
            return true;
        }
        if (i < 3 && j < 3 && i != j){
            return true;
        }
        return false;
    };
    // 深度复制
    auto deepCopyMatrix = [](int a[4][4], int b[4][4]) {
        int i, j;
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                b[i][j] = a[i][j];
            }
        }
    };

    int spriteMatrix[4][4];
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (activeCardArr[i][j] != NULL) {
                spriteMatrix[i][j] = 1;
            }
            else {
                spriteMatrix[i][j] = 0;
            }
        }
    }

    // 检测左移队列
    int tempMatrix[4][4];
    deepCopyMatrix(spriteMatrix, tempMatrix);
    for (i = 1; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (tempMatrix[i][j]) {
                if (tempMatrix[i - 1][j]) {
                    if (checkNum(activeCardArr[i - 1][j]->getNum(), activeCardArr[i][j]->getNum())) {
                        leftcardarr.push_back(cardspriteindex{ i, j });
                        tempMatrix[i][j] = 0;
                    }
                }
                else {
                    leftcardarr.push_back(cardspriteindex{ i, j });
                    tempMatrix[i][j] = 0;
                }
            }
        }
    }

    // 检测右移队列
    deepCopyMatrix(spriteMatrix, tempMatrix);
    for (i = 2; i >= 0; i--) {
        for (j = 0; j < 4; j++) {
            if (tempMatrix[i][j]) {
                if (tempMatrix[i + 1][j]) {
                    if (checkNum(activeCardArr[i + 1][j]->getNum(), activeCardArr[i][j]->getNum())) {
                        rightcardarr.push_back(cardspriteindex{ i, j });
                        tempMatrix[i][j] = 0;
                    }
                }
                else {
                    rightcardarr.push_back(cardspriteindex{ i, j });
                    tempMatrix[i][j] = 0;
                }
            }
        }
    }

    // 检测上移队列
    deepCopyMatrix(spriteMatrix, tempMatrix);
    for (j = 2; j >= 0; j--) {
        for (i = 0; i < 4; i++) {
            if (tempMatrix[i][j]) {
                if (tempMatrix[i][j + 1]) {
                    if (checkNum(activeCardArr[i][j + 1]->getNum(), activeCardArr[i][j]->getNum())) {
                        upcardarr.push_back(cardspriteindex{ i, j });
                        tempMatrix[i][j] = 0;
                    }
                }
                else {
                    upcardarr.push_back(cardspriteindex{ i, j });
                    tempMatrix[i][j] = 0;
                }
            }
        }
    }

    // 检测下移队列
    deepCopyMatrix(spriteMatrix, tempMatrix);
    for (j = 1; j < 4; j++) {
        for (i = 0; i < 4; i++) {
            if (tempMatrix[i][j]) {
                if (tempMatrix[i][j - 1]) {
                    if (checkNum(activeCardArr[i][j - 1]->getNum(), activeCardArr[i][j]->getNum())) {
                        downcardarr.push_back(cardspriteindex{ i, j });
                        tempMatrix[i][j] = 0;
                    }
                }
                else {
                    downcardarr.push_back(cardspriteindex{ i, j });
                    tempMatrix[i][j] = 0;
                }
            }
        }
    }
}


CardSprite* MainScene::operationPlus(int i, int j, int type)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 pos(0, 0);
	int num = 0;

	int last_i, last_j;
	switch (type) {
	case Config::up: {
		last_i = i;
		last_j = j + 1;
		break;
	}
	case Config::down: {
		last_i = i;
		last_j = j - 1;
		break;
	}
	case Config::right: {
		last_i = i + 1;
		last_j = j;
		break;
	}
	case Config::left: {
		last_i = i - 1;
		last_j = j;
		break;
	}
	}
	auto first = activeCardArr[i][j];
	auto last = activeCardArr[last_i][last_j];
	if (last != NULL) {
		num = first->getNum() + last->getNum();
        auto card = CardSprite::createCardSprite(num, Vec2(0, 0), gameLayerSize * Config::cardSizeScale);
        card->setPosition(staticCardArr[last_i][last_j]->getPosition());
        return card;
	}
	else {
		num = first->getNum();
        first->setPosition(staticCardArr[last_i][last_j]->getPosition());
        return first;
	}
	
}

void MainScene::gameOver() {
    log("score: %d", countScore());
    OverScene::setScore(countScore());
    auto overScene = OverScene::createScene();
    auto transilate = TransitionFadeDown::create(1.0f, overScene);
    Director::getInstance()->replaceScene(transilate);
}

int MainScene::countScore() {
    int sum = 0;
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            sum += activeCardArr[i][j]->getNum();
        }
    }
    return sum;
}

void MainScene::menuClickCallback(cocos2d::Ref* pSender){
	if (Config::SoundConfig::isVoice){
		SimpleAudioEngine::getInstance()->playEffect(Resource::effect_button.c_str(), false);
	}
	auto menuScene = MenuScene::createScene();
	auto transilate = TransitionMoveInR::create(0.5f, menuScene);
	Director::getInstance()->pushScene(transilate);
}

void MainScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
    if (!keyboardFlag) {
        keyboardFlag = true;
        return;
    }
    switch (keyCode) {
    // up
    case EventKeyboard::KeyCode::KEY_W:
    case EventKeyboard::KeyCode::KEY_UP_ARROW: {
        if (upcardarr.empty()){
            isScrollable = true;
            return;
        }
        for (auto index : upcardarr){
            activeCardArr[index.i][index.j]->stopActionByTag(1);
            if (activeCardArr[index.i][index.j + 1] != NULL){
                auto card = MainScene::operationPlus(index.i, index.j, Config::up);
                this->getChildByName("gameLayer")->removeChild(activeCardArr[index.i][index.j + 1]);
                this->getChildByName("gameLayer")->removeChild(activeCardArr[index.i][index.j]);
                activeCardArr[index.i][index.j + 1]->release();
                activeCardArr[index.i][index.j]->release();
                activeCardArr[index.i][index.j] = NULL;
                activeCardArr[index.i][index.j + 1] = card;
                this->getChildByName("gameLayer")->addChild(card, 1);
                card->setRotation3D(Vec3(0, 180, 0));
                card->runAction(RotateBy::create(0.3f, Vec3(0, 180, 0)));
            }
            else{
                activeCardArr[index.i][index.j + 1] = activeCardArr[index.i][index.j];
                auto moveTo = MoveTo::create(
                    0.3f,
                    staticCardArr[index.i][index.j + 1]->getPosition()
                    );
                moveTo->setTag(1);
                activeCardArr[index.i][index.j + 1]->runAction(moveTo);
                activeCardArr[index.i][index.j] = NULL;

            }
        }
        if (Config::SoundConfig::isVoice){
			SimpleAudioEngine::getInstance()->playEffect(Resource::effect_move.c_str(), false);
		}

        int i = CCRANDOM_0_1() * 4;
        while (activeCardArr[i][0] != NULL){
            if (i > 2)
            {
                i = 0;
            }
            else
                i++;
        }
        CardSprite* card = (CardSprite*)this->getChildByName("gameLayer")->getChildByName("newCard");
        card->setPosition(staticCardArr[i][0]->getPosition());
        card->setName("");
		card->setScaleX(0.1);
		card->setScaleY(0.1);
		auto scaleAction = ScaleTo::create(0.2f, 1.0f, 1.0f, 0);
		card->setVisible(true);
		card->runAction(scaleAction);
		activeCardArr[i][0] = (CardSprite*)card;
        break;
    }
    case EventKeyboard::KeyCode::KEY_S:
    case EventKeyboard::KeyCode::KEY_DOWN_ARROW: {
        if (downcardarr.empty()){
            isScrollable = true;
            return;
        }
        for (auto index : downcardarr){
            activeCardArr[index.i][index.j]->stopActionByTag(1);
            if (activeCardArr[index.i][index.j - 1] != NULL){
                auto card = MainScene::operationPlus(index.i, index.j, Config::down);
                this->getChildByName("gameLayer")->removeChild(activeCardArr[index.i][index.j - 1]);
                this->getChildByName("gameLayer")->removeChild(activeCardArr[index.i][index.j]);
                activeCardArr[index.i][index.j - 1]->release();
                activeCardArr[index.i][index.j]->release();
                activeCardArr[index.i][index.j] = NULL;
                activeCardArr[index.i][index.j - 1] = card;
                this->getChildByName("gameLayer")->addChild(card, 1);
                card->setRotation3D(Vec3(0, 180, 0));
                card->runAction(RotateBy::create(0.3f, Vec3(0, 180, 0)));
            }
            else{
                activeCardArr[index.i][index.j - 1] = activeCardArr[index.i][index.j];
                auto moveTo = MoveTo::create(
                    0.3f,
                    staticCardArr[index.i][index.j - 1]->getPosition()
                    );
                moveTo->setTag(1);
                activeCardArr[index.i][index.j - 1]->runAction(moveTo);
                activeCardArr[index.i][index.j] = NULL;

            }
        }
        if (Config::SoundConfig::isVoice){
			SimpleAudioEngine::getInstance()->playEffect(Resource::effect_move.c_str(), false);
		}

        int i = CCRANDOM_0_1() * 4;
        while (activeCardArr[i][3] != NULL){
            if (i > 2)
            {
                i = 0;
            }
            else
                i++;
        }
        CardSprite* card = (CardSprite*)this->getChildByName("gameLayer")->getChildByName("newCard");
        card->setPosition(staticCardArr[i][3]->getPosition());
        card->setName("");
		card->setScaleX(0.1);
		card->setScaleY(0.1);
		auto scaleAction = ScaleTo::create(0.2f, 1.0f, 1.0f, 0);
		card->setVisible(true);
		card->runAction(scaleAction);
        activeCardArr[i][3] = (CardSprite*)card;
        break;
    }
    case EventKeyboard::KeyCode::KEY_A:
    case EventKeyboard::KeyCode::KEY_LEFT_ARROW: {
        if (leftcardarr.empty()){
            isScrollable = true;
            return;
        }
        for (auto index : leftcardarr){
            activeCardArr[index.i][index.j]->stopActionByTag(1);
            if (activeCardArr[index.i - 1][index.j] != NULL){
                auto card = MainScene::operationPlus(index.i, index.j, Config::left);
                this->getChildByName("gameLayer")->removeChild(activeCardArr[index.i - 1][index.j]);
                this->getChildByName("gameLayer")->removeChild(activeCardArr[index.i][index.j]);
                activeCardArr[index.i - 1][index.j]->release();
                activeCardArr[index.i][index.j]->release();
                activeCardArr[index.i][index.j] = NULL;
                activeCardArr[index.i - 1][index.j] = card;
                card->setRotation3D(Vec3(0, 180, 0));
                this->getChildByName("gameLayer")->addChild(card, 1);
                card->runAction(RotateBy::create(0.3f, Vec3(0, 180, 0)));
            }
            else{
                activeCardArr[index.i - 1][index.j] = activeCardArr[index.i][index.j];
                //activeCardArr[index.i - 1][index.j]->setPosition(staticCardArr[index.i - 1][index.j]->getPosition());
                auto moveTo = MoveTo::create(
                    0.3f,
                    Vec2(staticCardArr[index.i - 1][index.j]->getPosition())
                    );
                moveTo->setTag(1);
                activeCardArr[index.i - 1][index.j]->runAction(moveTo);
                activeCardArr[index.i][index.j] = NULL;
            }
        }
        if (Config::SoundConfig::isVoice){
			SimpleAudioEngine::getInstance()->playEffect(Resource::effect_move.c_str(), false);
		}

        int j = CCRANDOM_0_1() * 4;
        while (activeCardArr[3][j] != NULL){
            if (j > 2)
            {
                j = 0;
            }
            else
                j++;
        }
        CardSprite* card = (CardSprite*)this->getChildByName("gameLayer")->getChildByName("newCard");
        card->setPosition(staticCardArr[3][j]->getPosition());
        card->setName("");
		card->setScaleX(0.1);
		card->setScaleY(0.1);
		auto scaleAction = ScaleTo::create(0.2f, 1.0f, 1.0f, 0);
		card->setVisible(true);
		card->runAction(scaleAction);
        activeCardArr[3][j] = (CardSprite*)card;
        break;
    }
    case EventKeyboard::KeyCode::KEY_D:
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW: {
        if (rightcardarr.empty()){
            isScrollable = true;
            return;
        }
        for (auto index : rightcardarr){
            activeCardArr[index.i][index.j]->stopActionByTag(1);
            if (activeCardArr[index.i + 1][index.j] != NULL){
                auto card = MainScene::operationPlus(index.i, index.j, Config::right);
                this->getChildByName("gameLayer")->removeChild(activeCardArr[index.i][index.j]);
                this->getChildByName("gameLayer")->removeChild(activeCardArr[index.i + 1][index.j]);
                activeCardArr[index.i + 1][index.j]->release();
                activeCardArr[index.i][index.j]->release();
                activeCardArr[index.i][index.j] = NULL;
                activeCardArr[index.i + 1][index.j] = card;

                this->getChildByName("gameLayer")->addChild(card, 1);
                card->setRotation3D(Vec3(0, 180, 0));
                card->runAction(RotateBy::create(0.3f, Vec3(0, 180, 0)));
            }
            else{
                activeCardArr[index.i + 1][index.j] = activeCardArr[index.i][index.j];
                //activeCardArr[index.i + 1][index.j]->setPosition(staticCardArr[index.i + 1][index.j]->getPosition());
                auto moveTo = MoveTo::create(
                    0.1f,
                    Vec2(staticCardArr[index.i + 1][index.j]->getPosition())
                    );
                moveTo->setTag(1);
                activeCardArr[index.i + 1][index.j]->runAction(moveTo);
                activeCardArr[index.i][index.j] = NULL;

            }
        }
        if (Config::SoundConfig::isVoice){
			SimpleAudioEngine::getInstance()->playEffect(Resource::effect_move.c_str(), false);
		}

        int j = CCRANDOM_0_1() * 4;
        while (activeCardArr[0][j] != NULL){
            if (j > 2)
            {
                j = 0;
            }
            else
                j++;
        }
        CardSprite* card = (CardSprite*)this->getChildByName("gameLayer")->getChildByName("newCard");
        card->setPosition(staticCardArr[0][j]->getPosition());
        card->setName("");
		card->setScaleX(0.1);
		card->setScaleY(0.1);
		auto scaleAction = ScaleTo::create(0.2f, 1.0f, 1.0f, 0);
		card->setVisible(true);
		card->runAction(scaleAction);
		activeCardArr[0][j] = (CardSprite*)card;
        break;
    }
    case EventKeyboard::KeyCode::KEY_MENU: {
        auto menuScene = MenuScene::createScene();
        auto transilate = TransitionMoveInR::create(0.5f, menuScene);
        Director::getInstance()->pushScene(transilate);
        break;
    }
    case EventKeyboard::KeyCode::KEY_BACKSPACE:
    case EventKeyboard::KeyCode::KEY_ESCAPE: {
        auto startScene = StartScene::createScene();
        auto translate = TransitionFlipAngular::create(1.0f, startScene);
        Director::getInstance()->replaceScene(translate);
        return;
    }
    }
    updateCardArr();
    isScrollable = true;
}

void MainScene::onEnter() {
    log("on Enter");
    Layer::onEnter();
    _eventDispatcher->removeEventListenersForType(EventListener::Type::KEYBOARD);

    auto keyListener = EventListenerKeyboard::create();
    keyListener->onKeyReleased = CC_CALLBACK_2(MainScene::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
    keyListener->setEnabled(true);   
    log("%d", Config::SoundConfig::isVoice);
}
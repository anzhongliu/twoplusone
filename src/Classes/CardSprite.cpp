#include "CardSprite.h"

USING_NS_CC;
USING_NS_CC_EXT;

// mode为模式，决定是否显示数字，1为普通卡片，0为预览用的图片
CardSprite * CardSprite::createCardSprite(int num, Vec2 position, Vec2 size, int mode) {
    CardSprite * card = new CardSprite();
    if (card && card->init()) {
        //card->autorelease();
        card->initCard(num, position, size, mode);
        return card;
    }
    CC_SAFE_DELETE(card);
    return NULL;
}

bool CardSprite::init() {
    if (!Sprite::init()) {
        return false;
    }
    return true;
}

// 初始化卡片
void CardSprite::initCard(int num, Vec2 position, Vec2 size, int mode) {
    // Color3B bgLayerColor;
	string bgPic = "";
    switch (num) {
    case 0:{
        // bgLayerColor = Config::CardBgLayerColor;
		bgPic = Resource::card_static;
        break;
    }
    case 1:{
        // bgLayerColor = Config::GameBGCardColor1;
		bgPic = Resource::card_1;
        break;
    }
    case 2:{
        // bgLayerColor = Config::GameBGCardColor2;
		bgPic = Resource::card_2;
        break;
    }
    default:{
		if (num >= 192) {
			bgPic = Resource::card_more_than_192;
		}
		else if (num >= 96) {
			bgPic = Resource::card_more_than_96;
		}
		else {
			bgPic = Resource::card_3;
		}
    }
    }

	// auto batchNode = SpriteBatchNode::create(bgPic);
	auto bgSprite = Scale9Sprite::create(bgPic, Rect(0, 0, 150, 150), Rect(5, 5, 140,140));
	// bgSprite->updateWithBatchNode(batchNode, Rect(0, 0, 100, 100), false, Rect(10, 10, 90, 90));
	bgSprite->setContentSize(Size(size.x, size.y));
	// auto bgSprite = Sprite::create(bgPic, Rect(0, 0, size.x, size.y));
	this->setPosition(position + size / 2);

	bgSprite->ignoreAnchorPointForPosition(false);
	bgSprite->setAnchorPoint(Vec2(0.5, 0.5));
	this->addChild(bgSprite, 1, "bgLayer");

	auto visibleSize = Director::getInstance()->getVisibleSize();
    // 创建卡片
    if (num > 0) {
        //if (mode) {
        auto labelCardNumber = Label::createWithTTF((string)(__String::createWithFormat("%i", num)->getCString()), Config::fontStyle, visibleSize.height * Config::cardFontSizeScale);
			if (num < 3){
				labelCardNumber->setColor(Config::numColor1);
			}
			else
				labelCardNumber->setColor(Config::numColor2);
			if (num > 100) {
				labelCardNumber->setSystemFontSize(visibleSize.height * Config::cardFontSizeScale_MoreThan100);
			}
			labelCardNumber->setPosition(bgSprite->getContentSize().width / 2, bgSprite->getContentSize().height / 2);
			bgSprite->addChild(labelCardNumber, 1);
        //}
        
        this->num = num;
        return;
    }
    // 创建卡片底座
    this->num = 0;
    return;
}
#ifndef __CARD_H__
#define __CARD_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Config.h"
#include "Resouce.h"
#include <iostream>

class CardSprite : public cocos2d::Sprite{
public:
    static CardSprite * createCardSprite(int num, cocos2d::Vec2 position, cocos2d::Vec2 size, int mode = 1);

    virtual bool init();

    CREATE_FUNC(CardSprite);

    int getNum() { return num; }

private:
    void initCard(int num, cocos2d::Vec2 position, cocos2d::Vec2 size, int mode);
    int num;
};

#endif
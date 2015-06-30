#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include <vector>
#include "CardSprite.h"
#include "OverScene.h"
#include "MenuScene.h"
#include "Resouce.h"
#include "CardSprite.h"
#include "SimpleAudioEngine.h"

class MainScene : public cocos2d::Layer {
public:
    static cocos2d::Scene * createScene();

    virtual bool init();

    CREATE_FUNC(MainScene);

    static bool keyboardFlag;

private:
    void initGameScene(const cocos2d::Size & visibleSize, const cocos2d::Vec2 & origin);
    void initCard(const cocos2d::Size & visibleSize, const cocos2d::Vec2 & origin);
	void initPreviewCard(cocos2d::Size);
    void setCard(int pos, const cocos2d::Size & visibleSize, const cocos2d::Vec2 & origin);
    CardSprite * staticCardArr[4][4];
    CardSprite * activeCardArr[4][4];

    // 游戏结束
    void gameOver();

    virtual void onEnter();

    // 触摸事件
    virtual bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event);
    virtual void onTouchMoved(cocos2d::Touch * touch, cocos2d::Event *);
    virtual void onTouchEnded(cocos2d::Touch * touch, cocos2d::Event *);
    virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    // 计算分数
    int countScore();

    // 更新各方向上的卡片数组
    void updateCardArr();
    void check();

	//卡片相加的操作
	CardSprite* operationPlus(int, int, int);

	//菜单栏点击的callback function
	void menuClickCallback(cocos2d::Ref* pSender);

    // 
    struct cardspriteindex {
        int i;
        int j;
    };

    // 维护各方向上的数组
    std::vector<cardspriteindex> upcardarr;
    std::vector<cardspriteindex> downcardarr;
    std::vector<cardspriteindex> rightcardarr;
    std::vector<cardspriteindex> leftcardarr;

	//gameLayer大小
	Vec2 gameLayerSize;

    // 判断是否可以滑动的标识
    bool isScrollable;

	//标志重复的等级
	int duplicateLevel[2];
	
	// 
	float cardWidth;
	float cardHeight;
	float cardWidthPadding;
	float cardHeightPadding;

	//
	int scroll;

	// 
	cocos2d::extension::Scale9Sprite * preview_card_1;
	cocos2d::extension::Scale9Sprite * preview_card_2;
	cocos2d::extension::Scale9Sprite * preview_card_3;

    float cardMoveOffset;

    
};

#endif
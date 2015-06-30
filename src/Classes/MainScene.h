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

    // ��Ϸ����
    void gameOver();

    virtual void onEnter();

    // �����¼�
    virtual bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event);
    virtual void onTouchMoved(cocos2d::Touch * touch, cocos2d::Event *);
    virtual void onTouchEnded(cocos2d::Touch * touch, cocos2d::Event *);
    virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    // �������
    int countScore();

    // ���¸������ϵĿ�Ƭ����
    void updateCardArr();
    void check();

	//��Ƭ��ӵĲ���
	CardSprite* operationPlus(int, int, int);

	//�˵��������callback function
	void menuClickCallback(cocos2d::Ref* pSender);

    // 
    struct cardspriteindex {
        int i;
        int j;
    };

    // ά���������ϵ�����
    std::vector<cardspriteindex> upcardarr;
    std::vector<cardspriteindex> downcardarr;
    std::vector<cardspriteindex> rightcardarr;
    std::vector<cardspriteindex> leftcardarr;

	//gameLayer��С
	Vec2 gameLayerSize;

    // �ж��Ƿ���Ի����ı�ʶ
    bool isScrollable;

	//��־�ظ��ĵȼ�
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
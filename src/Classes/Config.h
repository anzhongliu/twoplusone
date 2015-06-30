#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <iostream>
#include "cocos2d.h"
using namespace std;
USING_NS_CC;

namespace Config {
	const static Color4B BackGroundLayerColor(255, 255, 224, 255); //背景颜色
	const static Color3B CardBgLayerColor(203, 191, 179); // 游戏静止卡片颜色
	const static Color4B GameBGLayerColor(185, 171, 158, 255); // 游戏场景颜色
	const static Color3B GameBGCardColor1(238, 228, 218); // 1时卡片颜色
	const static Color3B GameBGCardColor2(229, 205, 171); // 2时卡片颜色
	const static Color3B GameBGCardColor3(244, 123, 94); // 大于等于3时卡片颜色
	const static Color3B numColor1(119, 110, 101); //字数小于3的颜色
	const static Color3B numColor2(255, 255, 255);//字数大于等于3的颜色

	const static Color3B menuLabelColor(255, 255, 255);

	const static Color3B scoreLabelColor(0, 0, 0); // 分数显示颜色

    const static Color3B voiceLayerLabelColor(0, 0, 0);

    const static float GameLayerCardSpacingScale = 0.03; // 卡片间距

	const static int right = 1;	//方向为右
	const static int left = 2;	//方向为左
	const static int up = 3;	//方向为上
	const static int down = 4;//方向为下

	//const static int cardFontSize = 35; // 卡片字体大小
	//const static int cardFontSize_MoreThan100 = 25;
	
	//字体相关
	const static float cardFontSizeScale = 0.07292;
	const static float cardFontSizeScale_MoreThan100 = 0.052083;
	const static float scoreFontSizeScale = 0.1041666;

	const static string fontStyle = "fonts/arial.ttf";

    // 按钮相关
	const static float buttonWidthScale = 0.6;
	const static float buttonHeightScale = 0.083333;
    const static float menuPaddingScale = 0.0625;
    const static float menuFontSizeScale = 0.0416666;

    // 菜单相关
	const static float menuButtonWidthScale = 0.24;
	const static float menuButtonHeightScale = 0.08333;
	const static float menuButtonTopScale = 0.0816;
	const static float menuButtonTopRightScale = 0.111111;
    
    // 场景相关
    const static float gameLayerSizeWidthScale = 0.9;
    const static float gameLayerSizeHeightScale = 0.666666;
    const static float cardSizeScale = 0.2;

    const static float cardMoveOffsetScale = 0.0083333;

    class SoundConfig{
    public:

        // 配置声音效果
        static bool isMusic; // 背景音乐
        static bool isVoice; // 音效
    };
    
}

#endif
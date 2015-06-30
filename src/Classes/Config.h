#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <iostream>
#include "cocos2d.h"
using namespace std;
USING_NS_CC;

namespace Config {
	const static Color4B BackGroundLayerColor(255, 255, 224, 255); //������ɫ
	const static Color3B CardBgLayerColor(203, 191, 179); // ��Ϸ��ֹ��Ƭ��ɫ
	const static Color4B GameBGLayerColor(185, 171, 158, 255); // ��Ϸ������ɫ
	const static Color3B GameBGCardColor1(238, 228, 218); // 1ʱ��Ƭ��ɫ
	const static Color3B GameBGCardColor2(229, 205, 171); // 2ʱ��Ƭ��ɫ
	const static Color3B GameBGCardColor3(244, 123, 94); // ���ڵ���3ʱ��Ƭ��ɫ
	const static Color3B numColor1(119, 110, 101); //����С��3����ɫ
	const static Color3B numColor2(255, 255, 255);//�������ڵ���3����ɫ

	const static Color3B menuLabelColor(255, 255, 255);

	const static Color3B scoreLabelColor(0, 0, 0); // ������ʾ��ɫ

    const static Color3B voiceLayerLabelColor(0, 0, 0);

    const static float GameLayerCardSpacingScale = 0.03; // ��Ƭ���

	const static int right = 1;	//����Ϊ��
	const static int left = 2;	//����Ϊ��
	const static int up = 3;	//����Ϊ��
	const static int down = 4;//����Ϊ��

	//const static int cardFontSize = 35; // ��Ƭ�����С
	//const static int cardFontSize_MoreThan100 = 25;
	
	//�������
	const static float cardFontSizeScale = 0.07292;
	const static float cardFontSizeScale_MoreThan100 = 0.052083;
	const static float scoreFontSizeScale = 0.1041666;

	const static string fontStyle = "fonts/arial.ttf";

    // ��ť���
	const static float buttonWidthScale = 0.6;
	const static float buttonHeightScale = 0.083333;
    const static float menuPaddingScale = 0.0625;
    const static float menuFontSizeScale = 0.0416666;

    // �˵����
	const static float menuButtonWidthScale = 0.24;
	const static float menuButtonHeightScale = 0.08333;
	const static float menuButtonTopScale = 0.0816;
	const static float menuButtonTopRightScale = 0.111111;
    
    // �������
    const static float gameLayerSizeWidthScale = 0.9;
    const static float gameLayerSizeHeightScale = 0.666666;
    const static float cardSizeScale = 0.2;

    const static float cardMoveOffsetScale = 0.0083333;

    class SoundConfig{
    public:

        // ��������Ч��
        static bool isMusic; // ��������
        static bool isVoice; // ��Ч
    };
    
}

#endif
#ifndef __RESOURCE_H__
#define __RESOURCE_H__

#include <iostream>
#include "cocos2d.h"
#include "CardSprite.h"

USING_NS_CC;
USING_NS_CC_EXT;

namespace Resource {
	// Í¼Æ¬×ÊÔ´
	// button
	// const static auto button_start = Scale9Sprite::create("button/button-start.png", Rect(0, 0, 150, 150), Rect(5, 5, 140, 140));
	const static string button_start = "button/button-start.png";
	const static string button_start_clicked = "button/button-start-clicked.png";
	const static string button_exit = "button/button-exit.png";
	const static string button_exit_clicked = "button/button-exit-clicked.png";
	const static string button_menu = "button/button-menu.png";
	const static string button_menu_clicked = "button/button-menu-clicked.png";
	const static string button_back = "button/button-back.png";
	const static string button_back_clicked = "button/button-back-clicked.png";
	const static string button_restart = "button/button-restart.png";
	const static string button_restart_clicked = "button/button-restart-clicked.png";
	const static string button_back_to_main = "button/button-back-to-main.png";
	const static string button_back_to_main_clicked = "button/button-back-to-main-clicked.png";
    const static string button_voice_setting = "button/button-back-to-main.png";
    const static string button_voice_setting_clicked = "button/button-back-to-main-clicked.png";
	
	// card
	const static string card_static = "card/card-static.png";
	const static string card_1 = "card/card-1.png";
	const static string card_2 = "card/card-2.png";
	const static string card_3 = "card/card-3.png";
	const static string card_more_than_96 = "card/card-more-than-96.png";
	const static string card_more_than_192 = "card/card-more-than-192.png";

	// layer
	const static string menu_bg = "layer/menu-bg.png";
	const static string gameLayer_bg = "layer/gameLayer-bg.png";

	// logo
	const static string logo = "logo.png";

	//music
	const static string music_bg = "music/music-bg.mp3";
	const static string music_bg_2 = "music/music-bg-2.mp3";

	//effect
	const static string effect_button = "effect/effect-button.mp3";
	const static string effect_toggleButton = "effect/effect-toggle-button.mp3";
	const static string effect_move = "effect/effect-move.wav";
	const static string effect_startButton = "effect/effect-start-button.wav";
	const static string effect_move_back = "effect/effect-move-back.wav";
};

#endif
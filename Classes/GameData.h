#pragma once
#include<string>
#include "cocos2d.h"
#include "SaveManager.h"
#include "sound&music.h"
using namespace std;
USING_NS_CC;
/* Save data is accessed only through SaveManager. */
// Reset all data
static void reset_data() {
	SaveManager::getInstance()->resetAllData();
}
// Initialize save data
static void init_data() {
	const bool shouldInitSound = !SaveManager::getInstance()->hasInit();
	SaveManager::getInstance()->initDefaultData();
	if (shouldInitSound) {
		// First run: reset data and initialize sound; do nothing if a save exists
		init_sound();
	}
}
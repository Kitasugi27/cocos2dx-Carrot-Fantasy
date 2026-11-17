#pragma once

#include "cocos2d.h"

class SaveManager
{
public:
    static SaveManager* getInstance();

    bool hasInit() const;
    void initDefaultData();
    void resetAllData();
    void flush();

    int getUnlockedLevel() const;
    void setUnlockedLevel(int level);

    bool getThemeUnlocked(int themeId) const;
    void setThemeUnlocked(int themeId, bool unlocked);
    void syncThemeUnlocksWithProgress();

    bool isBossUnlocked() const;
    void setBossUnlocked(bool unlocked);
    bool isNestUnlocked() const;
    void setNestUnlocked(bool unlocked);

    void addMoney(int amount);
    void addMonster(int amount);
    void addBoss(int amount);
    void addBarrier(int amount);
    int getMoney() const;
    int getMonster() const;
    int getBoss() const;
    int getBarrier() const;

    int getAdventureStatistic() const;
    void setAdventureStatistic(int value);
    int getHideStatistic() const;
    int getBossPatternStatistic() const;

    bool getSoundEnabled() const;
    void setSoundEnabled(bool enabled);
    bool getMusicEnabled() const;
    void setMusicEnabled(bool enabled);

private:
    SaveManager();
    ~SaveManager();
    SaveManager(const SaveManager&) = delete;
    SaveManager& operator=(const SaveManager&) = delete;

    // progress
    static constexpr const char* const KEY_HAVE_INIT = "have_init";
    static constexpr const char* const KEY_ADVENTURE_STATISTICS = "adventure_statistics";
    static constexpr const char* const KEY_UNLOCKED_LEVEL = "level_1";

    // theme
    static constexpr const char* const KEY_THEME_JUNGLE = "level_2";
    static constexpr const char* const KEY_THEME_DESERT = "level_3";

    // campaign
    static constexpr const char* const KEY_BOSS_LOCK = "if_boss_lock";
    static constexpr const char* const KEY_NEST_LOCK = "if_nest_lock";

    // stats
    static constexpr const char* const KEY_HIDE_STATISTICS = "hide_statistics";
    static constexpr const char* const KEY_BOSSPATTERN_STATISTICS = "bosspattern_statistics";
    static constexpr const char* const KEY_MONEY_STATISTICS = "money_statistics";
    static constexpr const char* const KEY_MONSTER_STATISTICS = "monster_statistics";
    static constexpr const char* const KEY_BOSS_STATISTICS = "boss_statistics";
    static constexpr const char* const KEY_DAMAGE_STATISTICS = "damage_statistics";

    // settings
    static constexpr const char* const KEY_SOUND_EFFECT = "sound_effect";
    static constexpr const char* const KEY_BG_MUSIC = "bg_music";

    cocos2d::UserDefault* _userDefault;
};

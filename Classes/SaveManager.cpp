#include "SaveManager.h"

namespace
{
    const int THEME_JUNGLE_UNLOCK_LEVEL = 2;
    const int THEME_DESERT_UNLOCK_LEVEL = 3;

    const int DEFAULT_ADVENTURE_STATISTIC = 1;
    const int DEFAULT_UNLOCKED_LEVEL = 1;
    const int DEFAULT_THEME_LOCKED = 0;
    const int DEFAULT_MODE_LOCKED = 1;
    const int DEFAULT_STATISTIC = 0;
    const int DEFAULT_SETTING_ENABLED = 1;
}

constexpr const char* const SaveManager::KEY_HAVE_INIT;
constexpr const char* const SaveManager::KEY_ADVENTURE_STATISTICS;
constexpr const char* const SaveManager::KEY_UNLOCKED_LEVEL;
constexpr const char* const SaveManager::KEY_THEME_JUNGLE;
constexpr const char* const SaveManager::KEY_THEME_DESERT;
constexpr const char* const SaveManager::KEY_BOSS_LOCK;
constexpr const char* const SaveManager::KEY_NEST_LOCK;
constexpr const char* const SaveManager::KEY_HIDE_STATISTICS;
constexpr const char* const SaveManager::KEY_BOSSPATTERN_STATISTICS;
constexpr const char* const SaveManager::KEY_MONEY_STATISTICS;
constexpr const char* const SaveManager::KEY_MONSTER_STATISTICS;
constexpr const char* const SaveManager::KEY_BOSS_STATISTICS;
constexpr const char* const SaveManager::KEY_DAMAGE_STATISTICS;
constexpr const char* const SaveManager::KEY_SOUND_EFFECT;
constexpr const char* const SaveManager::KEY_BG_MUSIC;

SaveManager* SaveManager::getInstance()
{
    static SaveManager instance;
    return &instance;
}

SaveManager::SaveManager()
    : _userDefault(cocos2d::UserDefault::getInstance())
{
}

SaveManager::~SaveManager()
{
}

bool SaveManager::hasInit() const
{
    return _userDefault->getBoolForKey(KEY_HAVE_INIT, false);
}

void SaveManager::initDefaultData()
{
    if (hasInit())
    {
        return;
    }
    resetAllData();
}

void SaveManager::resetAllData()
{
    _userDefault->setBoolForKey(KEY_HAVE_INIT, true);
    _userDefault->setIntegerForKey(KEY_ADVENTURE_STATISTICS, 1);
    _userDefault->setIntegerForKey(KEY_HIDE_STATISTICS, 0);
    _userDefault->setIntegerForKey(KEY_BOSSPATTERN_STATISTICS, 0);
    _userDefault->setIntegerForKey(KEY_MONEY_STATISTICS, 0);
    _userDefault->setIntegerForKey(KEY_MONSTER_STATISTICS, 0);
    _userDefault->setIntegerForKey(KEY_BOSS_STATISTICS, 0);
    _userDefault->setIntegerForKey(KEY_DAMAGE_STATISTICS, 0);
    _userDefault->setIntegerForKey(KEY_UNLOCKED_LEVEL, 1);
    setThemeUnlocked(2, false);
    setThemeUnlocked(3, false);
    setBossUnlocked(false);
    setNestUnlocked(false);
    setSoundEnabled(true);
    setMusicEnabled(true);
}

void SaveManager::flush()
{
    _userDefault->flush();
}

int SaveManager::getUnlockedLevel() const
{
    return _userDefault->getIntegerForKey(KEY_UNLOCKED_LEVEL, DEFAULT_UNLOCKED_LEVEL);
}

void SaveManager::setUnlockedLevel(int level)
{
    _userDefault->setIntegerForKey(KEY_UNLOCKED_LEVEL, level);
}

bool SaveManager::getThemeUnlocked(int themeId) const
{
    switch (themeId)
    {
    case 2:
        return _userDefault->getIntegerForKey(KEY_THEME_JUNGLE, DEFAULT_THEME_LOCKED) != 0;
    case 3:
        return _userDefault->getIntegerForKey(KEY_THEME_DESERT, DEFAULT_THEME_LOCKED) != 0;
    default:
        return false;
    }
}

void SaveManager::setThemeUnlocked(int themeId, bool unlocked)
{
    const int value = unlocked ? 1 : 0;
    switch (themeId)
    {
    case 2:
        _userDefault->setIntegerForKey(KEY_THEME_JUNGLE, value);
        break;
    case 3:
        _userDefault->setIntegerForKey(KEY_THEME_DESERT, value);
        break;
    default:
        break;
    }
}

void SaveManager::syncThemeUnlocksWithProgress()
{
    const int unlockedLevel = getUnlockedLevel();
    setThemeUnlocked(2, unlockedLevel >= THEME_JUNGLE_UNLOCK_LEVEL);
    setThemeUnlocked(3, unlockedLevel >= THEME_DESERT_UNLOCK_LEVEL);
}

bool SaveManager::isBossUnlocked() const
{
    return _userDefault->getIntegerForKey(KEY_BOSS_LOCK, DEFAULT_MODE_LOCKED) != 1;
}

void SaveManager::setBossUnlocked(bool unlocked)
{
    _userDefault->setIntegerForKey(KEY_BOSS_LOCK, unlocked ? 0 : 1);
}

bool SaveManager::isNestUnlocked() const
{
    return _userDefault->getIntegerForKey(KEY_NEST_LOCK, DEFAULT_MODE_LOCKED) != 1;
}

void SaveManager::setNestUnlocked(bool unlocked)
{
    _userDefault->setIntegerForKey(KEY_NEST_LOCK, unlocked ? 0 : 1);
}

void SaveManager::addMoney(int amount)
{
    _userDefault->setIntegerForKey(KEY_MONEY_STATISTICS, getMoney() + amount);
}

void SaveManager::addMonster(int amount)
{
    _userDefault->setIntegerForKey(KEY_MONSTER_STATISTICS, getMonster() + amount);
}

void SaveManager::addBoss(int amount)
{
    _userDefault->setIntegerForKey(KEY_BOSS_STATISTICS, getBoss() + amount);
}

void SaveManager::addBarrier(int amount)
{
    _userDefault->setIntegerForKey(KEY_DAMAGE_STATISTICS, getBarrier() + amount);
}

int SaveManager::getMoney() const
{
    return _userDefault->getIntegerForKey(KEY_MONEY_STATISTICS, DEFAULT_STATISTIC);
}

int SaveManager::getMonster() const
{
    return _userDefault->getIntegerForKey(KEY_MONSTER_STATISTICS, DEFAULT_STATISTIC);
}

int SaveManager::getBoss() const
{
    return _userDefault->getIntegerForKey(KEY_BOSS_STATISTICS, DEFAULT_STATISTIC);
}

int SaveManager::getBarrier() const
{
    return _userDefault->getIntegerForKey(KEY_DAMAGE_STATISTICS, DEFAULT_STATISTIC);
}

int SaveManager::getAdventureStatistic() const
{
    return _userDefault->getIntegerForKey(KEY_ADVENTURE_STATISTICS, DEFAULT_ADVENTURE_STATISTIC);
}

void SaveManager::setAdventureStatistic(int value)
{
    _userDefault->setIntegerForKey(KEY_ADVENTURE_STATISTICS, value);
}

int SaveManager::getHideStatistic() const
{
    return _userDefault->getIntegerForKey(KEY_HIDE_STATISTICS, DEFAULT_STATISTIC);
}

int SaveManager::getBossPatternStatistic() const
{
    return _userDefault->getIntegerForKey(KEY_BOSSPATTERN_STATISTICS, DEFAULT_STATISTIC);
}

bool SaveManager::getSoundEnabled() const
{
    return _userDefault->getIntegerForKey(KEY_SOUND_EFFECT, DEFAULT_SETTING_ENABLED) == 1;
}

void SaveManager::setSoundEnabled(bool enabled)
{
    _userDefault->setIntegerForKey(KEY_SOUND_EFFECT, enabled ? 1 : 0);
}

bool SaveManager::getMusicEnabled() const
{
    return _userDefault->getIntegerForKey(KEY_BG_MUSIC, DEFAULT_SETTING_ENABLED) == 1;
}

void SaveManager::setMusicEnabled(bool enabled)
{
    _userDefault->setIntegerForKey(KEY_BG_MUSIC, enabled ? 1 : 0);
}

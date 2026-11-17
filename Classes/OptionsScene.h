#ifndef __Options_SCENE_H__
#define __Options_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
//���ý���
class OptionsScene : public cocos2d::Scene
{
public:
    //���캯��
    static cocos2d::Scene* createScene();//�̳д�������
    virtual bool init();
    CREATE_FUNC(OptionsScene);
    //ȥ���˵�
    void goto_menu(Ref* psender);
    //ȥ����ѡ��ҳ
    void goto_set(Ref* psender, Widget::TouchEventType type);
    //ȥͳ��ѡ��ҳ
    void goto_statistics(Ref* psender, Widget::TouchEventType type);
    //ȥ��Աѡ��ҳ
    void goto_person(Ref* psender, Widget::TouchEventType type);
};
//���ý��������ѡ��ҳ
class SetLayer :public cocos2d::Layer
{
public:
    //���캯��
    static cocos2d::Layer* createLayer();//�̳д�������
    virtual bool init();
    CREATE_FUNC(SetLayer);
    //�ر���Ч
    virtual void close_sound(Ref* psender);
    //�ر�bgm
    virtual void close_bgmusic(Ref* psender);
    //������Ϸ�浵����
    virtual void reset_game(Ref* psender);
    // Refresh sound/music toggles from current save values
    void refresh_toggles();
};
//���ý����ͳ��ѡ��ҳ
class StatisticsLayer :public cocos2d::Layer
{
public:
    //���캯��
    static cocos2d::Layer* createLayer();//�̳д�������
    virtual bool init();
    CREATE_FUNC(StatisticsLayer);
};
//���ý������Աѡ��ҳ
class PersonLayer :public cocos2d::Layer
{
public:
    //���캯��
    static cocos2d::Layer* createLayer();//�̳д�������
    virtual bool init();
    CREATE_FUNC(PersonLayer);
};
#endif // __Options_SCENE_H__

#ifndef __Game_SCENE_H__
#define __Game_SCENE_H__

#include "cocos2d.h"
#include<vector>

#define EMPTY 0
#define DISABLED 1
#define TOWER 2
#define CARROT 5

//���ߺ���
struct pos {
    int i;
    int j;
};
struct vec2 {
    float x;
    float y;
};
//��ÿ��������������ת��Ϊ��������
static vec2 trans_ij_to_xy(pos position) {
    vec2 vec;
    vec.x = 40 + position.j * 80;
    vec.y = 40 + (6 - position.i) * 80;
    return vec;
}
//��ÿ����������ת���ɶ�Ӧ�ĸ�����������
static pos trans_xy_to_ij(vec2 vec) {
    pos position;
    position.j = static_cast<int>((vec.x) / 80);
    position.i = 6 - static_cast<int>((vec.y) / 80);
    return position;
}
//ð��ģʽ��Ϸ��
class GameScene : public cocos2d::Scene
{
public:
    //���캯��
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameScene);
    //���ò˵�����
    void reset_menu();
};
//��Ϸ�˵���
class GameMenu :public cocos2d::Layer 
{
public:
    //���캯��
    static cocos2d::Layer* createLayer();
    virtual bool init();
    CREATE_FUNC(GameMenu);
    //ѡ��
    void options();
    //��ʼ
    void start();
    //����
    void build(pos position, int tower_available[]);
    //����ɾ��
    void tower_operations(pos position);
    //��Ϸʧ��
    void lose();
    //��Ϸ��ʤ
    void win();
    //ʵʱ���½�ҵ�����
    virtual void update(float dt);

private:
    void commitBattleStats(int money, int monsters, int bosses, int barriers);
};
#endif // __Game_SCENE_H__

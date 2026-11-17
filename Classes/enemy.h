#pragma once
#include "cocos2d.h"
#include "GameScene.h"

#define BARRIER 0
#define MONSTER 1

#define BARRIER_ONE   1     //һ����ϰ�
#define BARRIER_TWO   2     //������ϰ�
#define BARRIER_FOUR  4     //�ĸ���ϰ�

#define BARRIER_HP_ONE     1600               //һ���ϰ���Ѫ
#define BARRIER_HP_TWO     3 * BARRIER_HP_ONE //�����ϰ���Ѫ
#define BARRIER_HP_FOUR    3 * BARRIER_HP_TWO //�ĸ��ϰ���Ѫ

#define BARRIER_COIN_ONE     50 
#define BARRIER_COIN_TWO     2 * BARRIER_COIN_ONE //�����ϰ���Ѫ
#define BARRIER_COIN_FOUR    2 * BARRIER_COIN_TWO //�ĸ��ϰ���Ѫ

#define MONSTER_NORMAL 0    //�е�Ѫ�����е��ٶ�
#define MONSTER_FAST   1    //��Ѫ�������ٶ�
#define MONSTER_HUGE   2    //��Ѫ�����ٶȽϵ�

#define MONSTER_FAST_HP       20                     //���ٹֵĻ���Ѫ��
#define MONSTER_NORMAL_HP     3 * MONSTER_FAST_HP    //��ͨ��Ѫ��
#define MONSTER_HUGE_HP       3 * MONSTER_NORMAL_HP  //���͹�Ѫ��

#define MONSTER_HUGE_SPEED    100                  //���͹��ƶ��ٶȣ���ţ�������Ķ���������
#define MONSTER_NORMAL_SPEED  1.5*MONSTER_HUGE_SPEED     //����������
#define MONSTER_FAST_SPEED    2*MONSTER_NORMAL_SPEED   //���ٹ�����

#define MONSTER_COIN_NORMAL   18                       //�����ֺ͸��ٹֵ�����
#define MONSTER_COIN_HUGE     188                      //���͹ֵ�����

#define BARRIER_BASE_PICTURE  "/Enemy/barrier/0/"        //�ϰ�·��
#define MONSTER_BASE_PICTURE  "/Enemy/monster/0/"

//0-8 0Ϊ��ͨ�� 1Ϊ���ٹ� 2Ϊ���͹� 34Ϊһ����ͼ 56Ϊ������ͼ 78Ϊ�ĸ���ͼ
#define NORMAL 0
#define FLY 1
#define BOSS 2
#define BARRIER_1 3
#define BARRIER_2 4
#define BARRIER_3 5
#define BARRIER_4 6
#define BARRIER_5 7
#define BARRIER_6 8


struct Tower_information;
struct Enemy_information {
	int type;                                     //��¼��������
	int hp;                                       //��¼����Ѫ��
	int speed;                                    //��¼�����ƶ��ٶ�
	int coin;                                     //Я���ܲ���
	int damage;                                   //���ܲ���ɵ��˺�
	cocos2d::Sprite* enemy_picture;               //�ϰ���ͼ
	int count;                                    //�߹��ĸ�����
	double time = 0;
	unsigned int id = 0;
	bool alive = true;                                 //��¼��Чʱ��
	int origin_speed;                             //��¼��̬���ٶ�
	int full_hp;                                  //��¼��ѪѪ��
	float total_length = 0;						  //��¼�߹���·�̳���
	pos position;                                 //��¼�ϰ���λ��
		Enemy_information(int _type=0,int originalHp = 0, int originalSpeed = 200, int defeatedCoin = 0, int realDamage = 0, int n = 0,int currentTime=0,pos Position={0,0})
		:type(_type),hp(originalHp), speed(originalSpeed), coin(defeatedCoin), damage(realDamage), count(n),origin_speed(originalSpeed),time(currentTime),full_hp(originalHp),position(Position)
	{
		enemy_picture = nullptr;

	}
		float get_length() { return total_length; }
};

class Enemy : public cocos2d::Sprite
{
	friend class Tower_body;
private:
	Enemy_information enemy;
public:
    static cocos2d::Sprite* createSprite();
	virtual bool init();
	CREATE_FUNC(Enemy);
	virtual void update(float dt);
	void setType(int selection);
	void set_position(pos _position) { enemy.position = _position; }
	bool declineHp(Tower_information tower, int op);
	unsigned int get_id() const { return enemy.id; }
	bool is_alive() const { return enemy.alive; }
	void set_alive(bool value) { enemy.alive = value; }
	static void reset_static_state();
};
//�����Ƿ���Ȼ���� monster/barrier �б��У������ڱ����ӵ���������������
bool enemy_is_alive(Enemy* e);
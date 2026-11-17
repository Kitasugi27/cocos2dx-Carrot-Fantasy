#include "cocos2d.h"
#include"GameScene.h"
#include"enemy.h"
#include"EnemyCreate.h"
#include<vector>
#include<algorithm>
using namespace std;
USING_NS_CC;

extern int game_waves;
extern int if_speed_up;
extern int if_pause;
extern vector<Enemy*> monster;
extern vector<Enemy*> barrier;

static float enemy_spawn_time = 1;
static float enemy_clear_time = 0;
static int enemy_spawn_n = 0;
static int enemy_spawn_flag = 0;
/************************************  ��ʼ��  ********************************/
cocos2d::Layer* EnemyCreate::createLayer() {
	return EnemyCreate::create();
}
bool EnemyCreate::init() {
	if (!Layer::init()) {
		return false;
	}
	return true;
}
/**********************************  ��Ա����ʵ��  ****************************/
/*���ùؿ�*/
void EnemyCreate::reset_static_state()
{
	enemy_spawn_time = 1;
	enemy_clear_time = 0;
	enemy_spawn_n = 0;
	enemy_spawn_flag = 0;
}
void EnemyCreate::SetLevel(int level_selection) {
	reset_static_state();
	monster.clear();
	barrier.clear();
	level = level_selection;
	vector<int>waves;
	if (level == 1) {
		//��һ��
		start_position = { 1,1 };
		current_waves = 1;
		max_waves = 15;
		//ÿһ������洢
		//ǰ����ȫ����ͨ��
		waves.clear();
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 10; j++) {
				waves.push_back(NORMAL);
			}
			monster_data.push_back(waves);
			waves.clear();
		}
		//��12����ͨ��5�������й�5��
		for (int i = 3; i < 15; i++) {
			for (int j = 0; j < 5; j++) {
				waves.push_back(NORMAL);
			}
			for (int j = 0; j < 5; j++) {
				waves.push_back(FLY);
			}
			monster_data.push_back(waves);
			waves.clear();
		}
		//�ϰ���
		barrier_appear(BARRIER_6, { 1,3 }, { 1,4 }, { 0,3 });
		barrier_appear(BARRIER_6, { 1,7 }, { 1,8 }, { 0,7 });
		barrier_appear(BARRIER_5, { 1,5 }, { 1,6 }, { 0,5 });
		barrier_appear(BARRIER_3, { 4,5 }, { 4,6 });
		barrier_appear(BARRIER_2, { 3,2 });
		barrier_appear(BARRIER_1, { 2,4 });
		barrier_appear(BARRIER_1, { 2,7 });
		barrier_appear(BARRIER_2, { 3,9 });

	}
	else if (level == 2) {
		//�ڶ���
		start_position = { 1,4 };
		current_waves = 1;
		max_waves = 15;
		//ÿһ������洢
		//ǰ����ȫ����ͨ��
		waves.clear();
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 10; j++) {
				waves.push_back(NORMAL);
			}
			if (i == 1) {
				waves.push_back(BOSS);
			}
			monster_data.push_back(waves);
			waves.clear();
		}
		//��13����ͨ��5�������й�5��
		//���һ����һ��boss
		for (int i = 2; i < 15; i++) {
			for (int j = 0; j < 5; j++) {
				waves.push_back(NORMAL);
			}
			for (int j = 0; j < 5; j++) {
				waves.push_back(FLY);
			}
			monster_data.push_back(waves);
			waves.clear();
		}

		//�ϰ���
		barrier_appear(BARRIER_2, { 4,5 });
		barrier_appear(BARRIER_1, { 2,4 });
		barrier_appear(BARRIER_1, { 2,8 });
		barrier_appear(BARRIER_1, { 1,11 });
		barrier_appear(BARRIER_1, { 4,3 });
		barrier_appear(BARRIER_3, { 4,0 }, { 4,1 });
		barrier_appear(BARRIER_4, { 4,8 }, { 4,9 });
		barrier_appear(BARRIER_6, { 1,1 }, { 1,2 }, { 0,1 });
		barrier_appear(BARRIER_5, { 3,10 }, { 3,11 }, { 2,10 });
	}
}
/*����*/
void EnemyCreate::monster_appear(int Type) {
	//��������ΪType�Ĺ���
	auto enemy = Enemy::createSprite();
	static_cast<Enemy*>(enemy)->setType(Type);
	vec2 start = trans_ij_to_xy(start_position);
	enemy->setPosition(Vec2(start.x, start.y));
	this->addChild(enemy);
	monster.push_back(static_cast<Enemy*>(enemy));//������������
	//����ǹ�������ϰ���������Ч����
	if (Type < 3) {
		auto effect = Sprite::create("/EnemyCreate/Items02-hd_0.PNG");
		effect->setPosition(Vec2(start.x, start.y));
		this->addChild(effect);
		effect->runAction(Sequence::create(ScaleTo::create(0.2, 3), CallFunc::create([effect]() {effect->removeFromParent(); }), nullptr));
	}
}
/*�ϰ���*/
//һ���ϰ���
void EnemyCreate::barrier_appear(int Type, pos position) {
	vec2 vec;
	auto barrier_1 = Enemy::createSprite();
	static_cast<Enemy*>(barrier_1)->setType(Type);
	static_cast<Enemy*>(barrier_1)->set_position(position);
	vec = trans_ij_to_xy(position);
	barrier_1->setPosition(Vec2(vec.x, vec.y));
	this->addChild(barrier_1);
	barrier.push_back(static_cast<Enemy*>(barrier_1));
}
//�����ϰ���
void EnemyCreate::barrier_appear(int Type, pos position_l,pos position_r) {
	vec2 vec_l, vec_r, vec;
	auto barrier_1 = Enemy::createSprite();
	static_cast<Enemy*>(barrier_1)->setType(Type);
	static_cast<Enemy*>(barrier_1)->set_position(position_l);
	vec_l = trans_ij_to_xy(position_l);
	vec_r = trans_ij_to_xy(position_r);
	vec = { (vec_l.x + vec_r.x) / 2,(vec_l.y + vec_r.y) / 2 };
	barrier_1->setPosition(Vec2(vec.x, vec.y));
	this->addChild(barrier_1);
	barrier.push_back(static_cast<Enemy*>(barrier_1));
}
//�����ϰ���
void EnemyCreate::barrier_appear(int Type, pos position_l, pos position_r,pos position_u) {
	vec2 vec_l, vec_r,vec_u, vec;
	auto barrier_1 = Enemy::createSprite();
	static_cast<Enemy*>(barrier_1)->setType(Type);
	static_cast<Enemy*>(barrier_1)->set_position(position_l);
	vec_l = trans_ij_to_xy(position_l);
	vec_r = trans_ij_to_xy(position_r);
	vec_u = trans_ij_to_xy(position_u);
	vec = { (vec_l.x + vec_r.x) / 2,(vec_l.y + vec_u.y) / 2 };
	barrier_1->setPosition(Vec2(vec.x, vec.y));
	this->addChild(barrier_1);
	barrier.push_back(static_cast<Enemy*>(barrier_1));
}
/*��ʼ��Ϸ*/
void EnemyCreate::start() {
	//��ʼ��Ϸ,�򿪵�����
	auto create_monster = CallFunc::create([=]() {this->scheduleUpdate(); });
	//���뵹��ʱ��ʼ����
	this->runAction(Sequence::create(DelayTime::create(3), create_monster, nullptr));
}
/*update����*/
void EnemyCreate::update(float dt) {
	float& time = enemy_spawn_time;
	float& clear_time = enemy_clear_time;
	int& n = enemy_spawn_n;
	int& flag = enemy_spawn_flag;
	if (if_pause == 0) {
		if (flag == 0) {
			if (monster.size() == 0 && clear_time >= 2) {
				flag = 1;
				clear_time = 0;
				game_waves += 1;
			}
		}
		//�����ǰ����ȫ�壬�һ��й���û��
		if (flag == 1 && current_waves <= max_waves) {
			if (n == 0) {
				monster_appear(monster_data[current_waves - 1][n]);
				n++;
				time = 0;
			}
			else if (time >= 1) {
				monster_appear(monster_data[current_waves - 1][n]);
				n++;
				time = 0;
			}
			if (n == monster_data[current_waves - 1].size()) {
				flag = 0;
				n = 0;
				current_waves += 1;
				if (current_waves == max_waves + 1) {
					extern int all_clear;
					all_clear= 1;
				}
			}
		}
		if (monster.size() == 0 && n == 0 && flag == 0) {
			clear_time += dt * (if_speed_up + 1);
		}
		time += dt * (if_speed_up + 1);
	}
}


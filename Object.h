#pragma once
#include <vector>
#include <cmath>
#include <random>
#include <ctime>
#include <iostream>
#include <Windows.h>
#include <string>



// ���� ��
/*
-����

��ž ��ü
ź ��ü

-ȭ��
ũ�� (����)
����� ���ھ� / id �� ǥ�� (��ü ������ �������� ����Ʈ)




*/



// �ʿ��� ��ü��
/*

����
-> ���̵� / ���ھ� / ü��
   ������Ʈ

������Ʈ
-> �� / ź �����̳� �� draw()
-> ���� �� �� �ı��� �� �� 
-> �� / ź ���� �޼ҵ�
-> �̼��浹 ����
-> ź �������
-> �� y�� ����
-> ������Ʈ�� �ϸ� �� ��/ź ������Ʈ ȣ��
	�浹����

��
-> �ڽ��� y��ġ�� ������ ���ϰ� �� ���
   ��ź �޼ҵ� ȣ��
   �������� ƽ�� ������Ʈ -> �浹���� ��

��ž 
-> ���ʷδ� �������ڸ� ���� / ���� �پ��� ���� �߰����� 
  ȭ��ǥŰ ������ ������Ʈ

ź 
->��ġ / ����
  ������Ʈ -> �浹���� ȣ��

  ������

  Ÿ�̸�1(ƽ) : ź��ġ ������Ʈ -> �浹����
  Ÿ�̸�2(�������) : �����ġ ������Ʈ -> �浹����

  ȭ��ǥ Ű : ��ž���� ������Ʈ

*/

static const double PI = 3.141592;
static const double BallSize = 15;
static const long windowWidth = 400;
static const long windowHighth = 700;

class Block;
class Bullet;
class Object;
class User;


class User
{
private:
	std::wstring name;
	int score = 0;
	int life = 10;

public:
	int GetScore();
	int Getlife();
	void demeged();
};



class Object
{
private:
	std::vector<Block*> blockCon;
	std::vector<Bullet*> bulletCon;
	
	int destroyedBlock;
	double bulletAngle = 0.5 * PI;
	static const int blockSpeed = 5;

public:
	Object();
	~Object();
	User me;
	void SetBulletAngle(POINT mousePt);
	int getDestroedBlock();
	int GetBlockNum();
	int GetBulletNum();
	void DrawCannon(HDC hdc);
	void DrawObject(HDC hdc);

	void UpdateAll();

	void CollisionCheck(); // ���⼭ ��Ʈ���� ȣ��

	void CreateBlock();
	void CreateBullet();

	void DestroyBlock(Block* , int);
	void DestroyBullet(Bullet*, int);

};

class Bullet
{
private:
	bool isOutofWindow = false;
	POINT pt;
	int vec;
	double vecAngel;

public:
	Bullet(double angle);
	~Bullet();
	POINT& getPoint();
	bool GetIsOutofWindow();
	void Update();
	void Draw(HDC hdc);
};

class Block
{
private:
	bool isOutofWindow = false;
	POINT pt;
	POINT vec;

public:
	
	Block(POINT createPT, const int& speed);
	~Block();
	bool GetIsOutofWindow();
	POINT& getPoint();
	void Update();
	void Draw(HDC hdc);
};


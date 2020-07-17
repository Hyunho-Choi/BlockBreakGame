#pragma once
#include <vector>
#include <cmath>
#include <random>
#include <ctime>
#include <iostream>
#include <Windows.h>
#include <string>



// 게임 씬
/*
-변수

포탑 객체
탄 객체

-화면
크기 (고정)
상단은 스코어 / id 등 표시 (객체 생성후 마지막에 프린트)




*/



// 필요한 객체들
/*

유저
-> 아이디 / 스코어 / 체력
   업데이트

오브젝트
-> 블럭 / 탄 컨테이너 및 draw()
-> 현재 블럭 및 파괴된 블럭 수 
-> 블럭 / 탄 삭제 메소드
-> 미세충돌 판정
-> 탄 장외판정
-> 블럭 y값 판정
-> 업데이트를 하면 각 블럭/탄 업데이트 호출
	충돌판정

블럭
-> 자신의 y위치가 일정값 이하가 될 경우
   피탄 메소드 호출
   내려오는 틱당 업데이트 -> 충돌판정 콜

포탑 
-> 최초로는 각도인자만 가짐 / 추후 다양한 상태 추가가능 
  화살표키 누를시 업데이트

탄 
->위치 / 벡터
  업데이트 -> 충돌판정 호출

  윈도우

  타이머1(틱) : 탄위치 업데이트 -> 충돌판정
  타이머2(블록진행) : 블록위치 업데이트 -> 충돌판정

  화살표 키 : 포탑각도 업데이트

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

	void CollisionCheck(); // 여기서 디스트로이 호출

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


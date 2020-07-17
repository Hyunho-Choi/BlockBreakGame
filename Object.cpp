#include "stdafx.h"
#include "Object.h"


Object::Object()
{
	srand((unsigned)time(NULL));
}

Object::~Object()
{
}

void Object::SetBulletAngle(POINT mousePt)
{
	bulletAngle =atan2( 700 - mousePt.y , mousePt.x-200) + (PI * 0.5);
}

int Object::getDestroedBlock()
{
	return destroyedBlock;
}

int Object::GetBlockNum()
{
	return blockCon.size();
}

int Object::GetBulletNum()
{
	return bulletCon.size();
}

void Object::DrawObject(HDC hdc)
{
	int i;
	for (i = 0; i < blockCon.size(); i++)
		blockCon[i]->Draw(hdc);

	for (i = 0; i < bulletCon.size(); i++)
		bulletCon[i]->Draw(hdc);


	
}

void Object::DrawCannon(HDC hdc)
{
	int cannonLen = 15;
	POINT cannon = { windowWidth*0.5, windowHighth - 60 };
	MoveToEx(hdc, cannon.x, cannon.y, NULL);
	LineTo(hdc, cannon.x + (cannonLen * sin(bulletAngle)), cannon.y + (cannonLen * cos(bulletAngle)));
}


void Object::UpdateAll()
{
	//모든 객체들 업데이트
	std::vector<int> delIndex;
	int i;
	for (i = 0; i < blockCon.size(); i++)
	{
		if (blockCon[i]->GetIsOutofWindow())
		{
			delIndex.push_back(i);
			me.demeged();
		}
		else
			blockCon[i]->Update();
	}

	for (i = 0; i < delIndex.size(); i++)
	{
		DestroyBlock(blockCon[delIndex[i]], delIndex[i]);
	}
	blockCon.shrink_to_fit();

	delIndex.clear();


	for (i = 0; i < bulletCon.size(); i++)
	{
		if (bulletCon[i]->GetIsOutofWindow())
			delIndex.push_back(i);
		else
			bulletCon[i]->Update();
	}

	for (i = 0; i < delIndex.size(); i++)
	{
		DestroyBullet(bulletCon[delIndex[i]], delIndex[i]);
	}
	bulletCon.shrink_to_fit();
		
	//충돌판정
	this->CollisionCheck();
}

void Object::CollisionCheck()
{
	for (int i = 0; i < bulletCon.size(); i++)
	{
		//하나와 충돌할경우 break;
		for (int j = 0; j < blockCon.size(); j++)
		{
			if
				(
				(pow
				(
					pow((bulletCon[i]->getPoint().x) - (blockCon[j]->getPoint().x), 2) +
					pow((bulletCon[i]->getPoint().y) - (blockCon[j]->getPoint().y), 2)
					, 0.5
				)) <= BallSize
			)
			{
				this->DestroyBlock(blockCon[j], j);
				this->DestroyBullet(bulletCon[i], i);
				blockCon.shrink_to_fit();
				bulletCon.shrink_to_fit();
				this->destroyedBlock++;
				break;
			}
		}
	}
}

void Object::CreateBlock()
{
	POINT temPt = { rand() % 400, 0 };
	Block* temp = new Block(temPt, blockSpeed);
	blockCon.push_back(temp);
}

void Object::CreateBullet()
{
	Bullet* temp = new Bullet(bulletAngle);
	bulletCon.push_back(temp);
}

void Object::DestroyBlock(Block * Del, int i)
{
	Block* temp = Del;
	this->blockCon.erase(blockCon.begin() + i);
	delete temp;
}

void Object::DestroyBullet(Bullet * Del, int i)
{
	Bullet* temp = Del;
	this->bulletCon.erase(bulletCon.begin() + i);
	delete temp;
}





Bullet::Bullet(double angle)
{
	pt = { windowWidth/2, windowHighth-60 };
	vec = 10;
	vecAngel = angle;
}

Bullet::~Bullet()
{
}

POINT& Bullet::getPoint()
{
	return pt;
}

bool Bullet::GetIsOutofWindow()
{
	return isOutofWindow;
}




void Bullet::Update()
{
	pt.x += vec*sin(vecAngel);
	pt.y += vec*cos(vecAngel);
	if (pt.x < 0 || pt.x > windowWidth || pt.y < 0 || pt.y > windowHighth)
	{
		isOutofWindow = true;
	}
}

void Bullet::Draw(HDC hdc)
{
	MoveToEx(hdc, pt.x, pt.y, NULL);
	LineTo(hdc, pt.x - (2 * vec*sin(vecAngel)), pt.y - (2 * vec*cos(vecAngel)));
}

Block::Block(POINT createPT, const int& speed)
{
	pt = { createPT.x , createPT.y };
	vec = { 0,speed };
}

Block::~Block()
{

}

bool Block::GetIsOutofWindow()
{
	return isOutofWindow;
}

POINT& Block::getPoint()
{
	return pt;
}

void Block::Update()
{
	pt.y += vec.y;
	if (pt.y > windowHighth-60)
	{
		isOutofWindow = true;
	}
}

void Block::Draw(HDC hdc)
{
	Ellipse(hdc, pt.x - BallSize, pt.y - BallSize, pt.x + BallSize, pt.y + BallSize);
}

int User::GetScore()
{
	return score;
}

int User::Getlife()
{
	return life;
}

void User::demeged()
{

	life--;

	if (life <= 0)
	{
		// 게임오버 호출
		PostQuitMessage(0); //임시
	}

}

#pragma once
#include"gameNode.h"
#include"CMap.h"
#include"CPlayer.h"
#include "CCollision.h"

class mainGame : public gameNode
{
private:
	
	CPlayer* player;
	CMap* map;
	CCollision* collision;

public:
	mainGame();
	~mainGame();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
};
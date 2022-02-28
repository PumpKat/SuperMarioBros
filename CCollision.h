#pragma once
#include"gameNode.h"

class CPlayer;
class CMap;

struct Object;
struct Player;

enum DIRECTION {
	LEFT,
	TOP,
	RIGHT,
	BOTTOM,
};

class CCollision :public gameNode
{

private:
	static const int CORRECTION = 5;
	CPlayer* m_Player;
	CMap* m_Map;
	Player* m_PlayerStruct;
	vector<Object> *m_VectObject;


public:
	CCollision();
	~CCollision();

	void getPlayerMemoryLink(CPlayer* PL) { m_Player = PL; }
	void getMapMemoryLink(CMap* Map) { m_Map = Map; }

	HRESULT init();
	void release();
	void update();
	void render();
	
	void CollisionObject(Player* playerStructPointer, vector<Object>* ObjectVectPointer);
	void OnGroundCheck(Player* playerStructPointer, vector<Object>* ObjectVectPointer);
	//충돌 방향 체크 함수
	DIRECTION CollisionDirection(RECT temp,RECT objectRect);
};
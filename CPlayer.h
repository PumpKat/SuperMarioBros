#pragma once
#include"gameNode.h"

enum class MOVESTATE 
{
	LEFTSTOP,
	RIGHTSTOP,
	LEFTWALK,
	RIGHTWALK,
	LEFTJUMP,
	RIGHTJUMP
	/*LEFTSIT,
	RIGHTSIT*/
};

enum POWERSTATE
{
	SMALL,
	BIG,
	FIRE
};

struct Player
{
	RECT playerRect;
	double jumpPower;
	double gravity;
	bool isOnGround;
	bool isJump;
	int Coin;
	int lifeCount;
};

class CPlayer : public gameNode
{
private:
	bool isDebug;
	static const int CORRECTION = 5;

	image* m_player_img;
	Player m_player;
	MOVESTATE playerMoveState;
	int PlayerSpeed;
	
	//중복점프 차단및 점프 스프라이트 조건걸기위해서

	int m_index;
	int m_count;

	int m_camera;

public:

	CPlayer();
	~CPlayer();

	//상태에 따른 스프라이트 출력함수
	void PlayerState(MOVESTATE playerState);
	//카메라의 주소값을 보내주기위한 함수-메인게임
	int* getCameraAdress() { return &m_camera; }
	//플레이어 rect값의 주소를 보내주기위한함수-콜리전
	Player* getPlayerStructAdress() { return &m_player; }

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
};
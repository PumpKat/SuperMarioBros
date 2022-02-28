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
	
	//�ߺ����� ���ܹ� ���� ��������Ʈ ���ǰɱ����ؼ�

	int m_index;
	int m_count;

	int m_camera;

public:

	CPlayer();
	~CPlayer();

	//���¿� ���� ��������Ʈ ����Լ�
	void PlayerState(MOVESTATE playerState);
	//ī�޶��� �ּҰ��� �����ֱ����� �Լ�-���ΰ���
	int* getCameraAdress() { return &m_camera; }
	//�÷��̾� rect���� �ּҸ� �����ֱ������Լ�-�ݸ���
	Player* getPlayerStructAdress() { return &m_player; }

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
};
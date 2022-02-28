#include "framework.h"
#include "CPlayer.h"

CPlayer::CPlayer() {}
CPlayer::~CPlayer() {}

//이곳의 목적
//키입력에따른 플레이어 렉트처리와, 출력 담당,플레이어 정보,카메라 좌표세팅

HRESULT CPlayer::init()
{
	isDebug = false;

	//IMAGE->addImage("카메라", "images/카메라.bmp", WINSIZEX / 10, WINSIZEY / 10, true, RGB(255, 0, 255));
	m_player_img = IMAGE->addFrameImage("마리오", "images/마리오+점프.bmp", 240, 240, 3, 4, true, RGB(255, 0, 255));
	m_player =
	{RectMakeCenter(100, WINSIZEY / 2, m_player_img->getFrameWidth() - CORRECTION * 4 , m_player_img->getFrameHeight() - CORRECTION * 2),
	0.0f,0.5f,false,true,0,3};
	playerMoveState = MOVESTATE::RIGHTJUMP;
	PlayerSpeed = 10;
	m_camera = 0;
	return S_OK;
}

void CPlayer::release() {}

void CPlayer::update()
{

	if (Input::getSingleton()->isOnceKeyDown('F'))
	{
		if (isDebug == true)
		{
			isDebug = false;
		}
		else if (isDebug == false)
		{
			isDebug = true;
		}
	}

	/*m_player.playerRect = RectMakeCenter((m_player.playerRect.left + m_player.playerRect.right) / 2,
		(m_player.playerRect.top + m_player.playerRect.bottom) / 2,
		m_player_img->getFrameWidth() - CORRECTION * 4, m_player_img->getFrameHeight() - CORRECTION * 2);*/

	//상태지정 및 방향키 렉트이동
	{
		if (Input::getSingleton()->isStayKeyDown(VK_RIGHT) &&m_player.playerRect.right < WINSIZEX)
		{
			playerMoveState = MOVESTATE::RIGHTWALK;

			if ((m_player.playerRect.left + m_player.playerRect.right) / 2 <= WINSIZEX / 2/*-200*/)
				//스테이지 왼편에 잇을때
			{
				OffsetRect(&m_player.playerRect, PlayerSpeed, 0);
			}
			else if (m_camera < WINSIZEX * 9.55)
			{
				m_camera += PlayerSpeed;
			}
			else { OffsetRect(&m_player.playerRect, PlayerSpeed, 0); }
		}
		else if (m_player.playerRect.right > WINSIZEX)
		{
			int playerWidth = m_player.playerRect.right - m_player.playerRect.left;
			m_player.playerRect.right = WINSIZEX;
			m_player.playerRect.left = m_player.playerRect.right - playerWidth;
		}

		if (Input::getSingleton()->isStayKeyDown(VK_LEFT) &&m_player.playerRect.left > 0)
		{
			playerMoveState = MOVESTATE::LEFTWALK;
			//OffsetRect(&m_player, -PlayerSpeed, 0);

			if ((m_player.playerRect.left + m_player.playerRect.right) / 2 >= WINSIZEX / 2)
				//플레이어가 맵 오른쪽편에 있을때
			{
				OffsetRect(&m_player.playerRect, -PlayerSpeed, 0);
			}
			else if (m_camera > 0) { m_camera -= PlayerSpeed; }
			else { OffsetRect(&m_player.playerRect, -PlayerSpeed, 0); }
		}
		else if (m_player.playerRect.left < 0)
		{
			int playerWidth = m_player.playerRect.right - m_player.playerRect.left;
			m_player.playerRect.left = 0;
			m_player.playerRect.right = m_player.playerRect.left + playerWidth;
		}

		if (Input::getSingleton()->isOnceKeyUp(VK_RIGHT) && m_player.isOnGround
			|| m_player.isOnGround && playerMoveState == MOVESTATE::RIGHTJUMP
			)
		{
			playerMoveState = MOVESTATE::RIGHTSTOP;
		}
		if (Input::getSingleton()->isOnceKeyUp(VK_LEFT) && m_player.isOnGround
			|| m_player.isOnGround && playerMoveState == MOVESTATE::LEFTJUMP)
		{
			playerMoveState = MOVESTATE::LEFTSTOP;
		}
	}

	if (!m_player.isOnGround) 
	{
		if(playerMoveState == MOVESTATE::RIGHTWALK || playerMoveState == MOVESTATE::RIGHTSTOP)
			playerMoveState = MOVESTATE::RIGHTJUMP;
		if(playerMoveState == MOVESTATE::LEFTWALK || playerMoveState == MOVESTATE::LEFTSTOP)
			playerMoveState = MOVESTATE::LEFTJUMP;
	}

	//점프 및 점프상태변경처리 로직
	{
		if (m_player.isJump == false)
		{
			m_player.playerRect.top += 10;
			m_player.playerRect.bottom += 10;
			if (InputManager->isOnceKeyDown(VK_SPACE)
				&& m_player.isOnGround
				)
			{
				m_player.jumpPower = 15;//점프 초기속력
				m_player.gravity = 0.5f; //중력가속도
				m_player.isOnGround = false;
				m_player.isJump = true;
			}
		}
		if (m_player.isJump)
		{
			m_player.playerRect.top -= m_player.jumpPower;
			m_player.playerRect.bottom -= m_player.jumpPower;
			m_player.jumpPower -= m_player.gravity;
			if (m_player.jumpPower < 0 && m_player.isOnGround)
			{
				m_player.isJump = false;
			}
		}
	}

	//상태에따른 프레임결정
	PlayerState(playerMoveState);
}

void CPlayer::render(HDC hdc)
{
	char str[256];
		SetTextColor(hdc, RGB(0, 0, 255));

	if (isDebug) {
		Rectangle(getMemDC(), m_player.playerRect.left, m_player.playerRect.top, m_player.playerRect.right, m_player.playerRect.bottom);
		sprintf_s(str, "땅위? %s", m_player.isOnGround ? "true" : "false");
		TextOut(hdc, 0, 20, str, strlen(str));
		sprintf_s(str, "점프중? %s", m_player.isJump ? "true" : "false");
		TextOut(hdc, 0, 40, str, strlen(str));
		sprintf_s(str, "점프파워? %f", m_player.jumpPower);
		TextOut(hdc, 0, 60, str, strlen(str));
	}
	//sprintf_s(str, "코인몇개? %d", m_player.Coin);
	//TextOut(hdc, 0, 80, str, strlen(str));
	//IMAGE->render("카메라", getMemDC(), 100 - m_camera / 10, 50);
	IMAGE->frameRender("마리오", getMemDC(), m_player.playerRect.left - CORRECTION*2 , m_player.playerRect.top - CORRECTION , m_player_img->getFrameX(), m_player_img->getFrameY());
}
//상태에따라서 스파라이트 프레임 결정 함수
void CPlayer::PlayerState(MOVESTATE playerState)
{
	switch (playerState)
	{
	case MOVESTATE::LEFTWALK:
		m_count++;
		m_player_img->setFrameY(1);

		if (m_count % 5 == 0)
		{
			m_count = 0;
			m_index--;
			if (m_index <= m_player_img->getMaxFrameX() - 2)
			{
				m_index = m_player_img->getMaxFrameX();
			}
			m_player_img->setFrameX(m_index);
		}
		break;
	case MOVESTATE::RIGHTWALK:
		m_count++;
		m_player_img->setFrameY(0);

		if (m_count % 5 == 0)
		{
			m_count = 0;
			m_index++;
			if (m_index >= m_player_img->getMaxFrameX())
			{
				m_index = 0;
			}
			m_player_img->setFrameX(m_index);
		}
		break;
	case MOVESTATE::LEFTSTOP:
		m_player_img->setFrameY(2);
		m_player_img->setFrameX(1);
		break;
	case MOVESTATE::RIGHTSTOP:
		m_player_img->setFrameY(2);
		m_player_img->setFrameX(0);
		break;
	case MOVESTATE::LEFTJUMP:
		m_player_img->setFrameY(3);
		m_player_img->setFrameX(1);
		break;
	case MOVESTATE::RIGHTJUMP:
		m_player_img->setFrameY(3);
		m_player_img->setFrameX(0);
		break;
	}
}
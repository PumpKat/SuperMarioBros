#include "framework.h"
#include "CCollision.h"
#include "CMap.h"
#include "CPlayer.h"

CCollision::CCollision() {}
CCollision::~CCollision() {}

HRESULT CCollision::init()
{
	m_PlayerStruct = m_Player->getPlayerStructAdress();
	m_VectObject = m_Map->getVectObjectAdress();
	return S_OK;
}

void CCollision::release() {}
void CCollision::update()
{
	OnGroundCheck(m_PlayerStruct, m_VectObject);
	CollisionObject(m_PlayerStruct, m_VectObject);
}
void CCollision::render() {}

void CCollision::CollisionObject(Player* PlayerStructPointer, vector<Object>* ObjectVectPointer)
{
	RECT temp;
	int playerWidth = PlayerStructPointer->playerRect.right - PlayerStructPointer->playerRect.left;
	int playerHeight = PlayerStructPointer->playerRect.bottom - PlayerStructPointer->playerRect.top;

	for (auto &i:*ObjectVectPointer)
	{
		if (!i.isOnScreen) {continue;}
		if (IntersectRect(&temp, &PlayerStructPointer->playerRect, &i.objectRect))
		{
			int tempWidth = temp.right - temp.left;
			int tempHeight = temp.bottom - temp.top;
			switch (CollisionDirection(temp, i.objectRect))
			{
			case TOP:
				if (i.blockType == HIDENBLOCK || i.blockType == VOIDBLOCK || i.blockType == FLAG) { break; }
				if (PlayerStructPointer->isJump == false) {
					PlayerStructPointer->playerRect.bottom -= tempHeight + CORRECTION;
					PlayerStructPointer->playerRect.top -= tempHeight + CORRECTION;
					PlayerStructPointer->jumpPower = 0;
				}
				break;

			case LEFT:
				if (i.blockType == HIDENBLOCK || i.blockType == VOIDBLOCK || i.blockType == FLAG) { break; }
				PlayerStructPointer->playerRect.right -= tempWidth+5;
				PlayerStructPointer->playerRect.left -= tempWidth + 5;
				break;

			case RIGHT:
				if (i.blockType == HIDENBLOCK || i.blockType == VOIDBLOCK || i.blockType == FLAG) { break; }
				PlayerStructPointer->playerRect.left += tempWidth + 5;
				PlayerStructPointer->playerRect.right += tempWidth + 5;
				break;
				
			case BOTTOM:
				if (PlayerStructPointer->playerRect.right - playerWidth / 2 < i.objectRect.right &&
					PlayerStructPointer->playerRect.right - playerWidth / 2 > i.objectRect.left) {
					switch (i.blockType)
					{
					case COINQUESTIONMARK:
						PlayerStructPointer->isJump = false;
						PlayerStructPointer->Coin++;
						if (PlayerStructPointer->Coin >= 100) {
							PlayerStructPointer->Coin = 0;
							PlayerStructPointer->lifeCount++;
						}
						i.blockType = BLANK;
						break;
					case ITEMQUESTIONMARK:
						PlayerStructPointer->isJump = false;
						i.blockType = BLANK;
						break;
					case BRICKS:
						PlayerStructPointer->isJump = false;
						i.blockType = VOIDBLOCK;
						break;
					case HIDENBLOCK:
						if (PlayerStructPointer->jumpPower > 0) {
							PlayerStructPointer->isJump = false;
							i.blockType = BLANK;
						}
						break;
					case STARBRICKS:
						PlayerStructPointer->isJump = false;
						i.blockType = BLANK;
						break;
					case COINBRICKS:
						PlayerStructPointer->Coin++;
						if (PlayerStructPointer->Coin >= 100) {
							PlayerStructPointer->Coin = 0;
							PlayerStructPointer->lifeCount++;
						}
						i.blockType = BLANK;
						break;
					case BLANK:
						PlayerStructPointer->isJump = false;
						break;
					}//switch end
				}//if end
			}//switch end
		}
	}//for end
}

void CCollision::OnGroundCheck(Player* playerStructPointer, vector<Object>* ObjectVectPointer)
{
	RECT temp;
	playerStructPointer->isOnGround = false;
	for (auto& i : *ObjectVectPointer)
	{
		if (i.blockType == HIDENBLOCK || i.blockType == VOIDBLOCK) { continue; }
		if (IntersectRect(&temp, &playerStructPointer->playerRect, &i.objectRect))
			if (CollisionDirection(temp, i.objectRect) == TOP)
				playerStructPointer->isOnGround = true;
		if (playerStructPointer->isOnGround)
			break;
	}
}

DIRECTION CCollision::CollisionDirection(RECT temp, RECT objectRect)
{
	int interWidth = temp.right - temp.left;
	int interHeight = temp.bottom - temp.top;
	if (interWidth > interHeight) {
		if (temp.top == objectRect.top) { return TOP; }
		else { return BOTTOM; }
	}
	else {
		if (temp.left == objectRect.left) { return LEFT; }
		else { return RIGHT; }
	}
}
#include "framework.h"
#include "CMap.h"

//이곳의 목적
//1스테이지에 대한 블록정보, 맵이미지정보, 카메라 좌표처리, 맵 출력담당

CMap::CMap() {}
CMap::~CMap() {}

HRESULT CMap::init()
{
	m_Block_img = IMAGE->addFrameImage("블록", "images/물음표블랭크브릭스블록.bmp", 150, 50, 3, 1, true, RGB(255, 0, 255));
	IMAGE->addImage("배경화면", "images/1스테이지지상만.bmp", WINSIZEX * 10.55, WINSIZEY, true, RGB(255, 0, 255));
	m_Block_img->setFrameY(0);
	isDebug = false;
	//오브젝트 초기화
	{
		//////땅
		vectObjectPushBack(m_InitVectObject, GROUND, 0, 664, 3532, 77);
		vectObjectPushBack(m_InitVectObject, GROUND, 3634, 664, 768, 104);
		vectObjectPushBack(m_InitVectObject, GROUND, 4554, 664, 3278, 104);
		vectObjectPushBack(m_InitVectObject, GROUND, 6859, 613, 204, 50);
		vectObjectPushBack(m_InitVectObject, GROUND, 6910, 561, 154, 52);
		vectObjectPushBack(m_InitVectObject, GROUND, 6962, 510, 102, 52);
		vectObjectPushBack(m_InitVectObject, GROUND, 7013, 458, 52, 52);
		vectObjectPushBack(m_InitVectObject, GROUND, 7167, 459, 52, 52);
		vectObjectPushBack(m_InitVectObject, GROUND, 7167, 509, 102, 52);
		vectObjectPushBack(m_InitVectObject, GROUND, 7167, 559, 152, 52);
		vectObjectPushBack(m_InitVectObject, GROUND, 7167, 609, 202, 52);
		vectObjectPushBack(m_InitVectObject, GROUND, 7576, 612, 256, 52);
		vectObjectPushBack(m_InitVectObject, GROUND, 7626, 562, 206, 52);
		vectObjectPushBack(m_InitVectObject, GROUND, 7676, 512, 156, 52);
		vectObjectPushBack(m_InitVectObject, GROUND, 7726, 462, 106, 52);
		vectObjectPushBack(m_InitVectObject, GROUND, 7934, 462, 52, 52);
		vectObjectPushBack(m_InitVectObject, GROUND, 7934, 512, 102, 52);
		vectObjectPushBack(m_InitVectObject, GROUND, 7934, 562, 152, 52);
		vectObjectPushBack(m_InitVectObject, GROUND, 7934, 612, 202, 52);
		vectObjectPushBack(m_InitVectObject, GROUND, 9165, 564, 100, 99);
		vectObjectPushBack(m_InitVectObject, GROUND, 9265, 612, 461, 52);
		vectObjectPushBack(m_InitVectObject, GROUND, 7934, 664, 2868, 103);
		//진작이렇게할껄
		for (size_t i = 0; i < 8; i++)
		{
			vectObjectPushBack(m_InitVectObject, GROUND, 9265 + 51 * i, 612 - 51 * i, 411 - 51 * i, 53);
		}
		vectObjectPushBack(m_InitVectObject, GROUND, 10136, 613, 52, 52);
		vectObjectPushBack(m_InitVectObject, GROUND, 9675, 254, 51, 409);

		//////파이프
		vectObjectPushBack(m_InitVectObject, GROUND, 1434, 564, 100, 102);
		vectObjectPushBack(m_InitVectObject, GROUND, 1946, 513, 100, 158);
		vectObjectPushBack(m_InitVectObject, GROUND, 2355, 459, 101, 208);

		//////물음표상자
		vectObjectPushBack(m_InitVectObject, ITEMQUESTIONMARK, 1175, 460, 52, 50);
		vectObjectPushBack(m_InitVectObject, ITEMQUESTIONMARK, 3993, 459, 52, 50);
		vectObjectPushBack(m_InitVectObject, ITEMQUESTIONMARK, 5579, 459, 52, 50);

		vectObjectPushBack(m_InitVectObject, COINQUESTIONMARK, 818, 460, 52, 50);
		vectObjectPushBack(m_InitVectObject, COINQUESTIONMARK, 1073, 460, 52, 50);
		vectObjectPushBack(m_InitVectObject, COINQUESTIONMARK, 1124, 254, 52, 50);
		vectObjectPushBack(m_InitVectObject, COINQUESTIONMARK, 4808, 255, 52, 50);
		vectObjectPushBack(m_InitVectObject, COINQUESTIONMARK, 5426, 459, 52, 50);
		vectObjectPushBack(m_InitVectObject, COINQUESTIONMARK, 5426, 459, 52, 50);
		vectObjectPushBack(m_InitVectObject, COINQUESTIONMARK, 5733, 459, 52, 50);
		vectObjectPushBack(m_InitVectObject, COINQUESTIONMARK, 5579, 255, 52, 50);
		vectObjectPushBack(m_InitVectObject, COINQUESTIONMARK, 6602, 254, 52, 50);
		vectObjectPushBack(m_InitVectObject, COINQUESTIONMARK, 6652, 254, 52, 50);
		vectObjectPushBack(m_InitVectObject, COINQUESTIONMARK, 8700, 459, 52, 50);

		vectObjectPushBack(m_InitVectObject, STARBRICKS, 5168, 459, 52, 50);
		vectObjectPushBack(m_InitVectObject, COINBRICKS, 4811, 459, 52, 50);
		///////벽돌
		vectObjectPushBack(m_InitVectObject, BRICKS, 1022, 460, 52, 50);
		vectObjectPushBack(m_InitVectObject, BRICKS, 1124, 460, 52, 50);
		vectObjectPushBack(m_InitVectObject, BRICKS, 1226, 460, 52, 50);
		vectObjectPushBack(m_InitVectObject, BRICKS, 3941, 459, 52, 50);
		vectObjectPushBack(m_InitVectObject, BRICKS, 4042, 459, 52, 50);
		vectObjectPushBack(m_InitVectObject, BRICKS, 4095, 255, 52, 50);
		vectObjectPushBack(m_InitVectObject, BRICKS, 4145, 255, 52, 50);
		vectObjectPushBack(m_InitVectObject, BRICKS, 4195, 255, 52, 50);
		vectObjectPushBack(m_InitVectObject, BRICKS, 4245, 255, 52, 50);
		vectObjectPushBack(m_InitVectObject, BRICKS, 4295, 255, 52, 50);
		vectObjectPushBack(m_InitVectObject, BRICKS, 4345, 255, 52, 50);
		vectObjectPushBack(m_InitVectObject, BRICKS, 4395, 255, 52, 50);
		vectObjectPushBack(m_InitVectObject, BRICKS, 4445, 255, 52, 50);
		vectObjectPushBack(m_InitVectObject, BRICKS, 4658, 255, 52, 50);
		vectObjectPushBack(m_InitVectObject, BRICKS, 4708, 255, 52, 50);
		vectObjectPushBack(m_InitVectObject, BRICKS, 4758, 255, 52, 50);
		vectObjectPushBack(m_InitVectObject, BRICKS, 5118, 459, 52, 50);
		vectObjectPushBack(m_InitVectObject, BRICKS, 6040, 459, 52, 50);
		vectObjectPushBack(m_InitVectObject, BRICKS, 6194, 255, 52, 50);
		vectObjectPushBack(m_InitVectObject, BRICKS, 6244, 255, 52, 50);
		vectObjectPushBack(m_InitVectObject, BRICKS, 6294, 255, 52, 50);
		vectObjectPushBack(m_InitVectObject, BRICKS, 6603, 459, 52, 50);
		vectObjectPushBack(m_InitVectObject, BRICKS, 6653, 459, 52, 50);
		vectObjectPushBack(m_InitVectObject, BRICKS, 6552, 254, 52, 50);
		vectObjectPushBack(m_InitVectObject, BRICKS, 6702, 254, 52, 50);
		vectObjectPushBack(m_InitVectObject, BRICKS, 8600, 459, 52, 50);
		vectObjectPushBack(m_InitVectObject, BRICKS, 8650, 459, 52, 50);
		vectObjectPushBack(m_InitVectObject, BRICKS, 8750, 459, 52, 50);

		//들어가는 파이프
		vectObjectPushBack(m_InitVectObject, INPIPE, 2918, 461, 102, 209);
		vectObjectPushBack(m_InitVectObject, OUTPIPE, 8346, 564, 99, 99);

		//히든블럭//이거는 옆충돌 위충돌 방해처리 안해야한다.
		vectObjectPushBack(m_InitVectObject, HIDENBLOCK, 3275, 407, 52, 55);
		//플래그 따로지정바람
		vectObjectPushBack(m_InitVectObject, FLAG, 10149, 126, 39, 488);
	}

	m_VectObject = m_InitVectObject;
	return S_OK;
}

void CMap::release() {}

void CMap::update()
{
	if (Input::getSingleton()->isOnceKeyDown('D')) 
	{
		if (isDebug == true)
		{
			isDebug = false;
		}
		else if(isDebug == false)
		{
			isDebug = true;
		}
	}

	int j = 0;
	for (auto& i : m_InitVectObject)
	{//초기블록위치에 카메라를 계산한 값이 화면내부인지 체크 
		if (i.objectRect.left - *m_camera <= WINSIZEX - 50)
		{
			m_VectObject[j].isOnScreen = true;
		}
		else { m_VectObject[j].isOnScreen = false; }
		if (i.objectRect.right - *m_camera < +50)
		{
			m_VectObject[j].isOnScreen = false;
		}
		j++;
	}
}

void CMap::render()
{
	IMAGE->render("배경화면", getMemDC(), -*m_camera, 0);

	int j = 0;
	for (auto& i : m_VectObject)
	{
		if (i.isOnScreen)
		{
			bringObject(m_InitVectObject[j].objectRect, i.objectRect, m_camera);
			if (i.blockType == ITEMQUESTIONMARK || i.blockType == COINQUESTIONMARK)
				m_Block_img->setFrameX(0);
			if (i.blockType == STARBRICKS || i.blockType == COINBRICKS || i.blockType == BRICKS)
				m_Block_img->setFrameX(2);
			if (i.blockType == BLANK)
				m_Block_img->setFrameX(1);
			if (i.blockType == ITEMQUESTIONMARK || i.blockType == COINQUESTIONMARK ||
				i.blockType == STARBRICKS || i.blockType == COINBRICKS || i.blockType == BRICKS
				|| i.blockType == BLANK)
				IMAGE->frameRender("블록", getMemDC(), i.objectRect.left, i.objectRect.top, m_Block_img->getFrameX(), m_Block_img->getFrameY());
			if(isDebug)
			Rectangle(getMemDC(), m_VectObject[j].objectRect.left, m_VectObject[j].objectRect.top, m_VectObject[j].objectRect.right, m_VectObject[j].objectRect.bottom);

		}
		j++;
	}
	//IMAGE->render("카메라", getMemDC(), 100 - m_player->getCamera() / 10, 50);
}

void CMap::vectObjectPushBack(vector<Object>& vectInit, BlockType blocktype, int x, int y, int width, int height, bool isCheckOnScreen)
{
	Object ob = { blocktype,RectMake(x,y,width,height), isCheckOnScreen };
	vectInit.push_back(ob);
}

void CMap::bringObject(RECT& initObjectRect, RECT& ObjectRect, int* camera)
{
	ObjectRect.left = initObjectRect.left - *camera;
	ObjectRect.right = initObjectRect.right - *camera;
}
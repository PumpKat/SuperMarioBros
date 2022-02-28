#include"framework.h"
#include "mainGame.h"

mainGame::mainGame() {}
mainGame::~mainGame() {}

HRESULT mainGame::init()
{
	gameNode::init(true);

	player = new CPlayer();
	map = new CMap();
	collision = new CCollision();
	player->init();
	map->init();
	//수정된 데이터를 연동시켜주는 함수
	collision->getPlayerMemoryLink(player);
	collision->getMapMemoryLink(map);
	collision->init();

	map->setMapCameraPointer(player->getCameraAdress());

	return S_OK;
}

void mainGame::release()
{
	gameNode::release();
	SAFE_DELETE(map);
	SAFE_DELETE(player);
	SAFE_DELETE(collision);
}

void mainGame::update()
{
	gameNode::update();
	map->update();
	player->update();
	collision->update();
}

void mainGame::render(HDC hdc)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==============================================

	//Rectangle(getMemDC(), rc.left, rc.top, rc.right, rc.bottom);
	map->render();
	player->render(getMemDC());


	//==============================================

	//백버퍼의 내용을 HDC그린다.(건드리지 말것.)
	this->getBackBuffer()->render(hdc, 0, 0);

}
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
	//������ �����͸� ���������ִ� �Լ�
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

	//������� ������ HDC�׸���.(�ǵ帮�� ����.)
	this->getBackBuffer()->render(hdc, 0, 0);

}
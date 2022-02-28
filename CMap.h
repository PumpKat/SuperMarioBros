#pragma once
#include"gameNode.h"

enum BlockType {
	GROUND=0,
	BLANK,
	COINQUESTIONMARK,
	ITEMQUESTIONMARK,
	BRICKS,
	HIDENBLOCK,
	INPIPE,
	OUTPIPE,
	STARBRICKS,
	COINBRICKS,
	VOIDBLOCK,
	FLAG
};
struct Object
{
	BlockType blockType;
	RECT objectRect;
	bool isOnScreen;
};

class CMap :public gameNode
{
private:
	image* m_Block_img;
	int* m_camera;
	vector<Object> m_InitVectObject;
	vector<Object> m_VectObject;
	bool isDebug;
public:

	CMap();
	~CMap();

	HRESULT init();
	void release();
	void update();
	void render();

	//vectObject�ʱ�ȭ�Լ�
	//���Ʈ�� ,������, �»�ܱ��� ���, ��ŭ, ȭ�鿡 �ִ��� üũ�ϴ� �Һ�������
	void vectObjectPushBack(vector<Object>& vectInit, BlockType blockType, int x, int y, int width, int height,bool isCheckOnScreen=false);
	
	//ī�޶� ���缭 ������Ʈ�� ���Ҵ�����(������,���,��������);
	void bringObject(RECT& initObjectRect, RECT& ObjectRect, int* camera);

	//�÷��̾�ī�޶� �ּ� �޾ƿ� �Լ�-���ΰ��ӿ��� ���
	void setMapCameraPointer(int* plCamera) { m_camera = plCamera; }
	
	//���Ⱑ�����ִ� m_VectObject�� ��������-�ݸ������� ���
	vector<Object>* getVectObjectAdress() { return &m_VectObject; }
};
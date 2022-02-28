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

	//vectObject초기화함수
	//어떤백트에 ,무슨블럭, 좌상단기준 어디에, 얼만큼, 화면에 있는지 체크하는 불변수까지
	void vectObjectPushBack(vector<Object>& vectInit, BlockType blockType, int x, int y, int width, int height,bool isCheckOnScreen=false);
	
	//카메라에 맞춰서 오브젝트를 재할당하자(무엇을,어디에,무엇으로);
	void bringObject(RECT& initObjectRect, RECT& ObjectRect, int* camera);

	//플레이어카메라 주소 받아올 함수-메인게임에서 사용
	void setMapCameraPointer(int* plCamera) { m_camera = plCamera; }
	
	//여기가지고있는 m_VectObject를 보내주자-콜리전에서 사용
	vector<Object>* getVectObjectAdress() { return &m_VectObject; }
};
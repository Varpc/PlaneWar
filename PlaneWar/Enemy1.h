#pragma once
#include "GameEnemy.h"
#include "resource.h"

class CEnemy1 : public CGameEnemy
{
public:
	CEnemy1();
	~CEnemy1();
public:
	BOOL Draw(CDC* pDC, BOOL bPause, int index);

	//��þ�������
	CRect GetRect();
	//�Ƿ񿪻�
	BOOL Fired();
	void AddBomb(CObList & objList, const CPoint & pos); //����ӵ�
	//����ͼƬ
	static BOOL LoadImage();
protected:
	static CImageList m_Images;
};


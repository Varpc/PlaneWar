#pragma once
#include "GameEnemy.h"
#include "resource.h"

class CBoss1 : public CGameEnemy
{
public:
	CBoss1();
	~CBoss1();
public:
	BOOL Draw(CDC* pDC, BOOL bPause, int index);

	//��þ�������
	CRect GetRect();
	BOOL Fired();
	void AddBomb(CObList & objList, const CPoint & pos);
	static BOOL LoadImage();
protected:
	static CImageList m_Images;
	int m_nHor, m_nVor;
	int m_nMaxHP; //���Ѫ��
	CBrush * m_pBrush1, *m_pBrush2;
};


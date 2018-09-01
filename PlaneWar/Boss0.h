#pragma once
#include "GameEnemy.h"
#include "resource.h"
#include "EnBomb0.h"

class CBoss0 : public CGameEnemy
{
public:
	CBoss0();
	~CBoss0();
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


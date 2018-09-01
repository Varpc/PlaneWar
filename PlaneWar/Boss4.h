#pragma once
#include "GameEnemy.h"

class CBoss4 : public CGameEnemy
{
public:
	CBoss4();
	~CBoss4();
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


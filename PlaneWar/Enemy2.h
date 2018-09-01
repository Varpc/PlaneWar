#pragma once
#include "GameEnemy.h"
#include "resource.h"

class CEnemy2 : public CGameEnemy
{
public:
	CEnemy2();
	~CEnemy2();
public:
	BOOL Draw(CDC* pDC, BOOL bPause, int index);

	//获得矩形区域
	CRect GetRect();
	BOOL Fired();
	void AddBomb(CObList & objList, const CPoint & pos);
	static BOOL LoadImage();
protected:
	static CImageList m_Images;
};


#pragma once
#include "GameEnemy.h"
#include "resource.h"

class CEnemy3 : public CGameEnemy
{
public:
	CEnemy3();
	~CEnemy3();
public:
	BOOL Draw(CDC* pDC, BOOL bPause, int index);

	//获得矩形区域
	CRect GetRect();
	BOOL Fired();
	void AddBomb(CObList & objList, const CPoint & ans);
	static BOOL LoadImage();
protected:
	static CImageList m_Images;
};


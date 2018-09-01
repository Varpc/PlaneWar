#pragma once
#include "GameEnemy.h"
#include "EnBomb0.h"
#include "resource.h"

class CEnemy4 : public CGameEnemy
{
public:
	CEnemy4();
	~CEnemy4();
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


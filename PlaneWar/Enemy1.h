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

	//获得矩形区域
	CRect GetRect();
	//是否开火
	BOOL Fired();
	void AddBomb(CObList & objList, const CPoint & pos); //添加子弹
	//加载图片
	static BOOL LoadImage();
protected:
	static CImageList m_Images;
};


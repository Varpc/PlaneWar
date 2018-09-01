#pragma once
#include "GameObject.h"
#include "resource.h"

class CExplosion :public CGameObject
{
public:
	CExplosion(int x, int y);
	~CExplosion(void);

	BOOL Draw(CDC* pDC, BOOL bPause, int nIndex);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + EXPLOSION_WIDTH, m_ptPos.y + EXPLOSION_WIDTH));
	}
private:
	//炸弹的图片列表
	static CImageList m_Images;
	//图像索引的步进计数
	int m_nProcess;
public:
	static const int  EXPLOSION_WIDTH = 66;

};


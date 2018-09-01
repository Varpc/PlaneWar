#pragma once
#include "GameObject.h"
#include "resource.h"

class CCounter : public CGameObject
{
public:
	CCounter(int x = 20, int y = 20);
	~CCounter();

public:

	void PlusNum(int x = 0); //º”“ª
	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x, m_ptPos.y));
	}
	static BOOL LoadImage();
	int GetNum() const;
	BOOL Draw(CDC* pDC, BOOL bPause, int iIndex = 0);
private:
	static CImageList m_Images;
	int m_nCounter;
	int m_iNum[20];
};


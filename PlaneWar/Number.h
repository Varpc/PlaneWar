#pragma once
#include "GameObject.h"
#include "resource.h"

class CNumber : public CGameObject
{
public:
	CNumber(int x = 0, int y = 0, int num = 0);
	~CNumber();
	
	
	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x, m_ptPos.y));
	}

	static BOOL LoadImage();
	BOOL Draw(CDC* pDC, BOOL bPause, int iIndex = 0);
private:
	static CImageList m_Images;
	int m_nTmp[32];
	int m_nNum;
};


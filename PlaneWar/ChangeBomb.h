#pragma once
#include "GameProp.h"

class CChangeBomb :
	public CGameProp
{
public:
	CChangeBomb();
	~CChangeBomb();
public:
	BOOL Draw(CDC* pDC, BOOL bPause, int nIndex);

	//��þ�������
	CRect GetRect();
	static BOOL LoadImage();
private:
	static CImageList m_Images;
};


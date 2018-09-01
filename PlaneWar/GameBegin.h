#pragma once
#include "GameObject.h"

class CGameBegin : public CGameObject
{
public:
	enum Type {back, start, beginback, help, cancel, title, fontback, rank, bossbutton};
	CGameBegin();
	~CGameBegin();
public:
	BOOL Draw(CDC* pDC, BOOL bPause, int nIndex);
	void AddText(CDC* pDC); //Ìí¼ÓÎÄ×Ö
	CRect GetRect();
	CRect GetRectBegin();
	CRect GetRectHelp();
	CRect GetRectCancel();
	CRect GetRectRank();
	CRect GetRectBoss();
	static BOOL LoadImage();
private:
	static CImageList m_Images[9];
};


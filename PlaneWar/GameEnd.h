#pragma once
#include "GameObject.h"
#include "Number.h"

class CGameEnd : public CGameObject
{
	enum {back, restart, cancel, star};
public:
	CGameEnd();
	~CGameEnd();
public:
	BOOL Draw(CDC* pDC, BOOL bPause, int nIndex);
	CRect GetRect();
	CRect GetRectRestart();
	CRect GetRectCancel();
	static BOOL LoadImage();
	void SetScore(int x, char c);
private:
	static CImageList m_Images[4];
	int m_nScore;
	int m_nTime; 
	CNumber * m_pNumber;
public:
	// 记录成绩到文件中
	void SaveScore(int num, char c);
};


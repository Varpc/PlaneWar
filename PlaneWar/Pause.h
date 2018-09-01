#pragma once
#include "GameObject.h"
#include "resource.h"

class CPause :
	public CGameObject
{
	enum {button, restart, cancel};
public:
	CPause(int x, int y);
	~CPause();
public:
	BOOL Draw(CDC *pDC, BOOL bPause, int nIndex);
	CRect GetRect();
	CRect GetRectRestart(); //���¿�ʼ��ť
	CRect GetRectCancel(); //�˳���ť
	static BOOL LoadImage();
	void PauseButton(bool & bPause);
private:
	static CImageList m_Images[3];
	const int PAUSE_HEIGHT = 40;
	const int PAUSE_WIDTH = 50;
};


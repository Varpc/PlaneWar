#pragma once
#include "GameObject.h"
class CText : public CGameObject
{
public:
	CText(int x, int y);
	~CText();

public:
	BOOL Draw(CDC* pDC, BOOL bPause, int nIndex);
	CRect GetRect();
	void SetText(CString text);
private:
	int m_nWait; //文字存在时长
	CString m_text;
};


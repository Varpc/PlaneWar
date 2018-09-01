#include "stdafx.h"
#include "Text.h"


CText::CText(int x, int y):CGameObject(x, y)
{
	m_text = "";
	m_nWait = 30;
}


CText::~CText()
{
}

//无用
CRect CText::GetRect()
{
	return CRect(m_ptPos, CPoint(m_ptPos.x, m_ptPos.y));
}

BOOL CText::Draw(CDC* pDC, BOOL bPause, int nIndex)
{
	if (bPause) return TRUE;
	if (m_nWait <= 0) return FALSE;
	m_nWait--;
	CFont font;
	font.CreateFont(25,
		10,
		0,
		0,
		400,
		FALSE,
		FALSE,
		0,
		ANSI_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS,
		_T("微软雅黑"));  //创建新字体
	pDC->SetBkMode(TRANSPARENT);
	CFont * pOld = pDC->SelectObject(&font);
	pDC->TextOut(m_ptPos.x, m_ptPos.y, m_text);
	pDC->SelectObject(pOld);
	return TRUE;
}


void CText::SetText(CString text)
{
	m_text = text;
	m_nWait = 30;
}
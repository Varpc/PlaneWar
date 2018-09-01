#include "stdafx.h"
#include "Timer.h"


CImageList CTimer::m_Images;
CTimer::CTimer(int x, int y, int time):CGameObject(x, y)
{
	m_nTime = time;
	m_nWait = 60;
}


CTimer::~CTimer()
{
}

CRect CTimer::GetRect()
{
	return CRect(m_ptPos, CPoint(m_ptPos.x + 22, m_ptPos.y + 26));
}

BOOL CTimer::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_NUMYELLOW, RGB(0, 0, 0), 22, 27, 10);
}

BOOL CTimer::Draw(CDC* pDC, BOOL bPause, int nIndex)
{
	if (bPause) return TRUE;
	if (m_nWait > 0) {
		m_nWait--;
	}
	else {
		m_nWait = 60;
		m_nTime--;
	}
	if (m_nTime < 0) return FALSE;
	
	int ans = m_nTime, index = 0;
	CPoint ptAns = m_ptPos;

	if (ans == 0) {
		m_nTemp[index++] = 0;
	}
	else {
		while (ans > 0) {
			m_nTemp[index++] = ans % 10;
			ans /= 10;
		}
	}

	for (int i = index - 1; i >= 0; i--) {
		m_Images.Draw(pDC, m_nTemp[i], ptAns, ILD_TRANSPARENT);
		ptAns.x += 22;
	}
	return TRUE;
}
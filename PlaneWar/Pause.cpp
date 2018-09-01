#include "stdafx.h"
#include "Pause.h"

CImageList CPause::m_Images[3];
CPause::CPause(int x, int y):CGameObject(x, y)
{
}


CPause::~CPause()
{
}

CRect CPause::GetRect()
{
	return CRect(m_ptPos, CPoint(m_ptPos.x + PAUSE_WIDTH, m_ptPos.y + PAUSE_HEIGHT));
}

CRect CPause::GetRectRestart()
{
	return CRect(CPoint(210, 350), CPoint(210 + 175, 350 + 48));
}

CRect CPause::GetRectCancel()
{
	return CRect(CPoint(430, 780), CPoint(430 + 150, 780 + 62));
}



BOOL CPause::LoadImage()
{
	return CGameObject::LoadImage(m_Images[button], IDB_PAUSE, RGB(0, 0, 0), 50, 40, 2) &&
		CGameObject::LoadImage(m_Images[restart], IDB_RESTART, RGB(0, 0, 0), 150, 41, 1) &&
		CGameObject::LoadImage(m_Images[cancel], IDB_OUT, RGB(255, 255, 255), 150, 62, 1);
}

void CPause::PauseButton(bool & bPause)
{
	bPause = !bPause;
}

BOOL CPause::Draw(CDC *pDC, BOOL bPause, int nIndex)
{
	if (bPause) {
		m_Images[button].Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);
		m_Images[restart].Draw(pDC, 0, CPoint(210, 350), ILD_TRANSPARENT);
		m_Images[cancel].Draw(pDC, 0, CPoint(430, 780), ILD_TRANSPARENT);
	}
	else {
		m_Images[button].Draw(pDC, 1, m_ptPos, ILD_TRANSPARENT);
	}
	return TRUE;
}

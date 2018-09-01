#include "stdafx.h"
#include "Wingman.h"


CImageList CWingman::m_Images;
CWingman::CWingman(int x, int y) :CGameBomb(x, y)
{
	m_nV = 8;
	m_nDamage = 100;
}


CWingman::~CWingman()
{
}

CRect CWingman::GetRect()
{
	return CRect(m_ptPos, CPoint(m_ptPos.x + 50, m_ptPos.y + 34));
}

BOOL CWingman::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_WINGMAN, RGB(0, 0, 0), 50, 34, 1);
}

BOOL CWingman::Draw(CDC* pDC, BOOL bPause, int nIndex)
{
	if (!bPause) {
		m_ptPos.y = m_ptPos.y - m_nV;
		//m_ptPos.x = m_ptPos.x + m_nHorLength;
	}
	if (m_ptPos.y < 0 || m_ptPos.x < 0 || m_ptPos.x > GAME_WIDTH) {
		return FALSE;
	}

	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);
	return TRUE;
}

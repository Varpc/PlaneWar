#include "stdafx.h"
#include "Addhp.h"

CImageList CAddhp::m_Images;
CAddhp::CAddhp()
{
	m_ptPos.y = -50;
	m_ptPos.x = rand() % (GAME_WIDTH - 50);
	m_nHor = (rand() % 2 == 0) ? 1 : -1;
	m_nV = rand() % 2 + 1;
	m_nID = 0;
}


CAddhp::~CAddhp()
{
}

BOOL CAddhp::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_ADDHP, RGB(0, 0, 0), 40, 36, 1);
}

CRect CAddhp::GetRect()
{
	return CRect(m_ptPos, CPoint(m_ptPos.x + 40, m_ptPos.y + 36));
}

BOOL CAddhp::Draw(CDC* pDC, BOOL bPause, int nIndex)
{
	if (m_ptPos.y > GAME_HEIGHT) return FALSE;

	if (!bPause) {
		m_ptPos.y += m_nV;
		m_ptPos.x = m_ptPos.x + m_nV * m_nHor;
		if (m_ptPos.x < 0 || m_ptPos.x > GAME_WIDTH)
			m_nHor = -m_nHor;
	}
	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);
	return TRUE;
}

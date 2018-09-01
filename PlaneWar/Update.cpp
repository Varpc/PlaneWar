#include "stdafx.h"
#include "Update.h"


CImageList CUpdate::m_Images;
CUpdate::CUpdate()
{
	m_ptPos.y = -50;
	m_ptPos.x = rand() % (GAME_WIDTH - 50);
	m_nHor = (rand() % 2 == 0) ? 1 : -1;
	m_nV = rand() % 2 + 1;
	m_nID = 1;
}


CUpdate::~CUpdate()
{
}

BOOL CUpdate::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_UPDATE, RGB(0, 0, 0), 40, 24, 1);
}

CRect CUpdate::GetRect()
{
	return CRect(m_ptPos, CPoint(m_ptPos.x + 40, m_ptPos.y + 26));
}

BOOL CUpdate::Draw(CDC* pDC, BOOL bPause, int nIndex)
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

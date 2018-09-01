#include "stdafx.h"
#include "ChangeBomb.h"


CImageList CChangeBomb::m_Images;
CChangeBomb::CChangeBomb()
{
	m_ptPos.y = -50;
	m_ptPos.x = rand() % (GAME_WIDTH - 50);
	m_nHor = (rand() % 2 == 0) ? 1 : -1;
	m_nV = rand() % 2 + 1;
	m_nID = 2;
}


CChangeBomb::~CChangeBomb()
{
}

BOOL CChangeBomb::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_CHANGEBOMB, RGB(255, 255, 255), 40, 26, 1);
}

CRect CChangeBomb::GetRect()
{
	return CRect(m_ptPos, CPoint(m_ptPos.x + 40, m_ptPos.y + 26));
}

BOOL CChangeBomb::Draw(CDC* pDC, BOOL bPause, int nIndex)
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

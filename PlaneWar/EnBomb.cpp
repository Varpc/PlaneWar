#include "stdafx.h"
#include "EnBomb.h"


CImageList CEnBomb::m_Images;
CEnBomb::CEnBomb(int x, int y, double hor) :CGameBomb(x, y, hor)
{
	m_nV = rand() % 1 + 3;
	m_nDamage = 1;
}


CEnBomb::~CEnBomb()
{
}

CRect CEnBomb::GetRect()
{
	return CRect(m_ptPos, CPoint(m_ptPos.x + 8, m_ptPos.y + 24));
}

BOOL CEnBomb::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_ENBOMB, RGB(0, 0, 0), 25, 25, 1);
}

BOOL CEnBomb::Draw(CDC* pDC, BOOL bPause, int nIndex)
{
	if (!bPause) {
		m_ptPos.y = m_ptPos.y + m_nV;
		m_ptPos.x = m_ptPos.x + m_nHorLength * m_nV;
	}
	if (m_ptPos.y < 0 || m_ptPos.x < 0 || m_ptPos.x > GAME_WIDTH || m_ptPos.y > GAME_HEIGHT) {
		return FALSE;
	}

	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);
	return TRUE;
}

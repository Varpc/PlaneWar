#include "stdafx.h"
#include "Bomb0.h"

CImageList CBomb0::m_Images;
CBomb0::CBomb0(int x, int y, double hor):CGameBomb(x, y, hor)
{
	m_nV = 5;
	m_nDamage = 1;
}


CBomb0::~CBomb0()
{
}

CRect CBomb0::GetRect()
{
	return CRect(m_ptPos, CPoint(m_ptPos.x + 8, m_ptPos.y + 24));
}

BOOL CBomb0::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BOMB0, RGB(0, 0, 0), 8, 24, 1);
}

BOOL CBomb0::Draw(CDC* pDC, BOOL bPause, int nIndex)
{
	if (!bPause) {
		m_ptPos.y = m_ptPos.y - m_nV;
		m_ptPos.x = m_ptPos.x + m_nHorLength;
	}
	if (m_ptPos.y < 0 || m_ptPos.x < 0 || m_ptPos.x > GAME_WIDTH) {
		return FALSE;
	}

	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);
	return TRUE;
}



#include "stdafx.h"
#include "Bomb1.h"


CImageList CBomb1::m_Images;
CBomb1::CBomb1(int x, int y, int left, int right, int hor) :CGameBomb(x, y)
{
	m_nV = 5;
	m_nDamage = 1;
	m_nLeft = left;
	m_nRight = right;
	m_nHorLength = 2 * hor;
}

CBomb1::~CBomb1()
{
}

CRect CBomb1::GetRect()
{
	return CRect(m_ptPos, CPoint(m_ptPos.x + 7, m_ptPos.y + 25));
}

BOOL CBomb1::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BOMB1, RGB(255, 255, 255), 7, 25, 1);
}

BOOL CBomb1::Draw(CDC* pDC, BOOL bPause, int nIndex)
{
	if (!bPause) {
		m_ptPos.y = m_ptPos.y - m_nV;
		m_ptPos.x = m_ptPos.x + m_nHorLength;
		if (m_ptPos.x < m_nLeft || m_ptPos.x > m_nRight) {
			m_nHorLength = -m_nHorLength;
		}
		m_nLeft--; m_nRight++;
	}
	if (m_ptPos.y < 0 || m_ptPos.x < -50 || m_ptPos.x > GAME_WIDTH + 50) {
		return FALSE;
	}

	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);
	return TRUE;
}


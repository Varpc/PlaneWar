#include "stdafx.h"
#include "EnBomb1.h"


CImageList CEnBomb1::m_Images;
CEnBomb1::CEnBomb1(int x, int y) :CGameBomb(x, y)
{
	m_nV = 4;
	m_nDamage = 2;
}


CEnBomb1::~CEnBomb1()
{
}

CRect CEnBomb1::GetRect()
{
	return CRect(m_ptPos, CPoint(m_ptPos.x + 20, m_ptPos.y + 36));
}

BOOL CEnBomb1::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BOSSBOMB1, RGB(0, 0, 0), 20, 36, 1);
}

BOOL CEnBomb1::Draw(CDC* pDC, BOOL bPause, int nIndex)
{
	if (!bPause) {
		m_ptPos.y = m_ptPos.y + m_nV;
		//m_ptPos.x = m_ptPos.x + m_nHorLength;
	}
	if (m_ptPos.y < 0 || m_ptPos.x < 0 || m_ptPos.x > GAME_WIDTH || m_ptPos.y > GAME_HEIGHT) {
		return FALSE;
	}

	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);
	return TRUE;
}

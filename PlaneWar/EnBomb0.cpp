#include "stdafx.h"
#include "EnBomb0.h"


CImageList CEnBomb0::m_Images;
CEnBomb0::CEnBomb0(int x, int y) :CGameBomb(x, y)
{
	m_nV = 3;
	m_nDamage = 1;
}


CEnBomb0::~CEnBomb0()
{
}

CRect CEnBomb0::GetRect()
{
	return CRect(m_ptPos, CPoint(m_ptPos.x + 20, m_ptPos.y + 35));
}

BOOL CEnBomb0::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BOSSBOMB0, RGB(0, 0, 0), 20, 35, 1);
}

BOOL CEnBomb0::Draw(CDC* pDC, BOOL bPause, int nIndex)
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

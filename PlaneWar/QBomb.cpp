#include "stdafx.h"
#include "QBomb.h"


CImageList CQBomb::m_Images;
CQBomb::CQBomb(int x, int y):CGameObject(x, y)
{
	m_iY = y;
}

CQBomb::~CQBomb(void)
{

}

BOOL CQBomb::Draw(CDC* pDC, BOOL bPause, int iIndex)
{
	if (m_ptPos.y <= m_iY / 2) return FALSE;
	if (!bPause) {
		m_ptPos.y = m_ptPos.y - 5;
	}
	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);
	return TRUE;
}

BOOL CQBomb::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_QBOMB, RGB(0, 0, 0), 25, 36, 1);
}

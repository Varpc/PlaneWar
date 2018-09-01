#include "stdafx.h"
#include "Bullet.h"


CImageList CBullet::m_Images[4];
CBullet::CBullet(int x, int y, double v, double h, int time):CGameObject(x, y)
{
	m_iVor = v;
	m_iHor = h;
	m_iTime = time;
	m_iWait = 10;
	m_iIndex = 0;
	m_iV = 3;
}


CBullet::~CBullet()
{
}


BOOL CBullet::Draw(CDC* pDC, BOOL bPause, int iIndex)
{
	if (!bPause) {
		if (m_iTime <= 0) return FALSE;
		m_iTime--;

		m_ptPos.x = m_ptPos.x + m_iV * m_iHor;
		m_ptPos.y = m_ptPos.y + m_iV * m_iVor;

		if (m_iWait <= 0) {
			m_iIndex = (m_iIndex + 1) % 4;
			m_iWait = 5;
		}
		else {
			m_iWait--;
		}
	}
	m_Images[m_iIndex].Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);
	return TRUE;
}

BOOL CBullet::LoadImage()
{
	return CGameObject::LoadImage(m_Images[0], IDB_BULLET0, RGB(0, 0, 0), 20, 20, 1) &&
		CGameObject::LoadImage(m_Images[1], IDB_BULLET1, RGB(0, 0, 0), 20, 20, 1) &&
		CGameObject::LoadImage(m_Images[2], IDB_BULLET2, RGB(0, 0, 0), 20, 20, 1) &&
		CGameObject::LoadImage(m_Images[3], IDB_BULLET3, RGB(0, 0, 0), 20, 20, 1);
}
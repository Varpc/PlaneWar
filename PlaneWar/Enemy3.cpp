#include "stdafx.h"
#include "Enemy3.h"


CImageList CEnemy3::m_Images;
CEnemy3::CEnemy3()
{
	m_ptPos.y = -50;
	m_ptPos.x = rand() % (GAME_WIDTH - 50);
	m_nV = 3;
	m_nWait = 100;
	m_nHP = 6;
	m_nDamege = 3;
	m_nID = 3;
}


CEnemy3::~CEnemy3()
{
}

CRect CEnemy3::GetRect()
{
	return CRect(m_ptPos, CPoint(m_ptPos.x + 60, m_ptPos.y + 44));
}

BOOL CEnemy3::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_ENEMY3, RGB(0, 0, 0), 60, 44, 1);
}

BOOL CEnemy3::Fired()
{
	if (rand() % 5 != 0) { //缩小发射子弹的概率
		return FALSE;
	}
	if (m_nWait > 0) {
		m_nWait--;
		return FALSE;
	}
	else {
		m_nWait = INF;
		return TRUE;
	}
}

BOOL CEnemy3::Draw(CDC* pDC, BOOL bPause, int index)
{
	if (m_ptPos.y > 900) return FALSE;
	if (!bPause)
		m_ptPos.y += m_nV;
	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);
	return TRUE;
}

void CEnemy3::AddBomb(CObList & objList, const CPoint & pos)
{
	if (rand() % 2) {
		objList.AddTail(new CEnBomb(m_ptPos.x + 20, m_ptPos.y - 5));
	}
	else {
		double xx = pos.x - m_ptPos.x;
		double yy = pos.y - m_ptPos.y;
		objList.AddTail(new CEnBomb(m_ptPos.x + 20, m_ptPos.y - 5, xx / yy));
	}
}
#include "stdafx.h"
#include "Enemy4.h"

CImageList CEnemy4::m_Images;
CEnemy4::CEnemy4()
{
	m_ptPos.y = -50;
	m_ptPos.x = rand() % (GAME_WIDTH - 50);
	m_nV = 3;
	m_nWait = 50;
	m_nHP = 6;
	m_nDamege = 4;
	m_nID = 4;
}


CEnemy4::~CEnemy4()
{
}

CRect CEnemy4::GetRect()
{
	return CRect(m_ptPos, CPoint(m_ptPos.x + 60, m_ptPos.y + 45));
}

BOOL CEnemy4::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_ENEMY4, RGB(0, 0, 0), 70, 51, 1);
}

BOOL CEnemy4::Fired()
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

BOOL CEnemy4::Draw(CDC* pDC, BOOL bPause, int index)
{
	if (m_ptPos.y > 900) return FALSE;
	if (!bPause)
		m_ptPos.y += m_nV;
	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);
	return TRUE;
}

void CEnemy4::AddBomb(CObList & objList, const CPoint & pos)
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

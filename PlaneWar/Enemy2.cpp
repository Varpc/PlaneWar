#include "stdafx.h"
#include "Enemy2.h"


CImageList CEnemy2::m_Images;
CEnemy2::CEnemy2()
{
	m_ptPos.y = -50;
	m_ptPos.x = rand() % (GAME_WIDTH - 50);
	m_nV = 2;
	m_nWait = 60;
	m_nHP = 4;
	m_nDamege = 2;
	m_nID = 2;
}


CEnemy2::~CEnemy2()
{
}

CRect CEnemy2::GetRect()
{
	return CRect(m_ptPos, CPoint(m_ptPos.x + 60, m_ptPos.y + 44));
}

BOOL CEnemy2::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_ENEMY2, RGB(0, 0, 0), 60, 44, 1);
}

BOOL CEnemy2::Fired()
{
	if (rand() % 4 != 0) { //缩小发射子弹的概率
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

BOOL CEnemy2::Draw(CDC* pDC, BOOL bPause, int index)
{
	if (m_ptPos.y > 900) return FALSE;
	if (!bPause)
		m_ptPos.y += m_nV;
	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);
	return TRUE;
}

void CEnemy2::AddBomb(CObList & objList, const CPoint & pos)
{
	if (rand() % 2) {
		objList.AddTail(new CEnBomb(m_ptPos.x + 20, m_ptPos.y - 5));
	}
	else {
		if (pos.x > m_ptPos.x) {
			objList.AddTail(new CEnBomb(m_ptPos.x + 20, m_ptPos.y - 5, 1.0));
		}
		else {
			objList.AddTail(new CEnBomb(m_ptPos.x + 20, m_ptPos.y - 5, -1.0));
		}
	}
}
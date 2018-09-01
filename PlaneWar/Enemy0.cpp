#include "stdafx.h"
#include "Enemy0.h"

CImageList CEnemy0::m_Images;
CEnemy0::CEnemy0()
{
	m_ptPos.y = -50;
	m_ptPos.x = rand() % (GAME_WIDTH - 50);
	m_nV = 2;
	m_nWait = 60;
	m_nHP = 1;
	m_nDamege = 1;
	m_nID = 0;
}


CEnemy0::~CEnemy0()
{
}

CRect CEnemy0::GetRect() 
{
	return CRect(m_ptPos, CPoint(m_ptPos.x + 60, m_ptPos.y + 45));
}

BOOL CEnemy0::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_ENEMY0, RGB(0,0,0), 60, 45, 1);
}

BOOL CEnemy0::Fired()
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

BOOL CEnemy0::Draw(CDC* pDC, BOOL bPause, int index)
{
	if (m_ptPos.y > GAME_HEIGHT) return FALSE;
	if(!bPause)
		m_ptPos.y += m_nV;
	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);
	return TRUE;
}

void CEnemy0::AddBomb(CObList & objList, const CPoint & pos)
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
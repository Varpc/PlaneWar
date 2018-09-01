#include "stdafx.h"
#include "Enemy1.h"


CImageList CEnemy1::m_Images;
CEnemy1::CEnemy1()
{
	m_ptPos.y = -50;
	m_ptPos.x = rand() % (GAME_WIDTH - 50);
	m_nV = 5;
	m_nHP = 2;
	m_nDamege = 3;
	m_nID = 1;
}


CEnemy1::~CEnemy1()
{
}

CRect CEnemy1::GetRect()
{
	return CRect(m_ptPos, CPoint(m_ptPos.x + 50, m_ptPos.y + 35));
}

BOOL CEnemy1::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_ENEMY1, RGB(0, 0, 0), 50, 35, 1);
}


//不能发射子弹
BOOL CEnemy1::Fired()
{
	return FALSE;
}

BOOL CEnemy1::Draw(CDC* pDC, BOOL bPause, int index)
{
	if (m_ptPos.y > 900) return FALSE;
	if (!bPause)
		m_ptPos.y += m_nV;
	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);
	return TRUE;
}

void CEnemy1::AddBomb(CObList & objList, const CPoint & pos)
{
	//敌机1不发射子弹
}

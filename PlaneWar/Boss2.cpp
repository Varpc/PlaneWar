#include "stdafx.h"
#include "Boss2.h"


CImageList CBoss2::m_Images;
CBoss2::CBoss2()
{
	m_ptPos.y = 1;
	m_ptPos.x = rand() % (GAME_WIDTH - 200);
	m_nV = 1;
	m_nWait = 300;
	m_nMaxHP = m_nHP = 160;
	m_nDamege = 100;
	m_nID = 1;
	m_nHor = rand() % 2 ? 1 : -1;
	m_nVor = 1;
	m_pBrush1 = new CBrush(RGB(255, 0, 0));
	m_pBrush2 = new CBrush(RGB(255, 255, 255));
}


CBoss2::~CBoss2()
{
	delete m_pBrush1;
	delete m_pBrush2;
}

CRect CBoss2::GetRect()
{
	return CRect(m_ptPos, CPoint(m_ptPos.x + 200, m_ptPos.y + 126));
}

BOOL CBoss2::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BOSS2, RGB(0, 0, 0), 200, 126, 1);
}

BOOL CBoss2::Fired()
{
	if (m_nWait > 0) {
		m_nWait--;
		return FALSE;
	}
	else {
		m_nWait = 300;
		return TRUE;
	}
}

BOOL CBoss2::Draw(CDC* pDC, BOOL bPause, int index)
{
	if (!bPause) {
		m_ptPos.y = m_ptPos.y + m_nV * m_nVor;
		m_ptPos.x = m_ptPos.x + m_nV * m_nHor;
		if (m_ptPos.x <= -50 || m_ptPos.x >= GAME_WIDTH - 100)
			m_nHor = -m_nHor;
		if (m_ptPos.y <= -50 || m_ptPos.y >= 100)
			m_nVor = -m_nVor;
	}
	if (m_nHP < 0) return FALSE;
	pDC->FillRect(CRect(m_ptPos.x, m_ptPos.y - 10, m_ptPos.x + 200, m_ptPos.y - 5), m_pBrush2);
	pDC->FillRect(CRect(m_ptPos.x, m_ptPos.y - 10, m_ptPos.x + 200 * (m_nHP * 1.0 / m_nMaxHP), m_ptPos.y - 5), m_pBrush1);
	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);
	return TRUE;
}

void CBoss2::AddBomb(CObList & objList, const CPoint & pos)
{
	if (!this->Fired()) return;
	CPoint ptAns = m_ptPos;
	ptAns.x -= 10;
	ptAns.y += 160;
	for (int i = 0; i < 6; i++) {
		objList.AddTail(new CEnBomb1(ptAns.x, ptAns.y));
		ptAns.x += 40;
	}
}
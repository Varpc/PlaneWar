#include "stdafx.h"
#include "Boss0.h"


CImageList CBoss0::m_Images;
CBoss0::CBoss0()
{
	m_ptPos.y = 1;
	m_ptPos.x = rand() % (GAME_WIDTH - 200);
	m_nV = 1;
	m_nWait = 400;
	m_nMaxHP = m_nHP = 100;
	m_nDamege = 100;
	m_nID = 0;
	m_nHor = rand() % 2 ? 1 : -1;
	m_nVor = 1;
	m_pBrush1 = new CBrush(RGB(255, 0, 0));
	m_pBrush2 = new CBrush(RGB(255, 255, 255));
}


CBoss0::~CBoss0()
{
	delete m_pBrush1;
	delete m_pBrush2;
}

CRect CBoss0::GetRect()
{
	return CRect(m_ptPos, CPoint(m_ptPos.x + 200, m_ptPos.y + 150));
}

BOOL CBoss0::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BOSS0, RGB(0, 0, 0), 200, 150, 1);
}

BOOL CBoss0::Fired()
{
	if (m_nWait > 0) {
		m_nWait--;
		return FALSE;
	}
	else {
		m_nWait = 400;
		return TRUE;
	}
}

BOOL CBoss0::Draw(CDC* pDC, BOOL bPause, int index)
{
	if (!bPause) {
		m_ptPos.y = m_ptPos.y + m_nV * m_nVor;
		m_ptPos.x = m_ptPos.x + m_nV * m_nHor;
		if (m_ptPos.x <= -50 || m_ptPos.x >= GAME_WIDTH - 50)
			m_nHor = -m_nHor;
		if (m_ptPos.y <= -50 || m_ptPos.y >= 100)
			m_nVor = -m_nVor;
	}
	if (m_nHP <= 0) return FALSE;

	pDC->FillRect(CRect(m_ptPos.x, m_ptPos.y - 10, m_ptPos.x + 200, m_ptPos.y - 5), m_pBrush2);
	pDC->FillRect(CRect(m_ptPos.x, m_ptPos.y - 10, m_ptPos.x + 200 * (m_nHP * 1.0 / m_nMaxHP), m_ptPos.y - 5), m_pBrush1);
	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);
	return TRUE;
}

void CBoss0::AddBomb(CObList & objList, const CPoint & pos)
{
	if (!this->Fired()) return;
	CPoint ptAns = m_ptPos;
	ptAns.x -= 10;
	ptAns.y += 160;
	for (int i = 0; i < 6; i++) {
		objList.AddTail(new CEnBomb0(ptAns.x, ptAns.y));
		ptAns.x += 40;
	}
}

#include "stdafx.h"
#include "Back.h"
#include <mmsystem.h>

CImageList CBack::m_Images[5];
CBack::CBack(int x, int y):CGameObject(x, y)
{
}


CBack::~CBack()
{
}

BOOL CBack::Draw(CDC* pDC, BOOL bPause, int iIndex)
{
	if (!bPause) {
		m_ptPos.y++;
	}
	if (m_ptPos.y >= 901) m_ptPos.y = 0;
	m_Images[iIndex].Draw(pDC, 0, m_ptPos, ILD_NORMAL);
	m_Images[iIndex].Draw(pDC, 0, CPoint(m_ptPos.x, m_ptPos.y - 900), ILD_NORMAL);
	return TRUE;
}


BOOL CBack::LoadImage()
{
	return CGameObject::LoadImage(m_Images[0], IDB_BACK0, RGB(0, 0, 0), 600, 900, 1) &&
		CGameObject::LoadImage(m_Images[1], IDB_BACK1, RGB(0, 0, 0), 600, 900, 1) &&
		CGameObject::LoadImage(m_Images[2], IDB_BACK2, RGB(0, 0, 0), 600, 900, 1) &&
		CGameObject::LoadImage(m_Images[3], IDB_BACK3, RGB(0, 0, 0), 600, 900, 1) &&
		CGameObject::LoadImage(m_Images[4], IDB_BACK4, RGB(0, 0, 0), 600, 900, 1);
}


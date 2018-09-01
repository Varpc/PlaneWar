#include "stdafx.h"
#include "Counter.h"

CImageList CCounter::m_Images;
CCounter::CCounter(int x, int y) :CGameObject(x, y)
{
	m_nCounter = 0;
}


CCounter::~CCounter()
{

}

void CCounter::PlusNum(int x)
{
	m_nCounter += x;
}

BOOL CCounter::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_NUMYELLOW, RGB(0, 0, 0), 22, 27, 10);
}


BOOL CCounter::Draw(CDC* pDC, BOOL bPause, int iIndex)
{
	m_ptPos.x = 20;
	if (m_nCounter == 0) {
		m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);
		return TRUE;
	}
	int ans = m_nCounter;
	int index = 0;
	while (ans > 0) {
		m_iNum[index++] = ans % 10;
		ans /= 10;
	}
	for (int i = index - 1; i >= 0; i--) {
		m_Images.Draw(pDC, m_iNum[i], m_ptPos, ILD_TRANSPARENT);
		m_ptPos.x += 22;
	}
	return TRUE;
}

int CCounter::GetNum() const
{
	return m_nCounter;
}
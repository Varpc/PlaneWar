#include "stdafx.h"
#include "Number.h"

CImageList CNumber::m_Images;
CNumber::CNumber(int x, int y, int num):CGameObject(x, y)
{
	m_nNum = num;
}


CNumber::~CNumber()
{
}


BOOL CNumber::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_NUM, RGB(0, 0, 0), 29, 37, 10);
}

BOOL CNumber::Draw(CDC* pDC, BOOL bPause, int iIndex)
{
	int index = 0;
	CPoint ans = m_ptPos;
	if (m_nNum == 0) {
		m_nTmp[index++] = 0;
	}
	else {
		int ans = m_nNum;
		while (ans > 0) {
			m_nTmp[index++] = ans % 10;
			ans /= 10;
		}
	}
	for (int i = index - 1, j = 0; i >= 0; i--, j++) {
		m_Images.Draw(pDC, m_nTmp[i], CPoint(ans.x, ans.y), ILD_TRANSPARENT);
		ans.x += 29;
	}
	return TRUE;
}
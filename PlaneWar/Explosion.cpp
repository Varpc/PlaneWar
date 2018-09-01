#include "stdafx.h"
#include "Explosion.h"


CImageList CExplosion::m_Images;
CExplosion::CExplosion(int x, int y) :CGameObject(x, y), m_nProcess(0)
{
	m_nProcess = 0;
}


CExplosion::~CExplosion()
{
}

BOOL CExplosion::Draw(CDC* pDC, BOOL bPause, int nIndex)
{
	if (m_nProcess == 8)
	{
		m_nProcess = 0;
		return FALSE;
	}

	//用新位置绘制图像
	m_Images.Draw(pDC, m_nProcess, m_ptPos, ILD_TRANSPARENT);
	if (!bPause)
		m_nProcess++;
	return TRUE;
}

BOOL CExplosion::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_EXPLOSION, RGB(0, 0, 0), 66, 66, 8);
}


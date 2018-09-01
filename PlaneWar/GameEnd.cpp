#include "stdafx.h"
#include "GameEnd.h"
#include <string>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

CImageList CGameEnd::m_Images[4];

CGameEnd::CGameEnd()
{
	m_pNumber = NULL;
	m_nTime = 160;
}


CGameEnd::~CGameEnd()
{
	delete m_pNumber;
}

void CGameEnd::SetScore(int num, char c)
{
	//将成绩添加到缓存文件
	std::fstream file;
	file.open("save.txt", std::ios::out | std::ios::app);
	if (file) {
		file << num << " " << c << std::endl;
		file.close();
	}
	m_nScore = num;
	m_pNumber = new CNumber(240, 310, num);
}

CRect CGameEnd::GetRect()
{
	return CRect(CPoint(0,0), CPoint(GAME_WIDTH, GAME_HEIGHT));
}

CRect CGameEnd::GetRectRestart()
{
	return CRect(CPoint(220, 550), CPoint(220 + 150, 550 + 41));
}

CRect CGameEnd::GetRectCancel()
{
	return CRect(CPoint(420, 800), CPoint(420 + 142, 800 + 44));
}

BOOL CGameEnd::Draw(CDC* pDC, BOOL bPause, int nIndex)
{
	if (m_nTime >= 0) m_nTime--;
	if (nIndex == 0) {
		m_Images[back].Draw(pDC, 0, CPoint(0, 100), ILD_NORMAL);
		if(m_pNumber != NULL)
			m_pNumber->Draw(pDC, false, 1);
		m_Images[restart].Draw(pDC, 0, CPoint(220, 550), ILD_TRANSPARENT);
		m_Images[cancel].Draw(pDC, 0, CPoint(420, 800), ILD_TRANSPARENT);
	}
	//绘制星星
	if (m_nTime <= 120 && m_nScore >= 200) {
		m_Images[star].Draw(pDC, 0, CPoint(147, 148), ILD_TRANSPARENT);
	}
	if (m_nTime <= 60 && m_nScore >= 500) {
		m_Images[star].Draw(pDC, 0, CPoint(238, 148), ILD_TRANSPARENT);
	}
	if (m_nTime <= 0 && m_nScore >= 1000) {
		m_Images[star].Draw(pDC, 0, CPoint(325, 148), ILD_TRANSPARENT);
	}
	return TRUE;
}

BOOL CGameEnd::LoadImage()
{
	return CGameObject::LoadImage(m_Images[back], IDB_ENDBACK, RGB(255, 255, 255), 600, 295, 1) &&
		CGameObject::LoadImage(m_Images[restart], IDB_RESTART, RGB(0, 0, 0), 150, 41, 1) &&
		CGameObject::LoadImage(m_Images[cancel], IDB_CANCEL, RGB(0, 0, 0), 142, 44, 1) &&
		CGameObject::LoadImage(m_Images[star], IDB_STAR, RGB(255, 255, 255), 120, 79, 1);
		
}



// 记录成绩到文件中
void CGameEnd::SaveScore(int num, char c)
{
}

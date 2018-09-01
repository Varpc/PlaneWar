#include "stdafx.h"
#include "Rank.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

CImageList CRank::m_Images[4];
CRank::CRank()
{
	m_bGetScore = false;
}


CRank::~CRank()
{
}

BOOL  CRank::Draw(CDC* pDC, BOOL bPause, int nIndex)
{
	m_Images[back].Draw(pDC, 0, m_ptPos, ILD_NORMAL);
	m_Images[cancel].Draw(pDC, 0, CPoint(420, 800), ILD_TRANSPARENT);
	
	CFont font;
	font.CreateFont(40,
		15,
		0,
		0,
		400,
		FALSE,
		FALSE,
		0,
		ANSI_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS,
		_T("微软雅黑"));  //创建新字体
	pDC->SetBkMode(TRANSPARENT);
	CFont * pOld = pDC->SelectObject(&font);
	if (m_bGetScore == FALSE) {
		pDC->TextOut(130, 300, _T("似乎出了点问题^_^..."));
	}
	else {
		if (m_nScore.size() == 0) {
			pDC->TextOut(200, 300, _T("暂无数据"));
		}
		else {
			CString ans;
			for (int i = 0; i < m_nScore.size() && i < 5; i++) {
				if (i != 0) {
					m_Images[bang].Draw(pDC, 0, CPoint(140, 295 + i * 50), ILD_TRANSPARENT);
				}
				m_Images[num].Draw(pDC, i+1, CPoint(140, 312 + i * 50), ILD_TRANSPARENT);
				ans.Format(_T("%d"), m_nScore[i].score);
				pDC->TextOut(200, 305 + i * 50, ans);
				if (m_nScore[i].c == 'a') {
					pDC->TextOut(310, 305 + i * 50, _T("普通模式"));
				}
				else {
					pDC->TextOut(310, 305 + i * 50, _T("Boss模式"));
				}
			}
		}
	}
	pDC->SelectObject(pOld);
	return TRUE;
}

CRect  CRank::GetRect()
{
	return CRect(CPoint(0,0), CPoint(600, 900));
}

CRect CRank::GetRectCancel()
{
	return CRect(CPoint(420, 800), CPoint(420 + 142, 800 + 44));
}

BOOL CRank::LoadImage()
{
	return CGameObject::LoadImage(m_Images[num], IDB_NUMYELLOW, RGB(0, 0, 0), 22, 27, 10) &&
		CGameObject::LoadImage(m_Images[back], IDB_RANK, RGB(0, 0, 0), 580, 870, 1) &&
		CGameObject::LoadImage(m_Images[cancel], IDB_CANCEL, RGB(0, 0, 0), 142, 44, 1) &&
		CGameObject::LoadImage(m_Images[bang], IDB_BANG, RGB(0, 0, 0), 300, 10, 1);
}



// 从文件中得到分数
bool CRank::GetScore()
{
	// TODO: 在此处添加实现代码.

	std::fstream file;
	file.open("save.txt", std::ios::in | std::ios::out | std::ios::app);
	if (file) {
		int a;
		char b;
		std::string s;
		m_nScore.clear();
		while (std::getline(file, s)) {
			std::stringstream ss(s);
			ss >> a >> b;
			m_nScore.push_back({ a, b });
		}
		file.close();
		m_bGetScore = TRUE;
		std::sort(m_nScore.rbegin(), m_nScore.rend());
	}
	return false;
}

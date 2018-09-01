#include "stdafx.h"
#include "GameBegin.h"

CImageList CGameBegin::m_Images[9];
CGameBegin::CGameBegin()
{
}


CGameBegin::~CGameBegin()
{
}

CRect CGameBegin::GetRect()
{
	return CRect(m_ptPos, CPoint(m_ptPos.x + GAME_WIDTH, m_ptPos.y + GAME_HEIGHT));
}

CRect CGameBegin::GetRectBegin()
{
	return CRect(CPoint(210, 350), CPoint(210 + 175, 350 + 48));
}

CRect CGameBegin::GetRectHelp()
{
	return CRect(CPoint(420, 800), CPoint(420 + 150, 800 + 50));
}

CRect CGameBegin::GetRectCancel()
{
	return CRect(CPoint(420, 800), CPoint(420 + 142, 800 + 44));
}

CRect CGameBegin::GetRectRank()
{
	return CRect(CPoint(210, 430), CPoint(210 + 175, 510 + 48));
}

CRect CGameBegin::GetRectBoss()
{
	return CRect(CPoint(210, 430), CPoint(210 + 175, 430 + 46));
}


BOOL CGameBegin::LoadImage()
{
	return CGameObject::LoadImage(m_Images[back], IDB_BEGINBACK, RGB(0, 0, 0), 600, 900, 1) &&
		CGameObject::LoadImage(m_Images[start], IDB_START, RGB(0, 0, 0), 175, 48, 1) &&
		CGameObject::LoadImage(m_Images[beginback], IDB_BEGINBACK1, RGB(255, 255, 255), 198, 69, 1) &&
		CGameObject::LoadImage(m_Images[help], IDB_HELP, RGB(0, 0, 0), 150, 50, 1) &&
		CGameObject::LoadImage(m_Images[cancel], IDB_CANCEL, RGB(0, 0, 0), 142, 44, 1) &&
		CGameObject::LoadImage(m_Images[title], IDB_TITLE, RGB(0, 0, 0), 346, 96, 1) &&
		CGameObject::LoadImage(m_Images[fontback], IDB_BEGINBACK2, RGB(0, 0, 0), 600, 743, 1) &&
		CGameObject::LoadImage(m_Images[rank], IDB_RANKBUTTON, RGB(255, 255, 255), 175, 48, 1) &&
		CGameObject::LoadImage(m_Images[bossbutton], IDB_BOSSBUTTON, RGB(255, 255, 255), 175, 46, 1);
}

BOOL CGameBegin::Draw(CDC* pDC, BOOL bPause, int nIndex)
{
	m_Images[back].Draw(pDC, 0, m_ptPos, ILD_NORMAL);
	m_Images[title].Draw(pDC, 0, CPoint(110, 100), ILD_TRANSPARENT);
	if (nIndex == 0) {
		m_Images[beginback].Draw(pDC, 0, CPoint(195, 340), ILD_TRANSPARENT);
		m_Images[beginback].Draw(pDC, 0, CPoint(195, 420), ILD_TRANSPARENT);
		m_Images[beginback].Draw(pDC, 0, CPoint(195, 500), ILD_TRANSPARENT);
		m_Images[start].Draw(pDC, 0, CPoint(210, 350), ILD_TRANSPARENT);
		m_Images[bossbutton].Draw(pDC, 0, CPoint(210, 430), ILD_TRANSPARENT);
		m_Images[rank].Draw(pDC, 0, CPoint(210, 510), ILD_TRANSPARENT);
		m_Images[help].Draw(pDC, 0, CPoint(420, 800), ILD_TRANSPARENT);
	}
	else if (nIndex == 1) {
		m_Images[fontback].Draw(pDC, 0, CPoint(-10, 200), ILD_TRANSPARENT);
		AddText(pDC);
		m_Images[cancel].Draw(pDC, 0, CPoint(420, 800), ILD_TRANSPARENT);
	}
	return TRUE;
}

void CGameBegin::AddText(CDC* pDC)
{
	CFont font;
	font.CreateFont(20,
		8,
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
		_T("΢���ź�"));  //����������
	pDC->SetBkMode(TRANSPARENT);
	CFont * pOld = pDC->SelectObject(&font);
	pDC->TextOut(10, 300, _T("ս�����ܽ��ܣ�"));
	pDC->TextOut(20, 320, _T("Q����:����һö�ڵ�����һ��λ�ñ�ը�γɶ�������С�ӵ�����boss��ĵл�"));
	pDC->TextOut(20, 340, _T("���б��������ӷֽϵ͡�����ս���ȼ������ӣ�С�ӵ����а˸���Ϊʮ��������"));
	pDC->TextOut(20, 360, _T("ȴʱ�䣺����"));
	pDC->TextOut(20, 380, _T("W����:ս������һ����������Ļ��ܣ����ܿ���ʱ��ս���޵С���ȴʱ�䣺����"));
	pDC->TextOut(20, 400, _T("E����:ս�����м��٣��������룬���ӵ��ٶȻ�����ս���ȼ������Ӷ����ӡ���"));
	pDC->TextOut(20, 420, _T("ȴʱ�䣺����"));
	pDC->TextOut(10, 440, _T("���߽��ܣ�"));
	pDC->TextOut(20, 460, _T("Ѫ����û��һ����Ѫ���������㣬ֱ��ս��Ѫ����Ϊֹ"));
	pDC->TextOut(20, 480, _T("��ɫ���ƣ�����ս��������ս��ÿ��һ�������Ѫ�����ӣ��ӵ���ǿ��������ǿ"));
	pDC->TextOut(20, 500, _T("��ɫ���ƣ������ӵ��任��"));
	pDC->TextOut(10, 520, _T("������ܣ�"));
	pDC->TextOut(20, 540, _T("Bossģʽ�ܹ�����أ�ÿ���Ѷȵ������л��˺������ӣ��ٶȻ����ӣ��л�����Ҳ������"));
	pDC->TextOut(20, 560, _T("ÿ�ػ���ָ����ʱ�ڳ���Boss�����Boss���ɽ�����һ�أ��������Boss����ͨ��"));
	pDC->TextOut(20, 580, _T("��ͨģʽ�ؿ�������Ѷȵ�����ֻ��ս�������Ż����"));
	pDC->TextOut(10, 600, _T("PS��ս���ȼ�Խ�߲�������Խ������ѡ���ʺ��Լ���ս��������ʤ����"));
	pDC->TextOut(10, 620, _T("ף������"));
	pDC->SelectObject(pOld);
}
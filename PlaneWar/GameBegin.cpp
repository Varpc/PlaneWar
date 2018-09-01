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
		_T("微软雅黑"));  //创建新字体
	pDC->SetBkMode(TRANSPARENT);
	CFont * pOld = pDC->SelectObject(&font);
	pDC->TextOut(10, 300, _T("战机技能介绍："));
	pDC->TextOut(20, 320, _T("Q技能:发射一枚炮弹，到一定位置爆炸形成多个方向的小子弹，除boss外的敌机"));
	pDC->TextOut(20, 340, _T("打中必死，但加分较低。随着战机等级的增加，小子弹会有八个变为十六个。冷"));
	pDC->TextOut(20, 360, _T("却时间：六秒"));
	pDC->TextOut(20, 380, _T("W技能:战机产生一个持续两秒的护盾，护盾开启时，战机无敌。冷却时间：七秒"));
	pDC->TextOut(20, 400, _T("E技能:战机进行加速，持续两秒，增加的速度会随着战机等级的增加而增加。冷"));
	pDC->TextOut(20, 420, _T("却时间：七秒"));
	pDC->TextOut(10, 440, _T("道具介绍："));
	pDC->TextOut(20, 460, _T("血包：没吃一个，血量增加两点，直至战机血量满为止"));
	pDC->TextOut(20, 480, _T("蓝色盾牌：用于战机升级。战机每升一级，最高血量增加，子弹增强，技能增强"));
	pDC->TextOut(20, 500, _T("黄色盾牌：用于子弹变换。"));
	pDC->TextOut(10, 520, _T("规则介绍："));
	pDC->TextOut(20, 540, _T("Boss模式总共有五关，每关难度递增，敌机伤害会增加，速度会增加，敌机数量也会增加"));
	pDC->TextOut(20, 560, _T("每关会在指定的时期出现Boss，打败Boss即可进入下一关，打败最终Boss即可通关"));
	pDC->TextOut(20, 580, _T("普通模式关卡随机，难度递增，只有战机死亡才会结束"));
	pDC->TextOut(10, 600, _T("PS：战机等级越高并不代表越厉害，选择适合自己的战机才是制胜王道"));
	pDC->TextOut(10, 620, _T("祝您好运"));
	pDC->SelectObject(pOld);
}
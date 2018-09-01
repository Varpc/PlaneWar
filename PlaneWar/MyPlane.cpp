#include "stdafx.h"
#include "MyPlane.h"


CMyPlane::CMyPlane(int x, int y, int id):CGameObject(x, y)
{
	m_nLevel = 0;
	m_nHorMotion = 0;
	m_nVerMotion = 0;
	m_nWait = 10;
	m_nV = 5;
	m_nEClock = 0;
	m_nWClock = 0;
	m_nQWait = 0;
	m_nWWait = 0;
	m_nEWait = 0;
	m_nRWait = 0;
	m_nHP = 10;
	m_nMaxHP = 10;
	m_nVPlus = 1;
	m_nBombID = 0;
	m_nUser = id;
	m_pBrush1 = new CBrush(RGB(0, 255, 128));
	m_pBrush2 = new CBrush(RGB(255, 255, 255));
	m_pBrush3 = new CBrush(RGB(255, 0, 128));
}

CMyPlane::~CMyPlane(void)
{
	delete m_pBrush1;
	delete m_pBrush2;
	delete m_pBrush3;
}

CImageList CMyPlane::m_Images[7];
CImageList CMyPlane::m_Skill[4];

BOOL CMyPlane::Draw(CDC* pDC, BOOL bPause, int nIndex)
{
	if (!bPause) {
		m_ptPos.x = m_ptPos.x + m_nHorMotion * m_nV;
		m_ptPos.y = m_ptPos.y + m_nVerMotion * m_nV;
		m_nHorMotion = m_nVerMotion = 0;

		//防止飞机出框
		if (m_ptPos.x < 0) m_ptPos.x = 0;
		//根据窗口进行了适当调整
		if (m_ptPos.x > GAME_WIDTH - PLANE_WIDTH - 10) m_ptPos.x = GAME_WIDTH - PLANE_WIDTH - 10;
		if (m_ptPos.y < 0) m_ptPos.y = 0;
		if (m_ptPos.y > GAME_HEIGHT - PLANE_HEIGHT - 70) m_ptPos.y = GAME_HEIGHT - PLANE_HEIGHT - 70;
	}

	//技能时间计时
	this->Timer();

	//技能冷却计时
	this->QWERTimer();

	if (m_nUser == 0) {
		//绘制血条
		pDC->FillRect(CRect(55, 10, 60 + 15 * m_nMaxHP, 25), m_pBrush2);
		if (m_nHP > 2) {
			pDC->FillRect(CRect(55, 10, 60 + 15 * m_nHP, 25), m_pBrush1);
		}
		else {
			pDC->FillRect(CRect(55, 10, 60 + 15 * m_nHP, 25), m_pBrush3);
		}


		//绘制hp字样
		m_Images[hp].Draw(pDC, 0, CPoint(10, 10), ILD_TRANSPARENT);
	}
	else {
		pDC->FillRect(CRect(55, 80, 60 + 15 * m_nMaxHP, 95), m_pBrush2);
		if (m_nHP > 2) {
			pDC->FillRect(CRect(55, 80, 60 + 15 * m_nHP, 95), m_pBrush1);
		}
		else {
			pDC->FillRect(CRect(55, 80, 60 + 15 * m_nHP, 95), m_pBrush3);
		}


		//绘制hp字样
		m_Images[hp].Draw(pDC, 0, CPoint(10, 80), ILD_TRANSPARENT);
	}
	//绘制战机
	m_Images[m_nLevel].Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);
	if (m_nEClock > 0) {
		DrawE(pDC);
	}

	if (m_nWClock > 0) {
		DrawW(pDC);
	}

	if (m_nUser == 0) {
		for (int i = 0; i < 4; i++) {
			m_Skill[i].Draw(pDC, 0, CPoint(180 + 60 * i, 810), ILD_NORMAL);
		}
	}
	return TRUE;
}

BOOL CMyPlane::LoadImage()
{
	return CGameObject::LoadImage(m_Images[leave0], IDB_LEAVE1, RGB(0, 0, 0), 60, 45, 1) &&
		CGameObject::LoadImage(m_Images[leave1], IDB_LEAVE2, RGB(0, 0, 0), 60, 48, 1) &&
		CGameObject::LoadImage(m_Images[leave2], IDB_LEAVE3, RGB(0, 0, 0), 80, 66, 1) &&
		CGameObject::LoadImage(m_Images[leave3], IDB_LEVEL4, RGB(0, 0, 0), 90, 71, 1) &&
		CGameObject::LoadImage(m_Images[hp], IDB_HP, RGB(0, 0, 0), 35, 20, 1) &&
		CGameObject::LoadImage(m_Images[cover], IDB_COVER, RGB(0, 0, 0), 80, 71, 1) &&
		CGameObject::LoadImage(m_Images[tail], IDB_TAIL, RGB(0, 0, 0), 10, 16, 1) &&
		CGameObject::LoadImage(m_Skill[q], IDB_Q, RGB(0, 0, 0), 50, 50, 1) &&
		CGameObject::LoadImage(m_Skill[w], IDB_W, RGB(0, 0, 0), 50, 50, 1) &&
		CGameObject::LoadImage(m_Skill[e], IDB_E, RGB(0, 0, 0), 50, 50, 1) &&
		CGameObject::LoadImage(m_Skill[r], IDB_R, RGB(0, 0, 0), 50, 50, 1);
}

//绘制w技能
void CMyPlane::DrawW(CDC *pDC)
{
	CRect rect = this->GetRect();
	CPoint ans;
	ans.x = (rect.left + rect.right) / 2;
	ans.y = (rect.top + rect.bottom) / 2;
	m_Images[cover].Draw(pDC, 0, CPoint(ans.x - 40, ans.y - 30), ILD_TRANSPARENT);
}

void CMyPlane::DrawE(CDC *pDC)
{
	if (m_nLevel == 0) {
		m_Images[tail].Draw(pDC, 0, CPoint(m_ptPos.x + 12, m_ptPos.y + 45), ILD_TRANSPARENT);
		m_Images[tail].Draw(pDC, 0, CPoint(m_ptPos.x + 37, m_ptPos.y + 45), ILD_TRANSPARENT);
	}
	if (m_nLevel == 1) {
		m_Images[tail].Draw(pDC, 0, CPoint(m_ptPos.x + 8, m_ptPos.y + 40), ILD_TRANSPARENT);
		m_Images[tail].Draw(pDC, 0, CPoint(m_ptPos.x + 42, m_ptPos.y + 40), ILD_TRANSPARENT);
	}if (m_nLevel == 2) {
		m_Images[tail].Draw(pDC, 0, CPoint(m_ptPos.x + 18, m_ptPos.y + 65), ILD_TRANSPARENT);
		m_Images[tail].Draw(pDC, 0, CPoint(m_ptPos.x + 52, m_ptPos.y + 65), ILD_TRANSPARENT);
	}if (m_nLevel == 3) {
		m_Images[tail].Draw(pDC, 0, CPoint(m_ptPos.x + 10, m_ptPos.y + 65), ILD_TRANSPARENT);
		m_Images[tail].Draw(pDC, 0, CPoint(m_ptPos.x + 72, m_ptPos.y + 65), ILD_TRANSPARENT);
	}
}

BOOL CMyPlane::Fired()
{
	if (m_nWait >= 0) {
		m_nWait--;
		return FALSE;
	}
	else {
		m_nWait = 10;
		return TRUE;
	}
}

void CMyPlane::PlusVelocity()
{
	m_nV += m_nVPlus;
	m_nEClock = 180;
}

void CMyPlane::AddCover()
{
	m_nWClock = 120;
}


BOOL CMyPlane::Q()
{
	if (m_nQWait > 0) return FALSE;
	else {
		m_nQWait = 360;
		return TRUE;
	}
}

BOOL CMyPlane::W()
{
	if (m_nWWait > 0) return FALSE;
	else {
		m_nWWait = 420;
		return TRUE;
	}
}

BOOL CMyPlane::E()
{
	if (m_nEWait > 0) return FALSE;
	else {
		m_nEWait = 420; //7秒
		return TRUE;
	}
}

BOOL CMyPlane::R()
{
	if (m_nRWait > 0) return FALSE;
	else {
		m_nRWait = 1200;
		return TRUE;
	}
}

void CMyPlane::QWERTimer()
{
	if (m_nQWait > 0) m_nQWait--;
	if (m_nWWait > 0) m_nWWait--;
	if (m_nEWait > 0) m_nEWait--;
	if (m_nRWait > 0) m_nRWait--;
}

//技能时间计时
void CMyPlane::Timer()
{
	//E技能计时
	if (m_nEClock > 0) {
		m_nEClock--;
	}
	else {
		m_nEClock = 0;
		m_nV = 5;
	}
	//W技能计时
	if (m_nWClock > 0) {
		m_nWClock--;
	}
	else {
		m_nWClock = 0;
	}
}

void CMyPlane::PlusHP(int iPH)
{
	m_nHP += iPH;
	if (m_nHP > m_nMaxHP)
		m_nHP = m_nMaxHP;
}

void CMyPlane::MinusHp(int iPH)
{
	m_nHP -= iPH;
	if (m_nHP < 0) m_nHP = 0;
}

void CMyPlane::PlaneUpdate()
{
	if (m_nLevel + 1 <= 3) {
		m_nLevel++;
		m_nMaxHP += 2;
		m_nVPlus += 1;
		if (m_nLevel == 1) {
			PLANE_WIDTH = 60;
			PLANE_HEIGHT = 48;
		}
		else if (m_nLevel == 2) {
			PLANE_WIDTH = 80;
			PLANE_HEIGHT = 66;
		}
		else if (m_nLevel == 3) {
			PLANE_WIDTH = 90;
			PLANE_HEIGHT = 71;
		}
	}
}

BOOL CMyPlane::WOn()
{
	if (m_nWClock > 0)
		return TRUE;
	return FALSE;
}

int CMyPlane::GetHP() const
{
	return m_nHP;
}

// 添加战机子弹
void CMyPlane::AddBomb(CObList & objList)
{
	// TODO: 在此处添加实现代码.
	if (m_nBombID == 0) {
		if (m_nLevel == 0) {
			objList.AddTail(new CBomb0(m_ptPos.x + 25, m_ptPos.y + 10, 0));
		}
		else if (m_nLevel == 1) {
			objList.AddTail(new CBomb0(m_ptPos.x + 10, m_ptPos.y + 10, 0));
			objList.AddTail(new CBomb0(m_ptPos.x + 40, m_ptPos.y + 10, 0));
		}
		else if (m_nLevel == 2) {
			objList.AddTail(new CBomb0(m_ptPos.x + 15, m_ptPos.y + 10, -1));
			objList.AddTail(new CBomb0(m_ptPos.x + 35, m_ptPos.y + 10, 0));
			objList.AddTail(new CBomb0(m_ptPos.x + 55, m_ptPos.y + 10, 1));
		}
		else if (m_nLevel == 3) {
			objList.AddTail(new CBomb0(m_ptPos.x + 10, m_ptPos.y + 10, 0));
			objList.AddTail(new CBomb0(m_ptPos.x + 32, m_ptPos.y, 0));
			objList.AddTail(new CBomb0(m_ptPos.x + 50, m_ptPos.y, 0));
			objList.AddTail(new CBomb0(m_ptPos.x + 72, m_ptPos.y + 10, 0));
		}
	}
	else if (m_nBombID == 1) {
		if (m_nLevel == 0) {
			objList.AddTail(new CBomb1(m_ptPos.x + 25, m_ptPos.y + 10, m_ptPos.x, m_ptPos.x + 60 - 7, -1));
		}
		else if (m_nLevel == 1) {
			objList.AddTail(new CBomb1(m_ptPos.x + 10, m_ptPos.y + 10, m_ptPos.x, m_ptPos.x + 60 - 7, 1));
			objList.AddTail(new CBomb1(m_ptPos.x + 40, m_ptPos.y + 10, m_ptPos.x, m_ptPos.x + 60 - 7, -1));
		}
		else if (m_nLevel == 2) {
			objList.AddTail(new CBomb1(m_ptPos.x + 15, m_ptPos.y + 10, m_ptPos.x, m_ptPos.x + 80 - 7, 1));
			objList.AddTail(new CBomb1(m_ptPos.x + 35, m_ptPos.y + 10, m_ptPos.x, m_ptPos.x + 80 - 7, 0));
			objList.AddTail(new CBomb1(m_ptPos.x + 55, m_ptPos.y + 10, m_ptPos.x, m_ptPos.x + 80 - 7, -1));
		}
		else if (m_nLevel == 3) {
			objList.AddTail(new CBomb1(m_ptPos.x + 10, m_ptPos.y + 10, m_ptPos.x, m_ptPos.x + 90 - 7, 1));
			objList.AddTail(new CBomb1(m_ptPos.x + 32, m_ptPos.y, m_ptPos.x, m_ptPos.x + 90 - 7, -1));
			objList.AddTail(new CBomb1(m_ptPos.x + 50, m_ptPos.y, m_ptPos.x, m_ptPos.x + 90 - 7, 1));
			objList.AddTail(new CBomb1(m_ptPos.x + 72, m_ptPos.y + 10, m_ptPos.x, m_ptPos.x + 90 - 7, -1));
		}
	}
}

void CMyPlane::SetBomb()
{
	m_nBombID = (m_nBombID + 1) % 2;
}

void CMyPlane::AddR(CObList & objList)
{
	for (int i = 0; i < 10; i++) {
		objList.AddTail(new CWingman(i * 60, 950));
	}
}

int CMyPlane::GetLevel() const
{
	return m_nLevel;
}

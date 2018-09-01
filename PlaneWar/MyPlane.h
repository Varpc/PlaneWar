#pragma once
#include "GameObject.h"
#include "resource.h"

class CMyPlane :public CGameObject
{
	enum Type { leave0, leave1, leave2, leave3, hp, cover, tail };
	enum Skill { q, w, e, r };
public:
	CMyPlane(int x = 0, int y = 0, int id = 0);
	~CMyPlane(void);

	BOOL Draw(CDC* pDC, BOOL bPause, int iIndex);

	static BOOL LoadImage();

	void SetHorMotion(int nMotion)
	{
		m_nHorMotion = nMotion;
	}
	int GetHorMotion() const
	{
		return m_nHorMotion;
	}

	void SetVerMotion(int nMotion)
	{
		m_nVerMotion = nMotion;
	}
	int GetVerMotion() const
	{
		return m_nVerMotion;
	}

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + PLANE_WIDTH, m_ptPos.y + PLANE_HEIGHT));
	}

	void DrawW(CDC *pDC);

	void DrawE(CDC * pDC);

	//是否可以开火发射导弹
	BOOL Fired();
	void PlusVelocity();
	void AddCover();
public:
	int PLANE_WIDTH = 60;
	int PLANE_HEIGHT = 45;
public:
	BOOL Q();
	BOOL W();
	BOOL E();
	BOOL R();
	void QWERTimer();
	void Timer();
	void PlusHP(int iHP); //战机加血
	void MinusHp(int iHP); //战机减血
	void PlaneUpdate();
	BOOL WOn();
	int GetHP() const;
private:
	static CImageList m_Images[7];
	static CImageList m_Skill[4];
	int m_nLevel;
	int    m_nHorMotion;//飞机水平运行方向0->静止，1->右 -1->左
	int    m_nVerMotion;//飞机垂直运行方向0->静止，1->上 -1->下
	int    m_nWait;//发射延时
	int	m_nV; //速度
	int m_nVPlus;
	int m_nWClock, m_nEClock; //WE技能持续时长
	int m_nQWait, m_nWWait, m_nEWait, m_nRWait; //QWER的冷却时间
	int m_nHP, m_nMaxHP; //战机血量 最大血量
	int m_nBombID; //子弹ID
	int m_nUser;
	CBrush * m_pBrush1, *m_pBrush2, * m_pBrush3;

public:
	// 添加战机子弹
	void AddBomb(CObList & objList);
	void SetBomb(); //变换子弹
	void AddR(CObList & objList); //添加大招
	int GetLevel() const;
};


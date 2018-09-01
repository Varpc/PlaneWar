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

	//�Ƿ���Կ����䵼��
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
	void PlusHP(int iHP); //ս����Ѫ
	void MinusHp(int iHP); //ս����Ѫ
	void PlaneUpdate();
	BOOL WOn();
	int GetHP() const;
private:
	static CImageList m_Images[7];
	static CImageList m_Skill[4];
	int m_nLevel;
	int    m_nHorMotion;//�ɻ�ˮƽ���з���0->��ֹ��1->�� -1->��
	int    m_nVerMotion;//�ɻ���ֱ���з���0->��ֹ��1->�� -1->��
	int    m_nWait;//������ʱ
	int	m_nV; //�ٶ�
	int m_nVPlus;
	int m_nWClock, m_nEClock; //WE���ܳ���ʱ��
	int m_nQWait, m_nWWait, m_nEWait, m_nRWait; //QWER����ȴʱ��
	int m_nHP, m_nMaxHP; //ս��Ѫ�� ���Ѫ��
	int m_nBombID; //�ӵ�ID
	int m_nUser;
	CBrush * m_pBrush1, *m_pBrush2, * m_pBrush3;

public:
	// ���ս���ӵ�
	void AddBomb(CObList & objList);
	void SetBomb(); //�任�ӵ�
	void AddR(CObList & objList); //��Ӵ���
	int GetLevel() const;
};


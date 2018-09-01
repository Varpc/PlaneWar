#pragma once
#include "GameObject.h"
#include "resource.h"

class CGameBomb :public CGameObject
{
public:
	CGameBomb(int x = 0, int y = 0, double hor = 0);
	virtual ~CGameBomb();
public:
	virtual BOOL Draw(CDC* pDC, BOOL bPause, int nIndex) = 0;

	//��þ�������
	virtual CRect GetRect() = 0;
	//����ӵ��˺�
	int GetDamage() const;

public:
	int m_nV; //�ӵ��ٶ�
	int m_nDamage; //�ӵ��˺�
	double m_nHorLength;//�ӵ�ˮƽƫ�ƾ���
};


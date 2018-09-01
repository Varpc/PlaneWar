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

	//获得矩形区域
	virtual CRect GetRect() = 0;
	//获得子弹伤害
	int GetDamage() const;

public:
	int m_nV; //子弹速度
	int m_nDamage; //子弹伤害
	double m_nHorLength;//子弹水平偏移距离
};


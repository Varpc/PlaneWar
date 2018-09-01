#pragma once
#include "GameObject.h"
class CGameProp :
	public CGameObject
{
public:
	CGameProp();
	~CGameProp();
public:
	virtual BOOL Draw(CDC* pDC, BOOL bPause, int index) = 0;

	//��þ�������
	virtual CRect GetRect() = 0;
	int GetPropID() const {
		return m_nID;
	}
protected:
	int m_nV;
	int m_nHor;
	int m_nID;
};


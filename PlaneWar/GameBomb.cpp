#include "stdafx.h"
#include "GameBomb.h"




CGameBomb::CGameBomb(int x, int y, double hor):CGameObject(x, y)
{
	m_nHorLength = hor;
}


CGameBomb::~CGameBomb()
{

}

int CGameBomb::GetDamage() const
{
	return m_nDamage;
}

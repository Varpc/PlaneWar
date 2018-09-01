#include "stdafx.h"
#include "GameEnemy.h"


CGameEnemy::CGameEnemy(int x, int y):CGameObject(x, y)
{
}


CGameEnemy::~CGameEnemy()
{
}

int CGameEnemy::GetHP() const
{
	return m_nHP;
}

int CGameEnemy::GetDamege() const
{
	return m_nDamege;
}

int CGameEnemy::GetEnemyID() const
{
	return m_nID;
}

void CGameEnemy::MinusHP(int iHP)
{
	m_nHP -= iHP;
}

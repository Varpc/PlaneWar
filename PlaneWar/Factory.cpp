#include "stdafx.h"
#include "Factory.h"


CFactory::CFactory()
{
}


CFactory::~CFactory()
{
}


CGameEnemy * CFactory::operator()(int nId)
{
	CGameEnemy * pTemp = NULL;
	switch (nId)
	{
	case 0:
		pTemp = new CEnemy0();
		break;
	case 1:
		pTemp = new CEnemy1();
		break;
	case 2:
		pTemp = new CEnemy2();
		break;
	case 3:
		pTemp = new CEnemy3();
		break;
	case 4:
		pTemp = new CEnemy4();
		break;
	default:
		break;
	}
	return pTemp;
}


CGameProp * CFactory::operator() ()
{
	int nId = rand() % 4;
	CGameProp * pTemp = NULL;
	switch (nId)
	{
	case 0:
		pTemp = new CAddhp();
		break;
	case 1:
		pTemp = new CUpdate();
		break;
	case 2: case 3:
		pTemp = new CChangeBomb();
		break;
	default:
		break;
	}
	return pTemp;
}
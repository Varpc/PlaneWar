#pragma once
#include "GameEnemy.h"
#include "GameBomb.h"
#include "GameProp.h"
#include "Enemy0.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Enemy4.h"
#include "Bomb0.h"
#include "EnBomb.h"
#include "Addhp.h"
#include "Update.h"
#include "ChangeBomb.h"


class CFactory
{
public:
	CFactory();
	~CFactory();
public:
	CGameProp * operator() (); //随机生产道具
	CGameEnemy * operator()(int nId); //生产敌机
	CGameBomb * operator() (int nId, int nx, int ny, double hor); //生产战机子弹
};


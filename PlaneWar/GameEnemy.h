#pragma once
#include "GameObject.h"
class CGameEnemy : public CGameObject
{
public:
	CGameEnemy(int x = 0, int y = 0);
	virtual ~CGameEnemy();
	virtual BOOL Draw(CDC* pDC, BOOL bPause, int index) = 0;

	//获得矩形区域
	virtual CRect GetRect() = 0;

	virtual BOOL Fired() = 0; //敌机是否开火
	virtual void AddBomb(CObList & objList, const CPoint & pos) = 0; //添加子弹
	int GetHP() const; //获取敌机血量
	void MinusHP(int iHP); //敌机血量减iHP
	int GetDamege() const; //获取敌机撞击时的破坏力
	int GetEnemyID() const; //获取敌机ID
protected:
	int m_nV, m_nWait; //速度 子弹发射等待时间
	int m_nHP; //敌机血量
	int m_nDamege; //敌机破坏力
	int m_nID; //敌机ID
};


#pragma once
#include "GameObject.h"
class CGameEnemy : public CGameObject
{
public:
	CGameEnemy(int x = 0, int y = 0);
	virtual ~CGameEnemy();
	virtual BOOL Draw(CDC* pDC, BOOL bPause, int index) = 0;

	//��þ�������
	virtual CRect GetRect() = 0;

	virtual BOOL Fired() = 0; //�л��Ƿ񿪻�
	virtual void AddBomb(CObList & objList, const CPoint & pos) = 0; //����ӵ�
	int GetHP() const; //��ȡ�л�Ѫ��
	void MinusHP(int iHP); //�л�Ѫ����iHP
	int GetDamege() const; //��ȡ�л�ײ��ʱ���ƻ���
	int GetEnemyID() const; //��ȡ�л�ID
protected:
	int m_nV, m_nWait; //�ٶ� �ӵ�����ȴ�ʱ��
	int m_nHP; //�л�Ѫ��
	int m_nDamege; //�л��ƻ���
	int m_nID; //�л�ID
};


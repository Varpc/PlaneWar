
// PlaneWarView.h: CPlaneWarView 类的接口
//

#pragma once
#include "Back.h"
#include "Counter.h"
#include "Number.h"
#include "MyPlane.h"
#include "GameBomb.h"
#include "Bullet.h"
#include "QBomb.h"
#include "Factory.h"
#include "GameEnemy.h"
#include "Explosion.h"
#include "Pause.h"
#include "GameEnemy.h"
#include "Boss0.h"
#include "EnBomb0.h"
#include "Text.h"
#include "Timer.h"
#include "GameBegin.h"
#include "GameEnd.h"
#include "Rank.h"
#include "Boss4.h"
#include "Enemy4.h"
#include "ServerSocket.h"
#include "UserSocket.h"

class CPlaneWarView : public CView
{
	enum Type { bomb, bullet, enemy, explosion, qbomb, enBomb, prop, boss, bossBomb, wingman, timer}; //11
	enum GameProcess { begin, help, game, end , rank};
	enum GameType {commonGame, bossGame};
	enum Net {server, host, namal};
protected: // 仅从序列化创建
	CPlaneWarView();
	DECLARE_DYNCREATE(CPlaneWarView)

// 特性
public:
	CPlaneWarDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CPlaneWarView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnInitialUpdate();
	void InitGame();

	afx_msg void OnTimer(UINT_PTR nIDEvent);
private:
	// 设备上下文
	CDC * m_pDC;
	// 背景对象指针
	CBack *m_pBack;
public:
	void ImpactCheck();
	void CatchProp();
	void OnDestroy();
	void StopGame();
private:
	// 内存DC指针
	CDC * m_pMemDC;
	// 内存位图指针
	CBitmap *m_pMemBitmap;
	// 计数对象
	CCounter * m_pCounter;
	//我的战机
	CMyPlane * m_pMyPlane;
	CMyPlane * m_pMyPlane1;
	//文字对象
	CText * m_pText;
	//游戏开始对象
	CGameBegin * m_pBegin;
	//游戏结束对象
	CGameEnd * m_pEnd;
	//排行榜对象
	CRank * m_pRank;
	CServerSocket m_server;
	CUserSocket  m_user;
public:
	// 监测按键，使飞机移动
	void PlaneMove();
	void AI();
	void Plane1Move();
	void MyPlaneShotEnemy();
	void QShotEnemy();
private:
	// 对象链表
	CObList m_objList[11];
	bool m_bPause;
	CPause * m_pPause;
	CFactory m_sampleFactory; //简单工厂，用于生产敌机和道具
	int m_nLevel; //关卡
	int m_nBackLevel; //背景等级
	int m_nCommonLevel;
	int m_mCommonEnemy; //普通模式敌机
	int m_nMaxEnemy; //出现在屏幕上的敌机总数量
	int m_nEnemy; //敌机数量
	int m_nPropWait; //道具生成间隔
	bool m_bNoEnemy; //无敌模式
	bool m_bQUp, m_bWUp, m_bEUp, m_bRUp; //检测qwer按键是否松开
	bool m_bQUp1, m_bWUp1, m_bEUp1, m_bRUp1;
	int m_nLastCounter; //每一关初始时的分数
	BOOL m_bBossHaveDaed;
	int m_nProcess;
	static int m_nWait;
	int m_nGameType; //游戏类型
	int m_nNetID; //
	BOOL bStarted;
	static double m_dMov[16][2];
public:
	// 绘制画面
	void UpdateFrame();
	// 绘制Q技能
	void DrawQBomb();
	// 生产敌机
	void MakeEnemy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	// 关卡升级
	void UpdateLevel();
	// 判断我死了没
	void MyDead();
	// 添加敌机子弹
	void AddEnBomb();
	// 敌机子弹打战机
	void EnBombShootPlane();
	// 载入图片资源
	void LoadImages();
	// 从新启动游戏
	void ReStart();
	// 添加Boss
	void AddBoss();
	// 判断战机子弹打中boss 相撞 并添加爆炸效果
	void BossAndPlane();
	// 添加boss子弹
	void AddBossBomb();
	BOOL GetConnect();
	BOOL GetListen();
	void OnSend(CString & ans);
};

#ifndef _DEBUG  // PlaneWarView.cpp 中的调试版本
inline CPlaneWarDoc* CPlaneWarView::GetDocument() const
   { return reinterpret_cast<CPlaneWarDoc*>(m_pDocument); }
#endif


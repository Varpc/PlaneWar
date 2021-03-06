
// PlaneWarView.cpp: CPlaneWarView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "PlaneWar.h"
#endif

#include "PlaneWarDoc.h"
#include "PlaneWarView.h"
#include <mmsystem.h>
#include <Windows.h>
#pragma comment(lib,"winmm.lib")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlaneWarView

IMPLEMENT_DYNCREATE(CPlaneWarView, CView)

BEGIN_MESSAGE_MAP(CPlaneWarView, CView)
//	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CPlaneWarView 构造/析构

CPlaneWarView::CPlaneWarView()
{
	// TODO: 在此处添加构造代码
}

CPlaneWarView::~CPlaneWarView()
{
}

BOOL CPlaneWarView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CPlaneWarView 绘图

void CPlaneWarView::OnDraw(CDC* /*pDC*/)
{
	CPlaneWarDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CPlaneWarView 诊断

#ifdef _DEBUG
void CPlaneWarView::AssertValid() const
{
	CView::AssertValid();
}

void CPlaneWarView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlaneWarDoc* CPlaneWarView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlaneWarDoc)));
	return (CPlaneWarDoc*)m_pDocument;
}
#endif //_DEBUG


// CPlaneWarView 消息处理程序
int CPlaneWarView::m_nWait = 80;

double CPlaneWarView::m_dMov[16][2] = {
	{1, 0}, {-1, 0}, {0, 1}, {0, -1},
	{0.71, 0.71}, {-0.71, 0.71}, {0.71, -0.71}, {-0.71, -0.71},
	{0.4, 0.9}, {0.9, 0.4}, {-0.4, 0.9}, {0.9, -0.4},
	{0.4, -0.9}, {-0.9, 0.4}, {-0.9, -0.4}, {-0.4, -0.9}
};

void CPlaneWarView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	// TODO: 在此添加专用代码和/或调用基类
	//初始化游戏
	static WSADATA wsaData;
	int ans = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (GetConnect()) {
		m_nNetID = host;
	}
	else if (GetListen()) {
		m_nNetID = server;
	}
	else {
		m_nNetID = namal;
	}
	InitGame();
	LoadImages();
	SetTimer(1, 15, 0);
}

// 载入图片资源
void CPlaneWarView::LoadImages()
{
	// TODO: 在此处添加实现代码.
	CBack::LoadImage();
	CCounter::LoadImage();
	CNumber::LoadImage();
	CMyPlane::LoadImage();
	CBullet::LoadImage();
	CQBomb::LoadImage();
	CEnemy0::LoadImage();
	CEnemy1::LoadImage();
	CEnemy2::LoadImage();
	CEnemy3::LoadImage();
	CEnemy4::LoadImage();
	CBomb0::LoadImage();
	CBomb1::LoadImage();
	CExplosion::LoadImage();
	CPause::LoadImage();
	CAddhp::LoadImage();
	CUpdate::LoadImage();
	CEnBomb::LoadImage();
	CBoss0::LoadImage();
	CBoss1::LoadImage();
	CBoss2::LoadImage();
	CBoss3::LoadImage();
	CBoss4::LoadImage();
	CEnBomb0::LoadImage();
	CEnBomb1::LoadImage();
	CTimer::LoadImage();
	CGameBegin::LoadImage();
	CGameEnd::LoadImage();
	CRank::LoadImage();
	CChangeBomb::LoadImage();
	CWingman::LoadImage();
}

void CPlaneWarView::InitGame()
{	
	PlaySound((LPCTSTR)IDR_BACKSOUND, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC | SND_NODEFAULT | SND_LOOP);
	m_pDC = new CClientDC(this);
	m_pBack = new CBack();

	//建立内存DC
	m_pMemDC = new CDC;
	m_pMemDC->CreateCompatibleDC(m_pDC);

	//建立内存位图
	m_pMemBitmap = new CBitmap;
	m_pMemBitmap->CreateCompatibleBitmap(m_pDC, GAME_WIDTH, GAME_HEIGHT);

	//将位图选入内存DC
	m_pMemDC->SelectObject(m_pMemBitmap);

	m_pCounter = new CCounter(5, 40);
	m_pMyPlane = new CMyPlane(300, 700);
	if (m_nNetID == server) {
		m_pMyPlane1 = new CMyPlane(100, 700, 1);
	}
	m_pPause = new CPause(530, 10);
	m_pBegin = new CGameBegin();
	m_pText = new CText(230, 780);
	m_pEnd = new CGameEnd();
	m_pRank = new CRank();
	//初始化变量
	m_nProcess = begin; //游戏进程初始化
	m_nCommonLevel = 0; //普通模式关卡
	m_nLevel = 0;
	m_nBackLevel = 0;
	m_nMaxEnemy = 10;
	m_mCommonEnemy = 10;
	m_nEnemy = 0;
	m_nPropWait = 1200; //每30秒生成一个道具
	m_bNoEnemy = false;
	m_bPause = false;
	m_nLastCounter = 0;
	m_bBossHaveDaed = FALSE;
	m_bQUp = m_bWUp = m_bEUp = m_bRUp = TRUE;
	m_bQUp1 = m_bWUp1 = m_bEUp1 = m_bRUp1 = TRUE;
}



void CPlaneWarView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	
	Plane1Move();
	if (m_nNetID == host) m_nProcess = begin; //若已经联机，这只画开始界面
	if (m_nProcess == begin || m_nProcess == help) {
		if(m_nProcess == begin)
			m_pBegin->Draw(m_pMemDC, false, 0);
		if(m_nProcess == help)
			m_pBegin->Draw(m_pMemDC, false, 1);
	}
	else if (m_nProcess == game || m_nProcess == end) {
		//控制战机的移动和释放技能
		AI();
		//绘制画面
		UpdateFrame();
		if (m_nProcess == end) {
			m_pEnd->Draw(m_pMemDC, false, 0);
		}
	}
	else if (m_nProcess == rank) {
		m_pRank->Draw(m_pMemDC, false, 0);
	}
	m_pDC->BitBlt(0, 0, GAME_WIDTH, GAME_HEIGHT, m_pMemDC, 0, 0, SRCCOPY);
	CView::OnTimer(nIDEvent);
}

// 绘制画面
void CPlaneWarView::UpdateFrame()
{
	// TODO: 在此处添加实现代码.
	//绘制背景
	m_pBack->Draw(m_pMemDC, m_bPause, m_nBackLevel);

	//绘制子弹 敌机 爆炸
	for (int i = 0; i < 10; i++) {
		//当是Q技能是调用另外一个函数
		if (i == qbomb) {
			DrawQBomb();
			continue;
		}
		POSITION pos, pos1;
		for (pos = m_objList[i].GetHeadPosition(); (pos1 = pos) != NULL; ) {
			CGameObject * pa = (CGameObject *)m_objList[i].GetNext(pos);
			if (!pa->Draw(m_pMemDC, m_bPause, m_nLevel)) {
				if (i == enemy) m_nEnemy--;
				if (i == boss) m_bBossHaveDaed = TRUE;
				m_objList[i].RemoveAt(pos1);
				delete pa;
			}
		}
	}

	//绘制分数
	m_pCounter->Draw(m_pMemDC, m_bPause, 0);

	//绘制暂停按钮
	m_pPause->Draw(m_pMemDC, m_bPause, 0);
	//绘制战机或总成绩
	if (m_nNetID == namal) {
		if (m_pMyPlane->GetHP() > 0) {
			m_pMyPlane->Draw(m_pMemDC, m_bPause, 0);
		}
	}
	else if (m_nNetID == server) {
		if (m_pMyPlane->GetHP() > 0 && m_pMyPlane1->GetHP() > 0) {
			m_pMyPlane->Draw(m_pMemDC, m_bPause, 0);
			m_pMyPlane1->Draw(m_pMemDC, m_bPause, 0);
		}
	}
	m_pText->Draw(m_pMemDC, m_bPause, 0);

	POSITION pos, pos1;
	for (pos = m_objList[timer].GetHeadPosition(); (pos1 = pos) != NULL; ) {
		CGameObject * pa = (CGameObject *)m_objList[timer].GetNext(pos);
		if (!pa->Draw(m_pMemDC, m_bPause, m_nLevel)) {
			m_objList[timer].RemoveAt(pos1);
			delete pa;
		}
	}
}

// 绘制Q技能
void CPlaneWarView::DrawQBomb()
{
	// TODO: 在此处添加实现代码.
	POSITION pos, pos1;
	for (pos = m_objList[qbomb].GetHeadPosition(); (pos1 = pos) != NULL;) {
		CGameObject * pa = (CGameObject *)m_objList[qbomb].GetNext(pos);
		if (!pa->Draw(m_pMemDC, m_bPause, 0)) {
			for (int i = 0; i < 8; i++) {
				m_objList[bullet].AddTail(new CBullet(pa->GetPoint().x, pa->GetPoint().y, m_dMov[i][0], m_dMov[i][1], 20 * (m_pMyPlane->GetLevel() + 1)));
			}
			if (m_pMyPlane->GetLevel() >= 2) {
				for (int i = 8; i < 16; i++) {
					m_objList[bullet].AddTail(new CBullet(pa->GetPoint().x, pa->GetPoint().y, m_dMov[i][0], m_dMov[i][1], 20 * (m_pMyPlane->GetLevel() + 1)));
				}
			}
			m_objList[qbomb].RemoveAt(pos1);
			delete pa;
		}
	}
}

// 监测按键，使飞机移动和释放技能
void CPlaneWarView::PlaneMove()
{
	// TODO: 在此处添加实现代码.
	if (GetKeyState(VK_SPACE) < 0 && m_pMyPlane->Fired()) {
		//根据战机等级添加子弹
		m_pMyPlane->AddBomb(m_objList[bomb]);
	}
	if (GetKeyState(VK_LEFT) < 0) {
		m_pMyPlane->SetHorMotion(-1);
	}
	if (GetKeyState(VK_RIGHT) < 0) {
		m_pMyPlane->SetHorMotion(1);
	}
	if (GetKeyState(VK_UP) < 0) {
		m_pMyPlane->SetVerMotion(-1);
	}
	if (GetKeyState(VK_DOWN) < 0) {
		m_pMyPlane->SetVerMotion(1);
	}
	if (GetKeyState('E') < 0 && m_bEUp) {
		if (m_pMyPlane->E()) {
			m_pMyPlane->PlusVelocity();
			m_objList[timer].AddTail(new CTimer(300, 810, 6));
		}
		else {
			m_pText->SetText(_T("E技能冷却中！"));
		}
		m_bEUp = FALSE;
	}
	if (GetKeyState('E') >= 0) m_bEUp = TRUE;
	if (GetKeyState('W') < 0 && m_bWUp) {
		if (m_pMyPlane->W()) {
			m_pMyPlane->AddCover();
			m_objList[timer].AddTail(new CTimer(240, 810, 6));
		}
		else {
			m_pText->SetText(_T("W技能冷却中！"));
		}
		m_bWUp = FALSE;
	}
	if (GetKeyState('W') >= 0) m_bWUp = TRUE;
	if (GetKeyState('Q') < 0 && m_bQUp) {
		if (m_pMyPlane->Q()) {
			m_objList[qbomb].AddTail(new CQBomb((m_pMyPlane->GetRect().left + m_pMyPlane->GetRect().right) / 2 - 12, m_pMyPlane->GetRect().top - 15));
			m_objList[timer].AddTail(new CTimer(180, 810, 5));
		}
		else {
			m_pText->SetText(_T("Q技能冷却中！"));
		}
		m_bQUp = FALSE;
	}
	if (GetKeyState('Q') >= 0) m_bQUp = TRUE;
	if (GetKeyState('R') < 0 && m_bRUp) {
		if (m_pMyPlane->R()) {
			m_pMyPlane->AddR(m_objList[wingman]);
			m_objList[timer].AddTail(new CTimer(360, 810, 20));
		}
		else {
			m_pText->SetText(_T("R技能冷却中！"));
		}
		m_bRUp = FALSE;
	}
	if (GetKeyState('R') >= 0) m_bRUp = TRUE;
	if (GetKeyState('Z') < 0) {
		m_bNoEnemy = TRUE;
	}
}


void CPlaneWarView::AI()
{
	if (m_bPause) return;
	//生成道具
	if (m_nPropWait <= 0) {
		m_objList[prop].AddTail(m_sampleFactory());
		m_nPropWait = 800;
	}
	m_nPropWait--;
	//生产敌机
	MakeEnemy();
	//产生敌机子弹
	AddEnBomb();
	AddBossBomb(); //添加boss子弹
	//所有改变战机死活的函数都应在战机活着的情况下进行
	if (m_nNetID == namal && m_pMyPlane->GetHP() > 0) {
		UpdateLevel();		//关卡升级 添加boss判断
		BossAndPlane();
		MyPlaneShotEnemy(); //战机子弹炸掉敌机
		QShotEnemy();		//战机Q技能炸掉敌机
		ImpactCheck();		//战机敌机碰撞检测
		EnBombShootPlane(); //敌机子弹炸掉战机
		CatchProp();		//判断飞机是否吃到道具
		PlaneMove();		//监测按键
		MyDead();
	}
	else if (m_nNetID == server && m_pMyPlane->GetHP() > 0 && m_pMyPlane1->GetHP() > 0) {
		UpdateLevel();		//关卡升级 添加boss判断
		BossAndPlane();
		MyPlaneShotEnemy(); //战机子弹炸掉敌机
		QShotEnemy();		//战机Q技能炸掉敌机
		ImpactCheck();		//战机敌机碰撞检测
		EnBombShootPlane(); //敌机子弹炸掉战机
		CatchProp();		//判断飞机是否吃到道具
		PlaneMove();		//监测按键
		MyDead();
	}
}

void CPlaneWarView::Plane1Move()
{
	if (m_nNetID == host) {
		CString ans;
		if (GetKeyState(VK_SPACE) < 0) {
			//根据战机等级添加子弹
			ans += 'K';
		}
		if (GetKeyState(VK_LEFT) < 0) {
			ans += 'L';
		}
		if (GetKeyState(VK_RIGHT) < 0) {
			ans += 'Y';
		}
		if (GetKeyState(VK_UP) < 0) {
			ans += 'U';
		}
		if (GetKeyState(VK_DOWN) < 0) {
			ans += 'D';
		}
		if (GetKeyState('E') < 0 ) {
			ans += 'E';
		}
		if (GetKeyState('W') < 0) {
			ans += 'W';
		}
		if (GetKeyState('Q') < 0) {
			ans += 'Q';
		}
		if (GetKeyState('R') < 0) {
			ans += 'R';
		}
		this->OnSend(ans);
	}
	else if (m_nNetID == server) {
		std::string ans = m_server.GetMove();
		for (int i = 0; i < ans.size(); i++) {
			switch (ans[i])
			{
			case 'K':
				if(m_pMyPlane1->Fired())
				m_pMyPlane1->AddBomb(m_objList[bomb]);
				break;
			case 'U':
				m_pMyPlane1->SetVerMotion(-1);
				break;
			case 'D':
				m_pMyPlane1->SetVerMotion(1);
				break;
			case 'L':
				m_pMyPlane1->SetHorMotion(-1);
				break;
			case 'Y':
				m_pMyPlane1->SetHorMotion(1);
				break;
			case 'Q':
				if(m_pMyPlane1->Q())
					m_objList[qbomb].AddTail(new CQBomb((m_pMyPlane1->GetRect().left + m_pMyPlane1->GetRect().right) / 2 - 12, m_pMyPlane1->GetRect().top - 15));
				break;
			case 'W':
				if(m_pMyPlane1->W())
					m_pMyPlane1->AddCover();
				break;
			case 'E':
				if(m_pMyPlane1->E())
					m_pMyPlane1->PlusVelocity();
				break;
			case 'R':
				if(m_pMyPlane1->R())
					m_pMyPlane1->AddR(m_objList[wingman]);
				break;
			default:
				break;
			}
		}
	}
}

// 判断战机子弹打中boss 相撞 并添加爆炸效果
void CPlaneWarView::BossAndPlane()
{
	// TODO: 在此处添加实现代码.
	POSITION pos1, pos2, pos3, pos4;
	CRect rectPlane, rect1, rect2, tmp;
	rectPlane = m_pMyPlane->GetRect();
	//boss子弹和战机
	for (pos1 = m_objList[bossBomb].GetHeadPosition(); (pos2 = pos1) != NULL; ) {
		CGameBomb * pb = (CGameBomb *)m_objList[bossBomb].GetNext(pos1);
		rect2 = pb->GetRect();
		if (tmp.IntersectRect(&rectPlane, &rect2)) {
			if (!m_pMyPlane->WOn() && !m_bNoEnemy)
				m_pMyPlane->MinusHp(pb->GetDamage());
			m_objList[bossBomb].RemoveAt(pos2);
			delete pb;
		}
	}

	if (m_nNetID == server) {
		//boss子弹和战机
		CRect rect3 = m_pMyPlane1->GetRect();
		for (pos1 = m_objList[bossBomb].GetHeadPosition(); (pos2 = pos1) != NULL; ) {
			CGameBomb * pb = (CGameBomb *)m_objList[bossBomb].GetNext(pos1);
			rect2 = pb->GetRect();
			if (tmp.IntersectRect(&rect3, &rect2)) {
				if (!m_pMyPlane1->WOn() && !m_bNoEnemy)
					m_pMyPlane1->MinusHp(pb->GetDamage());
				m_objList[bossBomb].RemoveAt(pos2);
				delete pb;
			}
		}
	}

	//boss子弹和战机子弹
	for (pos1 = m_objList[bossBomb].GetHeadPosition(); (pos2 = pos1) != NULL; ) {
		CGameBomb * pb = (CGameBomb *)m_objList[bossBomb].GetNext(pos1);
		rect1 = pb->GetRect();
		for (pos3 = m_objList[bomb].GetHeadPosition(); (pos4 = pos3) != NULL; ) {
			CGameBomb * pb1 = (CGameBomb *)m_objList[bomb].GetNext(pos3);
			rect2 = pb1->GetRect();
			if (tmp.IntersectRect(&rect1, &rect2)) {
				m_objList[bomb].RemoveAt(pos4);
				m_objList[bossBomb].RemoveAt(pos2);
				delete pb;
				delete pb1;
				break;
			}
		}
	}

	POSITION pos = m_objList[boss].GetHeadPosition();
	if (pos == NULL) return; //当boss不存在时，返回
	CGameEnemy * pBoss = (CGameEnemy *)m_objList[boss].GetAt(pos);
	rect2 = pBoss->GetRect();
	if (tmp.IntersectRect(&rectPlane, &rect2)) {
		if(!m_bNoEnemy)
			m_pMyPlane->MinusHp(pBoss->GetDamege());
		return;
	}

	for (pos1 = m_objList[bomb].GetHeadPosition(); (pos2 = pos1) != NULL; ) {
		CGameBomb * pb = (CGameBomb *)m_objList[bomb].GetNext(pos1);
		rectPlane = pb->GetRect();
		if (tmp.IntersectRect(&rectPlane, &rect2)) {
			pBoss->MinusHP(pb->GetDamage());
			m_objList[explosion].AddTail(new CExplosion(pb->GetPoint().x, pb->GetPoint().y - 30));
			m_objList[bomb].RemoveAt(pos2);
			delete pb;
		}
	}

	for (pos1 = m_objList[bullet].GetHeadPosition(); (pos2 = pos1) != NULL; ) {
		CGameObject * pb = (CGameObject *)m_objList[bullet].GetNext(pos1);
		rectPlane = pb->GetRect();
		if (tmp.IntersectRect(&rectPlane, &rect2)) {
			pBoss->MinusHP(2);
			m_objList[explosion].AddTail(new CExplosion(pb->GetPoint().x, pb->GetPoint().y - 30));
			m_objList[bullet].RemoveAt(pos2);
			delete pb;
		}
	}
}

// 判断我死了没
void CPlaneWarView::MyDead()
{
	// TODO: 在此处添加实现代码.

	if (m_nNetID == namal && m_pMyPlane->GetHP() <= 0) {
		m_objList[explosion].AddTail(new CExplosion(m_pMyPlane->GetPoint().x, m_pMyPlane->GetPoint().y));
		switch (m_nGameType)
		{
		case commonGame:
			m_pEnd->SetScore(m_pCounter->GetNum(), 'a');
			break;
		case bossGame:
			m_pEnd->SetScore(m_pCounter->GetNum(), 'b');
			break;
		default:
			break;
		}
		m_nProcess = end;
	}
	else if (m_nNetID == server && (m_pMyPlane->GetHP() <= 0 || m_pMyPlane1->GetHP() <= 0)) {
		m_objList[explosion].AddTail(new CExplosion(m_pMyPlane->GetPoint().x, m_pMyPlane->GetPoint().y));
		m_objList[explosion].AddTail(new CExplosion(m_pMyPlane1->GetPoint().x, m_pMyPlane1->GetPoint().y));
		switch (m_nGameType)
		{
		case commonGame:
			m_pEnd->SetScore(m_pCounter->GetNum(), 'a');
			break;
		case bossGame:
			m_pEnd->SetScore(m_pCounter->GetNum(), 'b');
			break;
		default:
			break;
		}
		m_nProcess = end;
	}
}

// 生产敌机
void CPlaneWarView::MakeEnemy()
{
	// TODO: 在此处添加实现代码.

	//随着关卡的难度提高，敌机等级提高，产生速度更快，数量更多

	switch (m_nGameType)
	{
	case bossGame:
		if (m_nWait < 0 && m_nEnemy < m_nMaxEnemy + m_nLevel * 4) {
			m_nWait = rand() % (40 - m_nLevel * 9) + 8;
			m_objList[enemy].AddTail(m_sampleFactory(rand() % (m_nLevel + 1)));
			m_nEnemy++;
		}
		m_nWait--;
		break;
	case commonGame:
		if (m_nWait < 0 && m_nEnemy < m_nMaxEnemy + m_nCommonLevel * 4) {
			if (m_nCommonLevel < 5)
				m_nWait = rand() % (50 - m_nCommonLevel * 10) + 10;
			else {
				m_nWait = 10;
			}
			if (m_nCommonLevel >= 5) {
				m_objList[enemy].AddTail(m_sampleFactory(rand() % 5));
			}
			else {
				m_objList[enemy].AddTail(m_sampleFactory(rand() % (m_nCommonLevel + 1)));
			}
			m_nEnemy++;
		}
		m_nWait--;
	default:
		break;
	}
}

//战机炸掉敌机
void CPlaneWarView::MyPlaneShotEnemy()
{
	POSITION pos1, pos2, pos3, pos4;
	CRect rect1, rect2, tmp;
	//子弹炸掉敌机
	for (pos1 = m_objList[enemy].GetHeadPosition(); (pos2 = pos1) != NULL; ) {
		CGameEnemy * pe = (CGameEnemy *)m_objList[enemy].GetNext(pos1);
		rect1 = pe->GetRect();
		for (pos3 = m_objList[bomb].GetHeadPosition(); (pos4 = pos3) != NULL; ) {
			CGameBomb * pb = (CGameBomb *)m_objList[bomb].GetNext(pos3);
			rect2 = pb->GetRect();
			if (tmp.IntersectRect(&rect1, &rect2)) {
				pe->MinusHP(pb->GetDamage()); //敌机减血
				m_objList[bomb].RemoveAt(pos4);
				delete pb;
				if (pe->GetHP() <= 0) {
					m_nEnemy--; //敌机的数量减少一
					m_pCounter->PlusNum(pe->GetEnemyID() + 1);   //计分系统
					m_objList[explosion].AddTail(new CExplosion(pe->GetPoint().x, pe->GetPoint().y));
					m_objList[enemy].RemoveAt(pos2);
					delete pe;
					break;
				}
			}
		}
	}
	//大招炸掉敌机
	for (pos1 = m_objList[wingman].GetHeadPosition(); pos1 != NULL;) {
		CGameBomb * pw = (CGameBomb *)m_objList[wingman].GetNext(pos1);
		rect1 = pw->GetRect();
		for (pos3 = m_objList[enemy].GetHeadPosition(); (pos4 = pos3) != NULL;) {
			CGameEnemy * pe = (CGameEnemy *)m_objList[enemy].GetNext(pos3);
			rect2 = pe->GetRect();
			if (tmp.IntersectRect(rect1, rect2)) {
				m_nEnemy--;
				m_pCounter->PlusNum(pe->GetEnemyID() + 1);
				m_objList[explosion].AddTail(new CExplosion(pe->GetPoint().x, pe->GetPoint().y));
				m_objList[enemy].RemoveAt(pos4);
				delete pe;
			}
		}
	}
	//大招炸掉子弹
	for (pos1 = m_objList[wingman].GetHeadPosition(); pos1 != NULL;) {
		CGameBomb * pw = (CGameBomb *)m_objList[wingman].GetNext(pos1);
		rect1 = pw->GetRect();
		for (pos3 = m_objList[enBomb].GetHeadPosition(); (pos4 = pos3) != NULL;) {
			CGameEnemy * pe = (CGameEnemy *)m_objList[enBomb].GetNext(pos3);
			rect2 = pe->GetRect();
			if (tmp.IntersectRect(rect1, rect2)) {
				m_objList[enBomb].RemoveAt(pos4);
				delete pe;
			}
		}
	}
}

//战机Q技能炸掉敌机
void CPlaneWarView::QShotEnemy()
{
	POSITION pos1, pos2, pos3, pos4;
	CRect rect1, rect2, tmp;
	for (pos1 = m_objList[enemy].GetHeadPosition(); (pos2 = pos1) != NULL; ) {
		CGameEnemy * pe = (CGameEnemy *)m_objList[enemy].GetNext(pos1);
		rect1 = pe->GetRect();
		for (pos3 = m_objList[bullet].GetHeadPosition(); (pos4 = pos3) != NULL; ) {
			CGameObject * pq = (CGameObject *)m_objList[bullet].GetNext(pos3);
			rect2 = pq->GetRect();
			if (tmp.IntersectRect(&rect1, &rect2)) {
				m_objList[bullet].RemoveAt(pos4);
				delete pq;
				m_nEnemy--;						//敌机的数量减少一
				m_pCounter->PlusNum(1);			//计分系统, 只加一分
				m_objList[explosion].AddTail(new CExplosion(pe->GetPoint().x, pe->GetPoint().y));
				m_objList[enemy].RemoveAt(pos2);
				delete pe;
				break;
			}
		}
	}
}

//敌机战机碰撞检测
void CPlaneWarView::ImpactCheck()
{
	POSITION pos1, pos2;
	CRect rect1, rect2, tmp;
	rect1 = m_pMyPlane->GetRect();
	for (pos1 = m_objList[enemy].GetHeadPosition(); (pos2 = pos1) != NULL; ) {
		CGameEnemy * pe = (CGameEnemy *)m_objList[enemy].GetNext(pos1);
		rect2 = pe->GetRect();
		if (tmp.IntersectRect(&rect1, &rect2)) {
			m_pCounter->PlusNum(pe->GetEnemyID() + 1);//计分系统
			m_objList[explosion].AddTail(new CExplosion(pe->GetPoint().x, pe->GetPoint().y));
			if(!m_pMyPlane->WOn() && !m_bNoEnemy)  //战机没开W技能
				m_pMyPlane->MinusHp(pe->GetDamege());
			m_objList[enemy].RemoveAt(pos2);
			m_nEnemy--;
			delete pe;
		}
	}
	if (m_nNetID == server) {
		rect1 = m_pMyPlane1->GetRect();
		for (pos1 = m_objList[enemy].GetHeadPosition(); (pos2 = pos1) != NULL; ) {
			CGameEnemy * pe = (CGameEnemy *)m_objList[enemy].GetNext(pos1);
			rect2 = pe->GetRect();
			if (tmp.IntersectRect(&rect1, &rect2)) {
				m_pCounter->PlusNum(pe->GetEnemyID() + 1);//计分系统
				m_objList[explosion].AddTail(new CExplosion(pe->GetPoint().x, pe->GetPoint().y));
				if (!m_pMyPlane1->WOn() && !m_bNoEnemy)  //战机没开W技能
					m_pMyPlane1->MinusHp(pe->GetDamege());
				m_objList[enemy].RemoveAt(pos2);
				m_nEnemy--;
				delete pe;
			}
		}
	}
}

//吃道具
void CPlaneWarView::CatchProp()
{
	POSITION pos1, pos2;
	CRect rect1, rect2, rect3, tmp;
	rect1 = m_pMyPlane->GetRect();
	for (pos1 = m_objList[prop].GetHeadPosition(); (pos2 = pos1) != NULL; ) {
		CGameProp * pp = (CGameProp *)m_objList[prop].GetNext(pos1);
		rect2 = pp->GetRect();
		if (tmp.IntersectRect(&rect1, &rect2)) {
			if (pp->GetPropID() == 0) {
				m_pMyPlane->PlusHP(2);
				m_pText->SetText(_T("补充血量！"));
			}
			else if(pp->GetPropID() == 1){
					m_pText->SetText(_T("战机升级！"));
					m_pMyPlane->PlaneUpdate();
			}
			else if (pp->GetPropID() == 2) {
				m_pMyPlane->SetBomb();
				m_pText->SetText(_T("子弹升级！"));
			}
			m_pCounter->PlusNum(3); //吃一个道具加三分
			m_objList[prop].RemoveAt(pos2);
			delete pp;
		}
	}
	if (m_nNetID == server) {
		rect3 = m_pMyPlane1->GetRect();
		for (pos1 = m_objList[prop].GetHeadPosition(); (pos2 = pos1) != NULL; ) {
			CGameProp * pp = (CGameProp *)m_objList[prop].GetNext(pos1);
			rect2 = pp->GetRect();
			if (tmp.IntersectRect(&rect3, &rect2)) {
				if (pp->GetPropID() == 0) {
					m_pMyPlane1->PlusHP(2);
					m_pText->SetText(_T("补充血量！"));
				}
				else if (pp->GetPropID() == 1) {
					m_pText->SetText(_T("战机升级！"));
					m_pMyPlane1->PlaneUpdate();
				}
				else if (pp->GetPropID() == 2) {
					m_pMyPlane1->SetBomb();
					m_pText->SetText(_T("子弹升级！"));
				}
				m_pCounter->PlusNum(3); //吃一个道具加三分
				m_objList[prop].RemoveAt(pos2);
				delete pp;
			}
		}
	}
}

void CPlaneWarView::OnDestroy()
{
	CView::OnDestroy();
	StopGame();
	// TODO: 在此处添加消息处理程序代码
}

void CPlaneWarView::StopGame()
{
	delete m_pBack;
	delete m_pDC;
	delete m_pMemDC;
	delete m_pMemBitmap;
	delete m_pCounter;
	delete m_pMyPlane;
	delete m_pPause;
	delete m_pText;
	delete m_pBegin;
	delete m_pEnd;
	if (m_nNetID == server) {
		delete m_pMyPlane1;
	}
}

void CPlaneWarView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_nProcess == begin) {
		CRect rect = m_pBegin->GetRectBegin();
		if (point.x > rect.left && point.x < rect.right && point.y > rect.top && point.y < rect.bottom) {
			m_nProcess = game;
			m_nGameType = commonGame;
		}
		rect = m_pBegin->GetRectHelp();
		if (point.x > rect.left && point.x < rect.right && point.y > rect.top && point.y < rect.bottom) {
			m_nProcess = help;
		}
		rect = m_pBegin->GetRectRank();
		if (point.x > rect.left && point.x < rect.right && point.y > rect.top && point.y < rect.bottom) {
			m_pRank->GetScore(); //从文件中读取最新分数
			m_nProcess = rank;
		}
		rect = m_pBegin->GetRectBoss();
		if (point.x > rect.left && point.x < rect.right && point.y > rect.top && point.y < rect.bottom) {
			m_nProcess = game;
			m_nGameType = bossGame;
		}
	}
	else if (m_nProcess == help) {
		CRect rect = m_pBegin->GetRectCancel();
		if (point.x > rect.left && point.x < rect.right && point.y > rect.top && point.y < rect.bottom)
			m_nProcess = begin;
	}
	else if (m_nProcess == game) {
		CRect rect = m_pPause->GetRect();
		if (point.x > rect.left && point.x < rect.right && point.y > rect.top && point.y < rect.bottom) {
			m_pPause->PauseButton(m_bPause);
			if (m_bPause == TRUE) {
				//mciSendString(_T("pause bgm"), NULL, 0, NULL);
			}
			else {
				//mciSendString(_T("resume bgm"), NULL, 0, NULL);
			}
		}
		rect = m_pPause->GetRectRestart();
		if (point.x > rect.left && point.x < rect.right && point.y > rect.top && point.y < rect.bottom) {
			ReStart();
			m_nProcess = game;
			if (m_nGameType == commonGame) {
				m_nCommonLevel = 0;
			}
		}
		rect = m_pPause->GetRectCancel();
		if (point.x > rect.left && point.x < rect.right && point.y > rect.top && point.y < rect.bottom) {
			ReStart();
		}
	}
	else if (m_nProcess == end) {
		CRect rect = m_pEnd->GetRectRestart();
		if (point.x > rect.left && point.x < rect.right && point.y > rect.top && point.y < rect.bottom) {
			ReStart();
			m_nProcess = game;
		}
		rect = m_pEnd->GetRectCancel();
		if (point.x > rect.left && point.x < rect.right && point.y > rect.top && point.y < rect.bottom) {
			ReStart();
			m_nProcess = begin;
		}
	}
	else if (m_nProcess == rank) {
		CRect rect = m_pRank->GetRectCancel();
		if (point.x > rect.left && point.x < rect.right && point.y > rect.top && point.y < rect.bottom) {
			m_nProcess = begin;
		}
	}
	CView::OnLButtonDown(nFlags, point);
}

// 关卡升级
void CPlaneWarView::UpdateLevel()
{
	// TODO: 在此处添加实现代码.
	
	if (m_bBossHaveDaed) {
		m_bBossHaveDaed = FALSE;
		m_nLastCounter = m_pCounter->GetNum();
		if (m_nGameType == bossGame) {
			m_nLevel++;
			m_nBackLevel++;
			if (m_nBackLevel > 4) {
				m_nBackLevel = 4;
			}
			if (m_nLevel > 4) {
				m_nLevel = 4;
				m_pMyPlane->MinusHp(100); //迫使产生CNumber退出
			}
		}
		else if (m_nGameType == commonGame) {
			m_nCommonLevel++;
			int ans = m_nBackLevel;
			while (m_nBackLevel == ans) //使背景不重复
				m_nBackLevel = rand() % 5;
		}
	}

	//添加boss
	if (m_nGameType == bossGame) {
		POSITION pos = m_objList[boss].GetHeadPosition();
		if (pos != NULL) return;
		if (m_nLevel == 4 && m_pCounter->GetNum() - m_nLastCounter > 500) {
			m_objList[boss].AddTail(new CBoss4());
			return;
		}if (m_nLevel == 3 && m_pCounter->GetNum() - m_nLastCounter > 400) {
			m_objList[boss].AddTail(new CBoss3());
			return;
		}if (m_nLevel == 2 && m_pCounter->GetNum() - m_nLastCounter > 300) {
			m_objList[boss].AddTail(new CBoss2());
			return;
		}if (m_nLevel == 1 && m_pCounter->GetNum() - m_nLastCounter > 200) {
			m_objList[boss].AddTail(new CBoss1());
			return;
		}
		if (m_nLevel == 0 && m_pCounter->GetNum() - m_nLastCounter > 100) {
			m_objList[boss].AddTail(new CBoss0());
			return;
		}
	}
	else if (m_nGameType == commonGame) {
		POSITION pos = m_objList[boss].GetHeadPosition();
		if (pos != NULL) return;
		if (m_nCommonLevel == 1 && m_pCounter->GetNum() - m_nLastCounter > 200) {
			m_objList[boss].AddTail(new CBoss1());
			return;
		}
		if (m_nCommonLevel == 0 && m_pCounter->GetNum() - m_nLastCounter > 100) {
			m_objList[boss].AddTail(new CBoss0());
			return;
		}
		if (m_nCommonLevel >= 2 && m_pCounter->GetNum() - m_nLastCounter > m_nCommonLevel * 100 + 100) {
			switch (rand() % 5)
			{
			case 0: m_objList[boss].AddTail(new CBoss0()); return;
			case 1: m_objList[boss].AddTail(new CBoss1()); return;
			case 2: m_objList[boss].AddTail(new CBoss2()); return;
			case 3: m_objList[boss].AddTail(new CBoss3()); return;
			case 4: m_objList[boss].AddTail(new CBoss4()); return;
			default:
				break;
			}
		}
	}
}


// 添加敌机子弹
void CPlaneWarView::AddEnBomb()
{
	// TODO: 在此处添加实现代码.
	CPoint ans = m_pMyPlane->GetPoint();
	POSITION pos;
	for (pos = m_objList[enemy].GetHeadPosition(); pos != NULL; ) {
		CGameEnemy * pe = (CGameEnemy *)m_objList[enemy].GetNext(pos);
		if (pe->Fired()) {
			pe->AddBomb(m_objList[enBomb], ans);
		}
	}
}


// 敌机子弹打战机
void CPlaneWarView::EnBombShootPlane()
{
	// TODO: 在此处添加实现代码.
	POSITION pos1, pos2;
	CRect rect1, rect2, tmp;
	rect1 = m_pMyPlane->GetRect();
	for (pos1 = m_objList[enBomb].GetHeadPosition(); (pos2 = pos1) != NULL; ) {
		CGameBomb * pb = (CGameBomb *)m_objList[enBomb].GetNext(pos1);
		rect2 = pb->GetRect();
		if (tmp.IntersectRect(&rect1, &rect2)) {
			if(!m_pMyPlane->WOn() && !m_bNoEnemy)  //战机没开W技能
				m_pMyPlane->MinusHp(2);
			m_objList[enBomb].RemoveAt(pos2);
			delete pb;
		}
	}

	if (m_nNetID == server) {
		rect1 = m_pMyPlane1->GetRect();
		for (pos1 = m_objList[enBomb].GetHeadPosition(); (pos2 = pos1) != NULL; ) {
			CGameBomb * pb = (CGameBomb *)m_objList[enBomb].GetNext(pos1);
			rect2 = pb->GetRect();
			if (tmp.IntersectRect(&rect1, &rect2)) {
				if (!m_pMyPlane1->WOn() && !m_bNoEnemy)  //战机没开W技能
					m_pMyPlane1->MinusHp(2);
				m_objList[enBomb].RemoveAt(pos2);
				delete pb;
			}
		}
	}
}


// 重新启动游戏
void CPlaneWarView::ReStart()
{
	for (int i = 0; i < 11; i++) {
		POSITION pos, pos1;
		for (pos = m_objList[i].GetHeadPosition(); (pos1 = pos) != NULL; ) {
			CGameObject * pa = (CGameObject *)m_objList[i].GetNext(pos);
			m_objList[i].RemoveAt(pos1);
			delete pa;
		}
	}
	StopGame();
	InitGame();
}


// 添加boss子弹
void CPlaneWarView::AddBossBomb()
{
	// TODO: 在此处添加实现代码.
	POSITION pos = m_objList[boss].GetHeadPosition();
	if (pos == NULL) return;
	CGameEnemy * pe = (CGameEnemy *)m_objList[boss].GetAt(pos);
	CPoint point = m_pMyPlane->GetPoint();
	pe->AddBomb(m_objList[bossBomb], point);
}

//连接服务端
BOOL CPlaneWarView::GetConnect()
{
	//不加在create是会出错
#define _afxSockThreadState AfxGetModuleThreadState() 
#define _AFX_SOCK_THREAD_STATE AFX_MODULE_THREAD_STATE 

	_AFX_SOCK_THREAD_STATE* pState = _afxSockThreadState;
	if (pState->m_pmapSocketHandle == NULL)
		pState->m_pmapSocketHandle = new CMapPtrToPtr;
	if (pState->m_pmapDeadSockets == NULL)
		pState->m_pmapDeadSockets = new CMapPtrToPtr;
	if (pState->m_plistSocketNotifications == NULL)
		pState->m_plistSocketNotifications = new CPtrList;

	std::fstream file;
	file.open("IP.txt", std::ios::in);
	if (file) {
		std::string ip;
		CString IP;
		int port;
		file >> ip >> port;
		IP = ip.c_str();
		m_user.Create();
		if (ip != "" && m_user.Connect(IP, port)) {
			AfxMessageBox(_T("已创建连接"));
			return TRUE;
		}
		else {
			AfxMessageBox(_T("创建失败"));
		}
	}
	return FALSE;
}

//服务端监听
BOOL CPlaneWarView::GetListen()
{
	//不加在create是会出错
#define _afxSockThreadState AfxGetModuleThreadState() 
#define _AFX_SOCK_THREAD_STATE AFX_MODULE_THREAD_STATE 

	_AFX_SOCK_THREAD_STATE* pState = _afxSockThreadState;
	if (pState->m_pmapSocketHandle == NULL)
		pState->m_pmapSocketHandle = new CMapPtrToPtr;
	if (pState->m_pmapDeadSockets == NULL)
		pState->m_pmapDeadSockets = new CMapPtrToPtr;
	if (pState->m_plistSocketNotifications == NULL)
		pState->m_plistSocketNotifications = new CPtrList;

	std::fstream file;
	file.open("server.txt", std::ios::in);
	if (file) {
		std::string s;
		int port = 0;
		file >> s >> port;
		if (s == "TRUE" && port != 0) {
			m_server.ShutDown();
			m_server.Close();
			if (m_server.Create(port)) {
				if (m_server.Listen()) {
					bStarted = true;
					AfxMessageBox(_T("服务器开启"));
					return TRUE;
				}
				else {
					int error = m_server.GetLastError();
					m_server.Close();
					return FALSE;
				}
			}
			else {
				int ans = m_server.GetLastError();
				AfxMessageBox(_T("端口已被占用"));
				return FALSE;
			}
		}
	}
	return FALSE;
}

void CPlaneWarView::OnSend(CString & ans)
{
	//AfxMessageBox(ans);
	
	m_user.Send(ans.GetBuffer(0), ans.GetLength() * 2);
}
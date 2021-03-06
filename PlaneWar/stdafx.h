
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展
#include <afxsock.h>        




#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持



//游戏窗口的高度和宽度
#define GAME_WIDTH 600
#define GAME_HEIGHT 900
#define INF  0x3f3f3f3f

#include <fstream>
#include <string>

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
#include "Boss1.h"
#include "Boss2.h"
#include "Boss3.h"
#include "Boss4.h"
#include "Bomb1.h"
#include "EnBomb.h"
#include "EnBomb0.h"
#include "EnBomb1.h"
#include "Wingman.h"


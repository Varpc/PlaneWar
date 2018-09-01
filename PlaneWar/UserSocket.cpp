#include "stdafx.h"
#include "UserSocket.h"


CUserSocket::CUserSocket()
{
}


CUserSocket::~CUserSocket()
{
}


void CUserSocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	CSocket::OnReceive(nErrorCode);
}

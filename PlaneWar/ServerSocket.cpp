#include "stdafx.h"
#include "ServerSocket.h"


CServerSocket::CServerSocket()
{
	peersocket = NULL;
}


CServerSocket::~CServerSocket()
{
}


void CServerSocket::OnAccept(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	peersocket = new CPeerSocket();
	BOOL ok = Accept(*peersocket); //接受客户连接
	if (!ok) { 
		delete peersocket;
		peersocket = NULL;
	}
	CSocket::OnAccept(nErrorCode);
}

std::string CServerSocket::GetMove()
{
	if (peersocket == NULL) return "";
	return peersocket->GetMove();
}
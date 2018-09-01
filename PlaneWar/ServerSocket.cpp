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
	// TODO: �ڴ����ר�ô����/����û���

	peersocket = new CPeerSocket();
	BOOL ok = Accept(*peersocket); //���ܿͻ�����
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
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
	// TODO: �ڴ����ר�ô����/����û���

	CSocket::OnReceive(nErrorCode);
}

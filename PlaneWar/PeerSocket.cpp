#include "stdafx.h"
#include "PeerSocket.h"


CPeerSocket::CPeerSocket()
{
}


CPeerSocket::~CPeerSocket()
{
}


void CPeerSocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	TCHAR buf[1025]; //缓冲区
	int len = 0;
	len = Receive(buf, 1024);
	buf[len / 2] = '\0'; //缓冲区末尾置零
	m_sCmd.clear();
	for (int i = 0; buf[i] != 0; i++) {
		m_sCmd.push_back(buf[i]);
	}
	CSocket::OnReceive(nErrorCode);
}

std::string CPeerSocket::GetMove()
{
	//std::string ans = m_sCmd;
	//m_sCmd.clear();
	return m_sCmd;
}
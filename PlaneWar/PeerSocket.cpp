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
	// TODO: �ڴ����ר�ô����/����û���
	TCHAR buf[1025]; //������
	int len = 0;
	len = Receive(buf, 1024);
	buf[len / 2] = '\0'; //������ĩβ����
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
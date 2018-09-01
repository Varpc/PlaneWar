#pragma once
#include <string>
class CPeerSocket: public CSocket
{
public:
	CPeerSocket();
	~CPeerSocket();
	virtual void OnReceive(int nErrorCode);
public:
	std::string GetMove();
	std::string m_sCmd;
};


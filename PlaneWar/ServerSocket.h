#pragma once
#include "PeerSocket.h"
#include <string>
class CServerSocket : public CSocket
{
public:
	CServerSocket();
	~CServerSocket();
	virtual void OnAccept(int nErrorCode);
public:
	std::string GetMove();
private:
	CPeerSocket * peersocket;
};


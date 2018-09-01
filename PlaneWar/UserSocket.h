#pragma once
class CUserSocket: public CSocket
{
public:
	CUserSocket();
	~CUserSocket();
	virtual void OnReceive(int nErrorCode);
};


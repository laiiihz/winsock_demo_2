
#pragma once

// CMySocket 命令目标

class CtalkingServerDlg;
class CMySocket : public CAsyncSocket
{
public:
	CMySocket();
	virtual ~CMySocket();
	
	void SetParent(CtalkingServerDlg* pDlg);
public:
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
private:
	CtalkingServerDlg* m_pDlg;
	
};



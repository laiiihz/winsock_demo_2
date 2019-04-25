
#pragma once

// CMySocket 命令目标
class CtalkingClientDlg;
class CMySocket : public CAsyncSocket
{
public:
	CMySocket();
	virtual ~CMySocket();
	virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	void SetParent(CtalkingClientDlg* pDlg);

	
private:
	CtalkingClientDlg* m_pDlg;
	
};



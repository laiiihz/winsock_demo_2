// CMySocket.cpp: 实现文件
//

#include "pch.h"
#include "talkingServer.h"
#include "CMySocket.h"
#include "talkingServerDlg.h"


// CMySocket

CMySocket::CMySocket()
{
	m_pDlg = NULL;
}

CMySocket::~CMySocket()
{
	m_pDlg = NULL;
}


// CMySocket 成员函数


void CMySocket::OnAccept(int nErrorCode)
{
	if (nErrorCode == 0)m_pDlg->OnAccept();
}


void CMySocket::OnClose(int nErrorCode)
{
	if (nErrorCode == 0)m_pDlg->OnClose();
}


void CMySocket::OnReceive(int nErrorCode)
{
	if (nErrorCode == 0)m_pDlg->OnReceive();
}

void CMySocket::SetParent(CtalkingServerDlg* pDlg)
{
	m_pDlg = pDlg;
}

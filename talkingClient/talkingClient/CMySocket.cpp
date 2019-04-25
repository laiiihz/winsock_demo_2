// CMySocket.cpp: 实现文件
//

#include "pch.h"
#include "talkingClient.h"
#include "talkingClientDlg.h"
#include "CMySocket.h"


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


void CMySocket::OnClose(int nErrorCode)
{
	if (nErrorCode == 0)m_pDlg->OnClose();
}


void CMySocket::OnConnect(int nErrorCode)
{
	if (nErrorCode == 0)m_pDlg->OnConnect();
}


void CMySocket::OnReceive(int nErrorCode)
{
	if (nErrorCode == 0)m_pDlg->OnReceive();
}


void CMySocket::SetParent(CtalkingClientDlg* pDlg)
{
	m_pDlg = pDlg;
}

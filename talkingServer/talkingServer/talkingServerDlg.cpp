
// talkingServerDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "talkingServer.h"
#include "talkingServerDlg.h"
#include "afxdialogex.h"
#include "CMySocket.h"
#include "iostream"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CtalkingServerDlg 对话框



CtalkingServerDlg::CtalkingServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TALKINGSERVER_DIALOG, pParent)
	, m_strServName(_T(""))
	, m_nServPort(0)
	, m_strMsg(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}



BEGIN_MESSAGE_MAP(CtalkingServerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LISTEN, &CtalkingServerDlg::OnButtonListen)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CtalkingServerDlg::OnButtonClose)
	ON_BN_CLICKED(IDOK, &CtalkingServerDlg::OnSendMsg)
END_MESSAGE_MAP()


// CtalkingServerDlg 消息处理程序

BOOL CtalkingServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_strServName = "localhost";
	m_nServPort = 1000;
	UpdateData(FALSE);
	m_sListenSocket.SetParent(this);
	m_sConnectSocket.SetParent(this);
	GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_MSG)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_MSG)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CtalkingServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CtalkingServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CtalkingServerDlg::OnButtonListen()
{
	UpdateData(TRUE);
	GetDlgItem(IDC_BUTTON_LISTEN)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SERVNAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SERVPORT)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_SERVNAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_SERVPORT)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_STATIC_MSG)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_MSG)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(TRUE);
	m_sListenSocket.Create(m_nServPort);
	m_sListenSocket.Listen();
}


void CtalkingServerDlg::OnButtonClose()
{
	OnClose();
}


void CtalkingServerDlg::OnSendMsg()
{
	int nLen;
	int nSend;
	UpdateData(TRUE);
	if (!m_strMsg.IsEmpty())
	{
		nLen = m_strMsg.GetLength();
		nSend = m_sConnectSocket.Send(CString(m_strMsg), nLen);
		if (nSend != SOCKET_ERROR)
		{
			m_listSend.AddString(m_strMsg);
			UpdateData(FALSE);
		}
		else
		{
			AfxMessageBox(_T("message send fail"), MB_OK | MB_ICONSTOP);
		}
		m_strMsg.Empty();
		UpdateData(FALSE);
	}
}

void CtalkingServerDlg::OnClose()
{
	m_listReceived.AddString("server get OnClose message");
	m_sConnectSocket.Close();
	GetDlgItem(IDC_EDIT_MSG)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_MSG)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(FALSE);
	
	while (m_listSend.GetCount() != 0)m_listSend.DeleteString(0);
	while (m_listReceived.GetCount() != 0)m_listReceived.DeleteString(0);

	GetDlgItem(IDC_BUTTON_LISTEN)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_SERVNAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_SERVPORT)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC_SERVNAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC_SERVPORT)->EnableWindow(TRUE);


}

void CtalkingServerDlg::OnAccept()
{
	m_listReceived.AddString("server receive OnAccept message");
	m_sListenSocket.Accept(m_sConnectSocket);

	GetDlgItem(IDC_EDIT_MSG)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC_MSG)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(TRUE);

}

void CtalkingServerDlg::OnReceive()
{
	char* pBuf = new char[1025];
	int nBufSize = 1024;
	int nReceived;
	CString strReceived;
	m_listReceived.AddString("server get OnReceive message");
	nReceived = m_sConnectSocket.Receive(pBuf, nBufSize);
	if (nReceived != SOCKET_ERROR) {
		pBuf[nReceived] = NULL;
		strReceived = pBuf;
		std::cout << strReceived <<"@@@@@@@@@@@@@@@@"<< std::endl;
		m_listReceived.AddString(strReceived);
		UpdateData(FALSE);
	}else
		{
			AfxMessageBox("message receive fail", MB_OK | MB_ICONSTOP);
		}
}

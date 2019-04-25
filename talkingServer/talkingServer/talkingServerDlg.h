
// talkingServerDlg.h: 头文件
//

#pragma once

#include "CMySocket.h"
// CtalkingServerDlg 对话框
class CtalkingServerDlg : public CDialogEx
{
// 构造
public:
	CtalkingServerDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TALKINGSERVER_DIALOG };
#endif

	protected:
		virtual void DoDataExchange(CDataExchange* pDX) {
			CDialogEx::DoDataExchange(pDX);
			DDX_Control(pDX, IDC_BUTTON_LISTEN, m_btnListen);
			DDX_Text(pDX, IDC_EDIT_SERVNAME, m_strServName);
			DDX_Text(pDX, IDC_EDIT_SERVPORT, m_nServPort);
			DDX_Text(pDX, IDC_EDIT_MSG, m_strMsg);
			DDX_Control(pDX, IDC_LIST_RECEIVED, m_listReceived);
			DDX_Control(pDX, IDC_LIST_SEND, m_listSend);
		}	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CMySocket m_sListenSocket;
	CMySocket m_sConnectSocket;
	CButton m_btnListen;
	CString m_strServName;
	int m_nServPort;
	CString m_strMsg;
	CListBox m_listReceived;
	CListBox m_listSend;
	afx_msg void OnButtonListen();
	afx_msg void OnButtonClose();
	afx_msg void OnSendMsg();
	
	void OnClose();
	void OnAccept();
	void OnReceive();
};

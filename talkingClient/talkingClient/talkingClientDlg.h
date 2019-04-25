#include "CMySocket.h"
// talkingClientDlg.h: 头文件
//

#pragma once


// CtalkingClientDlg 对话框
class CtalkingClientDlg : public CDialogEx
{
// 构造
public:
	CtalkingClientDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TALKINGCLIENT_DIALOG };
#endif

	protected:
		virtual void DoDataExchange(CDataExchange* pDX)
		{
			CDialogEx::DoDataExchange(pDX);
			DDX_Control(pDX, IDC_BUTTON_CONNECT, m_btnConnect);
			DDX_Text(pDX, IDC_EDIT_SERVPORT, m_nServPort);
			DDX_Text(pDX, IDC_EDIT_SERVNAME, m_strServName);
			DDX_Text(pDX, IDC_EDIT_MSG, m_strMSG);
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
	afx_msg void OnButtonClose();
	afx_msg void OnButtonConnect();
	afx_msg void OnSendMsg();
	DECLARE_MESSAGE_MAP()


public:
	CMySocket m_sConnectSocket;
	CButton m_btnConnect;
	int m_nServPort;
	CString m_strServName;
	CString m_strMSG;
	CListBox m_listReceived;
	CListBox m_listSend;
	

	void OnClose();
	void OnConnect();
	void OnReceive();

};

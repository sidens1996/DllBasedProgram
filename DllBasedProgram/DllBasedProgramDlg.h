
// DllBasedProgramDlg.h : 头文件
//

#pragma once
// CDllBasedProgramDlg 对话框
class CDllBasedProgramDlg : public CDialogEx
{
// 构造
public:
	CDllBasedProgramDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DLLBASEDPROGRAM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	//自定义消息映射函数
	afx_msg BOOL OnToolTipText(UINT id, NMHDR *pNMHDR, LRESULT *pResult);
	
	DECLARE_MESSAGE_MAP()

	//自定义
public:
	CToolBar m_ToolBar;
	CImageList m_ImageList;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int scanDLL();
	int numDLL;
	CString getText(int i);
	CString textInfo;
	CArray<int> orderButton;
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
};

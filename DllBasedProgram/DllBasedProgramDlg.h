
// DllBasedProgramDlg.h : ͷ�ļ�
//

#pragma once
// CDllBasedProgramDlg �Ի���
class CDllBasedProgramDlg : public CDialogEx
{
// ����
public:
	CDllBasedProgramDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DLLBASEDPROGRAM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	//�Զ�����Ϣӳ�亯��
	afx_msg BOOL OnToolTipText(UINT id, NMHDR *pNMHDR, LRESULT *pResult);
	
	DECLARE_MESSAGE_MAP()

	//�Զ���
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

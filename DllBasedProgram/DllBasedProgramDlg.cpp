
// DllBasedProgramDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DllBasedProgram.h"
#include "DllBasedProgramDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDllBasedProgramDlg �Ի���



CDllBasedProgramDlg::CDllBasedProgramDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDllBasedProgramDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDllBasedProgramDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDllBasedProgramDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	//�Զ�����Ϣ
	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipText)
	ON_COMMAND(ID_BUTTON1, &CDllBasedProgramDlg::OnButton1)
	ON_COMMAND(ID_BUTTON2, &CDllBasedProgramDlg::OnButton2)
	ON_COMMAND(ID_BUTTON3, &CDllBasedProgramDlg::OnButton3)
	ON_COMMAND(ID_BUTTON4, &CDllBasedProgramDlg::OnButton4)
END_MESSAGE_MAP()


// CDllBasedProgramDlg ��Ϣ�������

BOOL CDllBasedProgramDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	//����ͼ���б�
	m_ImageList.Create(32, 32, ILC_COLOR32 | ILC_MASK, 7, 1);
	m_ImageList.SetBkColor(RGB(255, 255, 255));//���ñ�����ɫ
	m_ToolBar.Create(this, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_TOOLTIPS | TBSTYLE_WRAPABLE, AFX_IDW_TOOLBAR);
	//CBRS_TOOLTIPS��ʾ����������ʾ��ʾ����
	//TBSTYLE_WRAPABLE��ʾ��ť�����Զ�����
	numDLL = scanDLL();
	//��ͼ���б������ͼ��
	for (int i = 0; i < numDLL; i++)
		m_ImageList.Add(AfxGetApp()->LoadIcon(128 + orderButton[i]));
	UINT array[11];
	for (int i = 0; i < numDLL; i++)
	{
		array[i] = i + 1001;
	}
	m_ToolBar.SetButtons(array, numDLL);//ͼ������
	for (int i = 0; i < numDLL; i++)
	{
		m_ToolBar.SetButtonText(i, getText(orderButton[i]));
	}
	//m_ToolBar.SetButtonInfo(0, ID_BUTTON1, TBSTYLE_BUTTON, 0);
	//����ͼ���б�
	m_ToolBar.GetToolBarCtrl().SetImageList(&m_ImageList);
	m_ToolBar.SetSizes(CSize(50, 50), CSize(30, 30)); //���ð�ť��ͼ��Ĵ�С
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CDllBasedProgramDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDllBasedProgramDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CDllBasedProgramDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ANSI To UNCODEת��
CString AnsiToUnicode(char * szAnsi, int len)
{
	CString str;
	// ansi to unicode
	//Ԥת�����õ�����ռ�Ĵ�С
	int wcsLen;
	if (len>0)
		wcsLen = len;
	else
		wcsLen = ::MultiByteToWideChar(CP_ACP, NULL, szAnsi, strlen(szAnsi), NULL, 0);
	//����ռ�Ҫ��'\0'�����ռ䣬MultiByteToWideChar�����'\0'�ռ�
	wchar_t* wszString = new wchar_t[wcsLen + 1];
	//ת��
	::MultiByteToWideChar(CP_ACP, NULL, szAnsi, strlen(szAnsi), wszString, wcsLen);
	//������'\0'
	wszString[wcsLen] = '\0';// UNICODE�ִ�
	str = wszString;
	delete wszString;
	return str;
}

//�Զ��庯��
//��ʾ��ʾ����
BOOL CDllBasedProgramDlg::OnToolTipText(UINT id, NMHDR *pNMHDR, LRESULT *pResult)
{
	TOOLTIPTEXT *pTTT = (TOOLTIPTEXT *)pNMHDR;
	//CString str;
	UINT nID = pNMHDR->idFrom; //��ȡ��������ťID
	USES_CONVERSION;
	if (nID)
	{
		nID = m_ToolBar.CommandToIndex(nID); //����ID��ȡ��ť����
		if (nID != -1 && nID < numDLL)
		{
			textInfo = getText(orderButton[nID]);
			//��ȡ�������ı�	
			pTTT->lpszText = (LPWSTR)(LPCTSTR)textInfo;
			pTTT->hinst = AfxGetResourceHandle();
			return TRUE;
		}
	}
	return FALSE;
}


//�õ�DLL�ӿڵ���ʾ����
CString CDllBasedProgramDlg::getText(int i)
{
	CString filename, str;
	LPWSTR result;
	int count = 0;
	filename.Format(L"DLL%d.dll", i);
	HMODULE hDll = LoadLibrary(filename);
	if (hDll != NULL)
	{
		typedef char *(*stringID)();
		// ��ȡ������ַ
		stringID id = (stringID)GetProcAddress(hDll, "stringID");
		if (id != NULL)
		{
			str = AnsiToUnicode(id(), 3);
		}
		FreeLibrary(hDll); //�ͷ� DLL
		return str;
	}
}

int CDllBasedProgramDlg::scanDLL()
{
	CString filename;
	int count = 0;
	for (int i = 1; i < 100; i++)
	{
		filename.Format(L"DLL%d.dll",i);
		HMODULE hDll = LoadLibrary(filename);
		if (hDll != NULL)
		{
			count++;
			orderButton.Add(i);
		}
			
	}
	return count;
}

void CDllBasedProgramDlg::OnButton1()
{
	// TODO:  �ڴ���������������
	textInfo = getText(orderButton[0]);
	MessageBox((LPCTSTR)textInfo);
}


void CDllBasedProgramDlg::OnButton2()
{
	// TODO:  �ڴ���������������
	textInfo = getText(orderButton[1]);
	MessageBox((LPCTSTR)textInfo);
}


void CDllBasedProgramDlg::OnButton3()
{
	// TODO:  �ڴ���������������
	textInfo = getText(orderButton[2]);
	MessageBox((LPCTSTR)textInfo);
}


void CDllBasedProgramDlg::OnButton4()
{
	// TODO:  �ڴ���������������
	textInfo = getText(orderButton[3]);
	MessageBox((LPCTSTR)textInfo);
}

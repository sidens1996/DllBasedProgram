
// DllBasedProgramDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DllBasedProgram.h"
#include "DllBasedProgramDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CDllBasedProgramDlg 对话框



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

	//自定义消息
	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipText)
	ON_COMMAND(ID_BUTTON1, &CDllBasedProgramDlg::OnButton1)
	ON_COMMAND(ID_BUTTON2, &CDllBasedProgramDlg::OnButton2)
	ON_COMMAND(ID_BUTTON3, &CDllBasedProgramDlg::OnButton3)
	ON_COMMAND(ID_BUTTON4, &CDllBasedProgramDlg::OnButton4)
END_MESSAGE_MAP()


// CDllBasedProgramDlg 消息处理程序

BOOL CDllBasedProgramDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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
	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	//创建图像列表
	m_ImageList.Create(32, 32, ILC_COLOR32 | ILC_MASK, 7, 1);
	m_ImageList.SetBkColor(RGB(255, 255, 255));//设置背景颜色
	m_ToolBar.Create(this, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_TOOLTIPS | TBSTYLE_WRAPABLE, AFX_IDW_TOOLBAR);
	//CBRS_TOOLTIPS表示可以悬浮显示提示文字
	//TBSTYLE_WRAPABLE表示按钮可以自动换行
	numDLL = scanDLL();
	//向图像列表中添加图标
	for (int i = 0; i < numDLL; i++)
		m_ImageList.Add(AfxGetApp()->LoadIcon(128 + orderButton[i]));
	UINT array[11];
	for (int i = 0; i < numDLL; i++)
	{
		array[i] = i + 1001;
	}
	m_ToolBar.SetButtons(array, numDLL);//图标数量
	for (int i = 0; i < numDLL; i++)
	{
		m_ToolBar.SetButtonText(i, getText(orderButton[i]));
	}
	//m_ToolBar.SetButtonInfo(0, ID_BUTTON1, TBSTYLE_BUTTON, 0);
	//关联图像列表
	m_ToolBar.GetToolBarCtrl().SetImageList(&m_ImageList);
	m_ToolBar.SetSizes(CSize(50, 50), CSize(30, 30)); //设置按钮和图标的大小
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDllBasedProgramDlg::OnPaint()
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
HCURSOR CDllBasedProgramDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ANSI To UNCODE转换
CString AnsiToUnicode(char * szAnsi, int len)
{
	CString str;
	// ansi to unicode
	//预转换，得到所需空间的大小
	int wcsLen;
	if (len>0)
		wcsLen = len;
	else
		wcsLen = ::MultiByteToWideChar(CP_ACP, NULL, szAnsi, strlen(szAnsi), NULL, 0);
	//分配空间要给'\0'留个空间，MultiByteToWideChar不会给'\0'空间
	wchar_t* wszString = new wchar_t[wcsLen + 1];
	//转换
	::MultiByteToWideChar(CP_ACP, NULL, szAnsi, strlen(szAnsi), wszString, wcsLen);
	//最后加上'\0'
	wszString[wcsLen] = '\0';// UNICODE字串
	str = wszString;
	delete wszString;
	return str;
}

//自定义函数
//显示提示文字
BOOL CDllBasedProgramDlg::OnToolTipText(UINT id, NMHDR *pNMHDR, LRESULT *pResult)
{
	TOOLTIPTEXT *pTTT = (TOOLTIPTEXT *)pNMHDR;
	//CString str;
	UINT nID = pNMHDR->idFrom; //获取工具栏按钮ID
	USES_CONVERSION;
	if (nID)
	{
		nID = m_ToolBar.CommandToIndex(nID); //根据ID获取按钮索引
		if (nID != -1 && nID < numDLL)
		{
			textInfo = getText(orderButton[nID]);
			//获取工具栏文本	
			pTTT->lpszText = (LPWSTR)(LPCTSTR)textInfo;
			pTTT->hinst = AfxGetResourceHandle();
			return TRUE;
		}
	}
	return FALSE;
}


//得到DLL接口的提示文字
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
		// 获取函数地址
		stringID id = (stringID)GetProcAddress(hDll, "stringID");
		if (id != NULL)
		{
			str = AnsiToUnicode(id(), 3);
		}
		FreeLibrary(hDll); //释放 DLL
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
	// TODO:  在此添加命令处理程序代码
	textInfo = getText(orderButton[0]);
	MessageBox((LPCTSTR)textInfo);
}


void CDllBasedProgramDlg::OnButton2()
{
	// TODO:  在此添加命令处理程序代码
	textInfo = getText(orderButton[1]);
	MessageBox((LPCTSTR)textInfo);
}


void CDllBasedProgramDlg::OnButton3()
{
	// TODO:  在此添加命令处理程序代码
	textInfo = getText(orderButton[2]);
	MessageBox((LPCTSTR)textInfo);
}


void CDllBasedProgramDlg::OnButton4()
{
	// TODO:  在此添加命令处理程序代码
	textInfo = getText(orderButton[3]);
	MessageBox((LPCTSTR)textInfo);
}


// MfcRwDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MfcRw.h"
#include "MfcRwDlg.h"
#include "afxdialogex.h"
#include "DriverLoad.h"
#include"DriverRw.h"
#ifdef _DEBUG
#define new DEBUG_NEW                           
#endif

#define  DriverName "GameRw"
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMfcRwDlg 对话框



CMfcRwDlg::CMfcRwDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCRW_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMfcRwDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, ProcessID);
	DDX_Control(pDX, IDC_EDIT2, ProcessAddr);
	DDX_Control(pDX, IDC_EDIT3, ProcessBuffer);
}

BEGIN_MESSAGE_MAP(CMfcRwDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMfcRwDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMfcRwDlg::OnBnClickedButton2)
	ON_WM_TIMER()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CMfcRwDlg 消息处理程序

BOOL CMfcRwDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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
	SetWindowText(L"驱动读写测试 菜霸");

	addStatusBar2Dlg(); //设置状态栏
	SetTimer(TIMER0, 50, 0);

	if (!LoadDriver(DriverName, "DriverRw.sys"))
	{
		GetDlgItem(IDC_STATIC_SE)->SetWindowText(L"驱动加载失败!");
		return FALSE;
	}
	GetDlgItem(IDC_STATIC_SE)->SetWindowText(L"驱动加载成功!");

	if (InitDriver == FALSE)
	{
		GetDlgItem(IDC_STATIC_SE)->SetWindowText(L"驱动启动失败!");
		return FALSE;
	}
	GetDlgItem(IDC_STATIC_SE)->SetWindowText(L"驱动加载并启动成功!");

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMfcRwDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMfcRwDlg::OnPaint()
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
HCURSOR CMfcRwDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMfcRwDlg::OnBnClickedButton1()
{
	CString StrPid;

	ProcessID.GetWindowTextW(StrPid);

	if (StrPid.IsEmpty())
	{
		GetDlgItem(IDC_STATIC_SE)->SetWindowText(L"进程PID 为空 请输入进程ID!");
		return;
	}
	DWORD Pid = _wtoi(StrPid);

	CString StrAddr;

	ProcessAddr.GetWindowTextW(StrAddr);
	if (StrAddr.IsEmpty())
	{
		GetDlgItem(IDC_STATIC_SE)->SetWindowText(L"内存地址为空!");
		return;
	}
	QWORD Addr = _wcstoi64(StrAddr, NULL, 16); //转16进制

	if (!Addr)
	{
		GetDlgItem(IDC_STATIC_SE)->SetWindowText(L"读取地址错误!");
		return;
	}
	DWORD Ret = 0;
	InitDriver();

	ReadMemory(Pid, Addr, &Ret, sizeof(Ret));

	CString strRet;
	strRet.Format(L"%d", Ret);
	SetDlgItemText(IDC_EDIT4, strRet);

	// TODO: 在此添加控件通知处理程序代码
}


void CMfcRwDlg::OnBnClickedButton2()
{
	CString StrPid;
	ProcessID.GetWindowTextW(StrPid);

	if (StrPid.IsEmpty())
	{
		GetDlgItem(IDC_STATIC_SE)->SetWindowText(L"进程PID 为空 请输入进程ID!");
		return;
	}
	DWORD Pid = _wtoi(StrPid);

	CString strAddr;
	ProcessAddr.GetWindowTextW(strAddr);

	if (strAddr.IsEmpty())
	{
		GetDlgItem(IDC_STATIC_SE)->SetWindowText(L"内存地址为空!");
		return;
	}
	QWORD Addr = _wcstoi64(strAddr, NULL, 16);

	if (!Addr)
	{
		GetDlgItem(IDC_STATIC_SE)->SetWindowText(L"写入地址错误!");
		return;
	}
	CString StrBuffer;
	ProcessBuffer.GetWindowTextW(StrBuffer);
	if (StrBuffer.IsEmpty())
	{
		GetDlgItem(IDC_STATIC_SE)->SetWindowText(L"写入值错误!");
		return;
	}

	DWORD Buffer = _wtoi(StrBuffer);
	InitDriver();

	WriteMemory(Pid, &Buffer, Addr, sizeof(Buffer));

	// TODO: 在此添加控件通知处理程序代码
}

void CMfcRwDlg::addStatusBar2Dlg(void)
{
	static UINT BASED_CODE indicators[] = {
	IDS_STRING_TIME,
	IDS_STRING_AUTHOR
	};

	CRect rect;
	GetClientRect(rect);
	statusBar.Create(this);
	statusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));
	// 调整状态栏高度，30
	statusBar.MoveWindow(0, rect.bottom - 25, rect.right, 30);
	// 调整左状态栏宽度,200
	statusBar.SetPaneInfo(0, statusBar.GetDlgCtrlID(), SBPS_NORMAL, 173);
	// 调整右状态栏宽度,200
	statusBar.SetPaneInfo(1, statusBar.GetDlgCtrlID(), SBPS_NORMAL, 275);
	statusBar.SetPaneText(0, getCurrentTime());
	statusBar.SetPaneText(1, _T("说明:加载程序使用原版CE 即可破除图标方便测试"));

}

CString CMfcRwDlg::getCurrentTime(void)
{
	CTime timeNow;
	CString strTime;

	timeNow = CTime::GetCurrentTime();
	strTime = timeNow.Format("当前时间: %Y/%m/%d %H:%M:%S");
	return strTime;
}


void CMfcRwDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnTimer(nIDEvent);
	if (nIDEvent == TIMER0)	statusBar.SetPaneText(0, getCurrentTime());

}


void CMfcRwDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	DriverUnload();
	//关闭驱动
	UnloadDriver(DriverName);   //点击X 即可卸载驱动.......  因为在下面卸载不了  也不知道是不是时间问题.....

	if (MessageBox(L"确定要退出程序并卸载驱动吗？", L"退出提示", MB_ICONINFORMATION | MB_YESNO) == IDNO)
	{
		return; //注意无返回值
	}
	CDialogEx::OnClose();
}

// TrafficDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Traffic.h"
#include "TrafficDlg.h"
#include "NT.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL


// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrafficDlg dialog

CTrafficDlg::CTrafficDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTrafficDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTrafficDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CTrafficDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTrafficDlg)
	DDX_Control(pDX, IDC_GRAPH, m_graph);
	DDX_Control(pDX, IDC_BTN_TOP, m_bTop);
	DDX_Control(pDX, IDC_STATIC_STATUS, m_static_status);
	DDX_Control(pDX, IDC_LIST_DEVICES, m_list_devices);
	DDX_Control(pDX, IDC_EDIT_FILTER, m_edit_filter);
	DDX_Control(pDX, IDC_BTN_STOP, m_bStop);
	DDX_Control(pDX, IDC_BTN_START, m_bStart);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTrafficDlg, CDialog)
	//{{AFX_MSG_MAP(CTrafficDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_START, OnBtnStart)
	ON_BN_CLICKED(IDC_BTN_STOP, OnBtnStop)
	ON_BN_CLICKED(IDC_BTN_TOP, OnBtnTop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrafficDlg message handlers

BOOL CTrafficDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	//SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
	::GetAllDevices();


	UINT timerresolution	= 1000;	// Well, I think a refresh of the netstatus every second is enough
	UINT gridresolution		= 1000;	// To fake the Taskmanager....

	m_graph.SetUpdateSpeed(timerresolution, gridresolution);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTrafficDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTrafficDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTrafficDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTrafficDlg::OnBtnStart() 
{
	// TODO: Add your control notification handler code here
	CTrafficDlg *p = (CTrafficDlg *)::AfxGetApp()->GetMainWnd();
	if (hThread)
		return;
	
	int idx;
	CString desc, dev;
	idx = p->m_list_devices.GetCurSel();

	if (idx == -1)
		idx = 0;

	p->m_list_devices.GetText(idx, desc);
	
	for (d = alldevs; d; d = d->next) {
		if (!strcmp(d->description, desc))
			break;
	}
	dev = d->name;
	p->m_static_status.SetWindowText(dev);

	if((adhandle = pcap_open_live(dev, 65536, 1, 1000, errbuf)) == NULL) {
		::MessageBox(NULL, "Open Device Error", "Error", MB_OK);
		return ;
	}

	if (pcap_setmode(adhandle, MODE_STAT) < 0) {
		::MessageBox(NULL, "Set Mode Error", "Error", MB_OK);
		return;
	}
	
	netmask = 0xffffff;
	p->m_edit_filter.GetWindowText(filter, 100);

//	::MessageBox(NULL, filter, NULL, MB_OK);

	if (pcap_compile(adhandle, &fcode, filter, 1, netmask) < 0) {
		::MessageBox(NULL, "Error compiling filter", "Error", MB_OK);
		p->m_static_status.SetWindowText("Error compiling filter");
		return;
	}
	if (pcap_setfilter(adhandle, &fcode) < 0) {
		::MessageBox(NULL, "Error setting the filter", "Error", MB_OK);
		p->m_static_status.SetWindowText("Error setting the filter");
		return;
	}

	p->m_edit_filter.SetReadOnly(TRUE);

	hThread = ::CreateThread(NULL, NULL, MyThread, NULL, 0, &MyThreadId);

	
}


void CTrafficDlg::OnBtnStop() 
{
	// TODO: Add your control notification handler code here
	CTrafficDlg *p = (CTrafficDlg *)::AfxGetApp()->GetMainWnd();
	if (!hThread)
		return;
	BOOL ret = ::TerminateThread(hThread, 0);
	if (ret) {
		p->m_static_status.SetWindowText("Thread terminated!");
		p->m_edit_filter.SetReadOnly(FALSE);
		p->m_graph.ClearResult();
		hThread = NULL;
	}
}

void CTrafficDlg::OnBtnTop() 
{
	// TODO: Add your control notification handler code here
	CTrafficDlg *p = (CTrafficDlg *)::AfxGetApp()->GetMainWnd();
	static int topstate = 0;
	if (topstate == 0) {
		SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
		p->m_bTop.SetWindowText("Not On Top");
		topstate = 1;
	} else {
		SetWindowPos(&wndNoTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
		
		p->m_bTop.SetWindowText("On Top");
		topstate = 0;
	}
}

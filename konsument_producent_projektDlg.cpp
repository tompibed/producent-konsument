// konsument_producent_projektDlg.cpp : implementation file
//

#include "stdafx.h"
#include "konsument_producent_projekt.h"
#include "konsument_producent_projektDlg.h"
#include "afxmt.h"
#include "Windows.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define ROZ_BUFFER 10

CSemaphore wolne(ROZ_BUFFER, ROZ_BUFFER);
CSemaphore pelne(0, ROZ_BUFFER);
int cz1, cz2;
int volatile produkcja, konsumpcja;
int volatile koniec;
int licznik;
int bufor[ROZ_BUFFER];


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// Ckonsument_producent_projektDlg dialog




Ckonsument_producent_projektDlg::Ckonsument_producent_projektDlg(CWnd* pParent /*=NULL*/)
	: CDialog(Ckonsument_producent_projektDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Ckonsument_producent_projektDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_OknoCzasProdukcji);
	DDX_Control(pDX, IDC_EDIT2, m_OknoCzasKonsumpcji);
	DDX_Control(pDX, IDC_EDIT3, m_OknoProdukcji);
	DDX_Control(pDX, IDC_EDIT4, m_OknoKonsumpcji);
	DDX_Control(pDX, IDC_EDIT6, m_OknoIloscWBuforze);
	DDX_Control(pDX, IDC_EDIT5, m_OknoBufora);
	DDX_Control(pDX, IDC_BUTTON2, m_pn_Producent);
	DDX_Control(pDX, IDC_BUTTON1, m_pn_Konsument);
}

BEGIN_MESSAGE_MAP(Ckonsument_producent_projektDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON2, &Ckonsument_producent_projektDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &Ckonsument_producent_projektDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &Ckonsument_producent_projektDlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &Ckonsument_producent_projektDlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &Ckonsument_producent_projektDlg::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, &Ckonsument_producent_projektDlg::OnEnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT6, &Ckonsument_producent_projektDlg::OnEnChangeEdit6)
	ON_EN_CHANGE(IDC_EDIT5, &Ckonsument_producent_projektDlg::OnEnChangeEdit5)
END_MESSAGE_MAP()


// Ckonsument_producent_projektDlg message handlers

BOOL Ckonsument_producent_projektDlg::OnInitDialog()
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

	/*==================================================*/

	cz1=100;
	cz2=1000;

	CString czas;
	czas.Format(_T("%d"), cz1);
	m_OknoCzasProdukcji.SetWindowText(czas);
	czas.Format(_T("%d"), cz2);
	m_OknoCzasKonsumpcji.SetWindowText(czas);

	SetTimer(0,100,NULL);

	
	for(int i=0; i<ROZ_BUFFER; i++)
	{
		bufor[i]=0;
	}

	/*==================================================*/

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void Ckonsument_producent_projektDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Ckonsument_producent_projektDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR Ckonsument_producent_projektDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


UINT Ckonsument_producent_projektDlg::Producent(void* pParametr)
{
		int do_wlozenia=0;
	//licznik++;
	while(!koniec){
		wolne.Lock();
		bufor[do_wlozenia]=1;
		produkcja++;
		do_wlozenia++;
		do_wlozenia %=ROZ_BUFFER;
		pelne.Unlock();
		Sleep(cz1);
	}
	//licznik--;
	return 0;
}

UINT Ckonsument_producent_projektDlg::Konsument(void* pParametr)
{
int do_wyjecia=0;
	licznik++;
	while(!koniec){
		pelne.Lock();
		bufor[do_wyjecia]=0;
		konsumpcja++;
		do_wyjecia++;
		do_wyjecia %=ROZ_BUFFER;
		wolne.Unlock();
		Sleep(cz2);
	}
	//licznik--;
	return 0;
}

void Ckonsument_producent_projektDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	/*==========================================================*/
		CString tmp;
	tmp.Format(_T("%d"), produkcja);
	m_OknoProdukcji.SetWindowText(tmp);
	tmp.Format(_T("%d"), konsumpcja);
	m_OknoKonsumpcji.SetWindowText(tmp);
	tmp="";
	for(int i=0; i<ROZ_BUFFER; i++)
	{
		tmp.AppendFormat(_T("%d"), bufor[i]);
	}
	m_OknoBufora.SetWindowText(tmp);

	tmp.Format(_T("%d"), produkcja-konsumpcja);
	m_OknoIloscWBuforze.SetWindowText(tmp);

	/*=============================================================*/

	CDialog::OnTimer(nIDEvent);
}

void Ckonsument_producent_projektDlg::OnBnClickedButton2()
{
	m_pn_Producent.EnableWindow(0);
	koniec=0;
	AfxBeginThread(Producent, 0);
}

void Ckonsument_producent_projektDlg::OnBnClickedButton1()
{
	m_pn_Konsument.EnableWindow(0);
	koniec=0;
	AfxBeginThread(Konsument, 0);
}

void Ckonsument_producent_projektDlg::OnEnChangeEdit1()
{
	CString tmp;
	m_OknoCzasProdukcji.GetWindowText(tmp);
	sscanf(tmp, _T("%d"), &cz1);
}

void Ckonsument_producent_projektDlg::OnEnChangeEdit2()
{
	CString tmp;
	m_OknoCzasKonsumpcji.GetWindowText(tmp);
	sscanf(tmp, _T("%d"), &cz2);
}

void Ckonsument_producent_projektDlg::OnEnChangeEdit3()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void Ckonsument_producent_projektDlg::OnEnChangeEdit4()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void Ckonsument_producent_projektDlg::OnEnChangeEdit6()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void Ckonsument_producent_projektDlg::OnEnChangeEdit5()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

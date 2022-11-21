// PlayerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Player.h"
#include "PlayerDlg.h"

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
// CPlayerDlg dialog

CPlayerDlg::CPlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPlayerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPlayerDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPlayerDlg)
	DDX_Control(pDX, IDC_SOUND, m_Volume);
	DDX_Control(pDX, IDC_PLAYLIST, m_List);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPlayerDlg, CDialog)
	//{{AFX_MSG_MAP(CPlayerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_FILE_OPEN, OnFileOpen)
	ON_BN_CLICKED(IDC_PLAY, OnPlay)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_NOTIFY(NM_CLICK, IDC_PLAYLIST, OnClickPlaylist)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_PLAYLIST, OnItemchangedPlaylist)
	ON_NOTIFY(NM_DBLCLK, IDC_PLAYLIST, OnDblclkPlaylist)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SOUND, OnReleasedcaptureSound)
	ON_MESSAGE(WM_MEDIAPLAYER_NOTIFY, OnUserDefinedMessage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlayerDlg message handlers

BOOL CPlayerDlg::OnInitDialog()
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

	strcpy(m_strFileName,"");
	InitListCtrl();
	InitVolumn();
	MP3=NULL;
	
	GetDlgItem(IDC_PLAY)->EnableWindow(FALSE);
	GetDlgItem(IDC_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_PAUSE)->EnableWindow(FALSE);
	
	// TODO: Add extra initialization here
	
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPlayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPlayerDlg::OnPaint() 
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
HCURSOR CPlayerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPlayerDlg::OnFileOpen() 
{

	CString PathName;
	CString FileName;
	
	CFileDialog dlg(TRUE,_T("MP3") ,_T("*.MP3"),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("MP3 FILE (*.MP3)|*.MP3|WAVE FILE (*.WAV)|*.WAV|ALL FILE (*.*)|*.*|"));
	if(dlg.DoModal()==IDOK)
	{
		PathName=dlg.GetPathName();
		FileName=dlg.GetFileName();
		lstrcpy((LPSTR)m_strPathName,(LPSTR)PathName.operator const char*());
		lstrcpy((LPSTR)m_strFileName,(LPSTR)FileName.operator const char*());
		TotalCnt=m_List.GetItemCount();
		lvitem.mask=LVIF_TEXT;
		lvitem.iItem=TotalCnt;
		lvitem.iSubItem=0;
		lvitem.pszText=m_strFileName;
		m_List.InsertItem(&lvitem);
		
		lvitem.mask=LVIF_TEXT;
		lvitem.iItem=TotalCnt;
		lvitem.iSubItem=1;
		lvitem.pszText=m_strPathName;
		m_List.SetItem(&lvitem);


		
		
		
		GetDlgItem(IDC_PLAY)->EnableWindow(TRUE);
		GetDlgItem(IDC_STOP)->EnableWindow(TRUE);
	}	
}



void CPlayerDlg::OnPlay() 
{	
	OnStop();	
	MP3=new CMediaPlayer;
	MP3->Init(m_hWnd,WM_MEDIAPLAYER_NOTIFY);
	MP3->Open((LPSTR)m_strPathName);
	MP3->Stop();
	MP3->Play();


	
	
}

void CPlayerDlg::OnStop() 
{
	if(MP3!=NULL)
	{
		MP3->Stop();
		delete MP3;
		MP3=NULL;
	}
}



BOOL CPlayerDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	OnStop();
	return CDialog::DestroyWindow();
}





void CPlayerDlg::InitListCtrl()
{
	lvcolumn.mask=LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvcolumn.fmt=LVCFMT_LEFT;
	lvcolumn.pszText="FileName";
	lvcolumn.iSubItem=0;
	lvcolumn.cx=80;
	m_List.InsertColumn(0,&lvcolumn);

	lvcolumn.mask=LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvcolumn.fmt=LVCFMT_LEFT;
	lvcolumn.pszText="PathName";
	lvcolumn.iSubItem=1;
	lvcolumn.cx=80;
	m_List.InsertColumn(1,&lvcolumn);



}

void CPlayerDlg::OnClickPlaylist(NMHDR* pNMHDR, LRESULT* pResult) 
{

	m_List.GetItemText(DataNum,1,m_strPathName,256);
	*pResult = 0;
}

void CPlayerDlg::OnItemchangedPlaylist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	DataNum=pNMListView->iItem;
	*pResult = 0;
}

void CPlayerDlg::OnDblclkPlaylist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnStop();
	OnPlay();
	*pResult = 0;
}



void CPlayerDlg::OnDelete() 
{
	if(!m_List.GetItemCount())
	{
		AfxMessageBox("������ ����Ʈ�� �����ϴ�!!");
		return;
	}
	if(MP3->GetState())
	{
		if(!strcmp(MP3->GetPlayFile(),m_strPathName))
		{
			AfxMessageBox("������ ������Դϴ�.");
			return;
		}
	}
	m_List.DeleteItem(DataNum);

}

void CPlayerDlg::InitVolumn()
{
	m_Volume.SetRange(0,50 );
	
    m_Volume.SetPageSize( 2 );
	
	
	
    //���� ������ �ް� �������� �����Ѵ�.
	
    waveOutGetVolume( NULL, &m_nVolume );
	
    m_nleftVolume = LOWORD( m_nVolume);
	
    m_nrightVolume = HIWORD( m_nVolume );
	
	
	
    //���� ������� ��� ������ ������ ���� ������ ���� 0 ~ 65535�� ��ġ�� ������ �˴ϴ�.
	
    //�� ������ ��ġ�� �����̴��� ������ ������ 16���� �ɰ��� �����̴� �Ѱ������� 4095
	
    //�� �ȴٴ� ����� �˼� �������Դϴ�. ��, �Ʒ����� 4095(0xFFF)�� ������ �������ִ� ������
	
    //������ ũ�⸦ �츮�� ������ �����̴� ��Ʈ�ѿ� �����ϵ��� ��ġ�� ���� �����Դϴ�.
	
    m_nVolumePos = m_nleftVolume/0xFFF;
	
	
	
    //�����̴� ��Ʈ���� ����� 0�̰� �ϴ��� 16�̹Ƿ� �ٲپ ��ġ��ŵ�ϴ�.
	
    m_nVolumePos = 16-m_nVolumePos;
	
	
	
    //�����̴� ��Ʈ���� ��ġ�� �����Ѵ�.
	
    m_Volume.SetPos( m_nVolumePos );
	


}

void CPlayerDlg::OnReleasedcaptureSound(NMHDR* pNMHDR, LRESULT* pResult) 
{

	int nNum;

    nNum = m_Volume.GetPos();

    m_nVolumePos = nNum;

 

    //���⿡�� �� 16���� ���ְ� 0xFFF�� ������� �ϴ��� �� �𸣰ڴٸ� InitVolumn()�κ��� �� �ڼ��� �о����.

    nNum = 16-nNum;

    nNum = nNum*0xFFF; 

    m_nleftVolume = nNum;

    m_nrightVolume = nNum;

 

    m_nVolume = m_nrightVolume;

    m_nVolume = m_nVolume << 16;

    m_nVolume = m_nVolume + m_nleftVolume;

 

    //���� ������ m_nVolumn�� �����մϴ�.

    waveOutSetVolume(NULL,m_nVolume);


	*pResult = 0;
}


BOOL CPlayerDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	return CDialog::OnCommand(wParam, lParam);
}

LRESULT CPlayerDlg::OnUserDefinedMessage(WPARAM wParam, LPARAM lParam) {

	return 0;
}

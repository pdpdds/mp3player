// PlayerDlg.h : header file
//

#if !defined(AFX_PLAYERDLG_H__38A8379A_14A6_4E9F_A4D5_2E21D83C1981__INCLUDED_)
#define AFX_PLAYERDLG_H__38A8379A_14A6_4E9F_A4D5_2E21D83C1981__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MediaPlayer.h"
//#include "Playlist.h"
#include "mmsystem.h"
/////////////////////////////////////////////////////////////////////////////
// CPlayerDlg dialog

class CPlayerDlg : public CDialog
{
// Construction
public:
	void InitVolumn();
	void InitListCtrl();
	CPlayerDlg(CWnd* pParent = NULL);	// standard constructor

	char m_strFileName[255];
	char m_strPathName[255];
	CMediaPlayer *MP3;
	LV_COLUMN lvcolumn;
	LV_ITEM lvitem;
	int DataNum;
	int TotalCnt;


	int	m_nrightVolume;      //¿À¸¥ ÂÊ º¼·ý 
    int m_nleftVolume;       //¿ÞÂÊ º¼·ý 
    DWORD m_nVolume;           
    int m_nVolumePos;

// Dialog Data
	//{{AFX_DATA(CPlayerDlg)
	enum { IDD = IDD_PLAYER_DIALOG };
	CSliderCtrl	m_Volume;
	CListCtrl	m_List;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlayerDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	
	

	// Generated message map functions
	//{{AFX_MSG(CPlayerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnFileOpen();
	afx_msg void OnPlay();
	afx_msg void OnStop();
	afx_msg void OnClickPlaylist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedPlaylist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkPlaylist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDelete();
	afx_msg void OnReleasedcaptureSound(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg LRESULT OnUserDefinedMessage(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYERDLG_H__38A8379A_14A6_4E9F_A4D5_2E21D83C1981__INCLUDED_)

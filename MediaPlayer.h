// MediaPlayer.h: interface for the CMediaPlayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEDIAPLAYER_H__83F8DCC7_059B_4A46_B729_4D21DBD5DF57__INCLUDED_)
#define AFX_MEDIAPLAYER_H__83F8DCC7_059B_4A46_B729_4D21DBD5DF57__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Dshow.h>
#include <tchar.h>
#define SAFE_RELEASE(p)           {if (p) p->Release();p=NULL;}
#define WM_MEDIAPLAYER_NOTIFY      WM_USER+100
#define STOP 0
#define PLAY 1
#define PAUSE 2

class CMediaPlayer  
{
public:
	CMediaPlayer();
	virtual ~CMediaPlayer();

public:
	
	void Init(HWND hWnd ,  UINT uiMsg);
	void Open(const char *szFileName);
	bool Play();//
	void Pause();
	void Stop();
	void Close();
	int GetState();//재생상태를 넘겨주는 함수
	char* GetPlayFile();//재생중인 파일이름을 가져오는 함수
	
	bool WMNotify();
	
	bool Replay();
	bool IsPause();
	
private:
	IGraphBuilder        *p_GraphBuilder;
	IMediaControl        *p_MediaControl;
	IMediaEventEx        *p_MediaEvent;
	IMediaSeeking        *p_MediaSeeking;
	IBaseFilter			 *p_SrcCur;
	IBaseFilter			 *p_SrcNext;


	
	BYTE m_state;
	char m_strPathName[255];
    

};

#endif // !defined(AFX_MEDIAPLAYER_H__83F8DCC7_059B_4A46_B729_4D21DBD5DF57__INCLUDED_)

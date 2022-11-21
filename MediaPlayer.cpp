// MediaPlayer.cpp: implementation of the CMediaPlayer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Player.h"
#include "MediaPlayer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMediaPlayer::CMediaPlayer()
{
	m_state=STOP;
	p_GraphBuilder=NULL;
	p_MediaControl=NULL;
	p_MediaEvent=NULL;
	p_MediaSeeking=NULL;
	p_SrcCur=NULL;
	p_SrcNext=NULL;
	
}

CMediaPlayer::~CMediaPlayer()
{
	SAFE_RELEASE(p_GraphBuilder);
	SAFE_RELEASE(p_MediaControl);
	SAFE_RELEASE(p_MediaEvent);
	SAFE_RELEASE(p_MediaSeeking);
	SAFE_RELEASE(p_SrcCur);
	SAFE_RELEASE(p_SrcNext);
	CoUninitialize();

}


void CMediaPlayer::Init(HWND hWnd , UINT uiMsg)
{
	CoInitialize(NULL);
	
	CoCreateInstance(CLSID_FilterGraph, NULL,CLSCTX_INPROC, IID_IGraphBuilder,(void **)&p_GraphBuilder);
	p_GraphBuilder->QueryInterface(IID_IMediaControl, (void **)&p_MediaControl);
	p_GraphBuilder->QueryInterface(IID_IMediaEvent, (void **)&p_MediaEvent);
	p_GraphBuilder->QueryInterface(IID_IMediaSeeking, (void **)&p_MediaSeeking);
	
	p_MediaEvent->SetNotifyWindow((OAHWND)hWnd, uiMsg, 0);
}

void CMediaPlayer::Open(const char *szFileName)
{
	WCHAR wszName[256];
	MultiByteToWideChar(CP_ACP, 0, szFileName, -1, wszName, 256);
	p_GraphBuilder->RenderFile(wszName, NULL);
	strcpy(m_strPathName,szFileName);
}

bool CMediaPlayer::Play()
{
        if(!p_MediaControl)
			return FALSE;
        if(FAILED(p_MediaControl->Run()))
			return FALSE;
        m_state=PLAY;
        return TRUE;
}
void CMediaPlayer::Stop()
{
	
	if(!p_MediaControl)
		return;
	p_MediaControl->Stop();
	m_state=STOP;
	
	LONGLONG pos=0;
	p_MediaSeeking->SetPositions(&pos, AM_SEEKING_AbsolutePositioning, NULL, AM_SEEKING_NoPositioning);
}

int CMediaPlayer::GetState()
{
	return m_state;
}

char* CMediaPlayer::GetPlayFile()
{
	return m_strPathName;
}
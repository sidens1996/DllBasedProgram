
// DllBasedProgram.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDllBasedProgramApp: 
// �йش����ʵ�֣������ DllBasedProgram.cpp
//

class CDllBasedProgramApp : public CWinApp
{
public:
	CDllBasedProgramApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDllBasedProgramApp theApp;
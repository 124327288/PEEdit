
// PEEdit.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPEEditApp:
// �йش����ʵ�֣������ PEEdit.cpp
//

class CPEEditApp : public CWinApp
{
public:
	CPEEditApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPEEditApp theApp;
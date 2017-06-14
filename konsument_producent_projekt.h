// konsument_producent_projekt.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// Ckonsument_producent_projektApp:
// See konsument_producent_projekt.cpp for the implementation of this class
//

class Ckonsument_producent_projektApp : public CWinApp
{
public:
	Ckonsument_producent_projektApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern Ckonsument_producent_projektApp theApp;
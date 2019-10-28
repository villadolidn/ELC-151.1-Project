//---------------------------------------------------------------------------
//
// Name:        fingerCountApp.h
// Author:      Nathan Villadolid
// Created:     10/28/2019 12:49:45 PM
// Description: 
//
//---------------------------------------------------------------------------

#ifndef __FINGERCOUNTFRMApp_h__
#define __FINGERCOUNTFRMApp_h__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#else
	#include <wx/wxprec.h>
#endif

class fingerCountFrmApp : public wxApp
{
	public:
		bool OnInit();
		int OnExit();
};

#endif

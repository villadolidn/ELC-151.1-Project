//---------------------------------------------------------------------------
//
// Name:        fingerCountv3App.h
// Author:      Nathan Villadolid
// Created:     10/29/2019 9:31:36 PM
// Description: 
//
//---------------------------------------------------------------------------

#ifndef __FINGERCOUNTV3FRMApp_h__
#define __FINGERCOUNTV3FRMApp_h__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#else
	#include <wx/wxprec.h>
#endif

class fingerCountv3FrmApp : public wxApp
{
	public:
		bool OnInit();
		int OnExit();
};

#endif

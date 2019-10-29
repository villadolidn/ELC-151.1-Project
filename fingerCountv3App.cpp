//---------------------------------------------------------------------------
//
// Name:        fingerCountv3App.cpp
// Author:      Nathan Villadolid
// Created:     10/29/2019 9:31:36 PM
// Description: 
//
//---------------------------------------------------------------------------

#include "fingerCountv3App.h"
#include "fingerCountv3Frm.h"

IMPLEMENT_APP(fingerCountv3FrmApp)

bool fingerCountv3FrmApp::OnInit()
{
    fingerCountv3Frm* frame = new fingerCountv3Frm(NULL);
    SetTopWindow(frame);
    frame->Show();
    return true;
}
 
int fingerCountv3FrmApp::OnExit()
{
	return 0;
}

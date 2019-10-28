//---------------------------------------------------------------------------
//
// Name:        fingerCountApp.cpp
// Author:      Nathan Villadolid
// Created:     10/28/2019 12:49:45 PM
// Description: 
//
//---------------------------------------------------------------------------

#include "fingerCountApp.h"
#include "fingerCountFrm.h"

IMPLEMENT_APP(fingerCountFrmApp)

bool fingerCountFrmApp::OnInit()
{
    fingerCountFrm* frame = new fingerCountFrm(NULL);
    SetTopWindow(frame);
    frame->Show();
    return true;
}
 
int fingerCountFrmApp::OnExit()
{
	return 0;
}

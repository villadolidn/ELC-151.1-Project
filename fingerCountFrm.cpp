///-----------------------------------------------------------------
///
/// @file      fingerCountFrm.cpp
/// @author    Nathan Villadolid
/// Created:   10/28/2019 12:49:45 PM
/// @section   DESCRIPTION
///            fingerCountFrm class implementation
///
///------------------------------------------------------------------

#include "fingerCountFrm.h"

//Do not add custom headers between
//Header Include Start and Header Include End
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// fingerCountFrm
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(fingerCountFrm, wxFrame)
	////Manual Code Start
	////Manual Code End
	EVT_CLOSE(fingerCountFrm::OnClose)
END_EVENT_TABLE()
////Event Table End

fingerCountFrm::fingerCountFrm(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxFrame(parent, id, title, position, size, style)
{
	CreateGUIControls();
}

fingerCountFrm::~fingerCountFrm()
{
}

void fingerCountFrm::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start
	////GUI Items Creation End
}

void fingerCountFrm::OnClose(wxCloseEvent& event)
{
	Destroy();
}

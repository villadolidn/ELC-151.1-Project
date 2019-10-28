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
BEGIN_EVENT_TABLE(fingerCountFrm,wxFrame)
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

	wxInitAllImageHandlers();   //Initialize graphic format handlers

	actualFingerCount = new wxStaticText(this, ID_ACTUALFINGERCOUNT, _("0"), wxPoint(648, 527), wxDefaultSize, 0, _("actualFingerCount"));

	labelFingerCount = new wxStaticText(this, ID_LABELFINGERCOUNT, _("Number of Fingers Extended"), wxPoint(472, 527), wxDefaultSize, 0, _("labelFingerCount"));

	actualDefectCount = new wxStaticText(this, ID_ACTUALDEFECTCOUNT, _("0"), wxPoint(1026, 449), wxDefaultSize, 0, _("actualDefectCount"));

	labelDefectCount = new wxStaticText(this, ID_LABELDEFECTCOUNT, _("Number of Convexity Defects:"), wxPoint(858, 449), wxDefaultSize, 0, _("labelDefectCount"));

	buttonCountFingers = new wxButton(this, ID_BUTTONCOUNTFINGERS, _("Count Fingers"), wxPoint(880, 392), wxSize(145, 32), 0, wxDefaultValidator, _("buttonCountFingers"));

	buttonThreshold = new wxButton(this, ID_BUTTONTHRESHOLD, _("Obtain Threshold"), wxPoint(488, 384), wxSize(151, 32), 0, wxDefaultValidator, _("buttonThreshold"));

	buttonSelectImage = new wxButton(this, ID_BUTTONSELECTIMAGE, _("Select Image"), wxPoint(128, 384), wxSize(137, 34), 0, wxDefaultValidator, _("buttonSelectImage"));

	bitmapDefects = new wxStaticBitmap(this, ID_BITMAPDEFECTS, wxNullBitmap, wxPoint(760, 24), wxSize(350, 350) );

	bitmapThreshold = new wxStaticBitmap(this, ID_BITMAPTHRESHOLD, wxNullBitmap, wxPoint(392, 24), wxSize(350, 350) );

	bitmapOriginal = new wxStaticBitmap(this, ID_BITMAPORIGINAL, wxNullBitmap, wxPoint(24, 24), wxSize(350, 350) );

	WxStaticBitmap2 = new wxStaticBitmap(this, ID_WXSTATICBITMAP2, wxNullBitmap, wxPoint(384, 24), wxSize(1, 2) );

	SetTitle(_("Finger Counting"));
	SetIcon(wxNullIcon);
	SetSize(8,8,1184,608);
	Center();
	
	////GUI Items Creation End
}

void fingerCountFrm::OnClose(wxCloseEvent& event)
{
	Destroy();
}

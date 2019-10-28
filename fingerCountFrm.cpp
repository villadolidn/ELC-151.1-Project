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
#include <wx/bitmap.h>
#include <string>
#include <iostream>
#include <cmath>

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
	EVT_BUTTON(ID_BUTTONSELECTIMAGE,fingerCountFrm::buttonSelectImageClick)
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

	WxOpenFileDialog1 =  new wxFileDialog(this, _("Choose a file"), _(""), _(""), _("*.*"), wxFD_OPEN);

	actualFingerCount = new wxStaticText(this, ID_ACTUALFINGERCOUNT, _("0"), wxPoint(552, 434), wxDefaultSize, 0, _("actualFingerCount"));

	labelFingerCount = new wxStaticText(this, ID_LABELFINGERCOUNT, _("Number of Fingers Extended"), wxPoint(376, 434), wxDefaultSize, 0, _("labelFingerCount"));

	actualDefectCount = new wxStaticText(this, ID_ACTUALDEFECTCOUNT, _("0"), wxPoint(881, 389), wxDefaultSize, 0, _("actualDefectCount"));

	labelDefectCount = new wxStaticText(this, ID_LABELDEFECTCOUNT, _("Number of Convexity Defects:"), wxPoint(713, 389), wxDefaultSize, 0, _("labelDefectCount"));

	buttonCountFingers = new wxButton(this, ID_BUTTONCOUNTFINGERS, _("Count Fingers"), wxPoint(717, 334), wxSize(150, 30), 0, wxDefaultValidator, _("buttonCountFingers"));

	buttonThreshold = new wxButton(this, ID_BUTTONTHRESHOLD, _("Obtain Threshold"), wxPoint(399, 334), wxSize(150, 30), 0, wxDefaultValidator, _("buttonThreshold"));

	buttonSelectImage = new wxButton(this, ID_BUTTONSELECTIMAGE, _("Select Image"), wxPoint(129, 332), wxSize(150, 30), 0, wxDefaultValidator, _("buttonSelectImage"));

	bitmapDefects = new wxStaticBitmap(this, ID_BITMAPDEFECTS, wxNullBitmap, wxPoint(649, 24), wxSize(300, 300) );

	bitmapThreshold = new wxStaticBitmap(this, ID_BITMAPTHRESHOLD, wxNullBitmap, wxPoint(337, 24), wxSize(300, 300) );

	bitmapOriginal = new wxStaticBitmap(this, ID_BITMAPORIGINAL, wxNullBitmap, wxPoint(25, 24), wxSize(300, 300) );

	WxStaticBitmap2 = new wxStaticBitmap(this, ID_WXSTATICBITMAP2, wxNullBitmap, wxPoint(384, 24), wxSize(1, 2) );

	SetTitle(_("Finger Counting"));
	SetIcon(wxNullIcon);
	SetSize(8,8,1015,521);
	Center();
	
	////GUI Items Creation End
}

void fingerCountFrm::OnClose(wxCloseEvent& event)
{
	Destroy();
}

/*****************************************************************************
Functions for Calculations
******************************************************************************/








/*****************************************************************************
Button Events
******************************************************************************/

// image variables (wxImage class)
wxImage imageIn;
wxImage wip;
wxImage imageOut;

// boolean that stops the dialog from closing until an image is picked
bool isImageOpen = false;

// button that loads the image
void fingerCountFrm::buttonSelectImageClick(wxCommandEvent& event)
{
    WxOpenFileDialog1->ShowModal();
    
    if (WxOpenFileDialog1->GetPath().IsEmpty())
    {
        return;
    }
    
    isImageOpen = imageIn.LoadFile(WxOpenFileDialog1->GetPath(), wxBITMAP_TYPE_ANY);
    	
    int height = imageIn.GetHeight();
    int width = imageIn.GetWidth();
        
    wip.Create(width,height);
        
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            wip.SetRGB(x, y, 240, 240, 240); // (width, height, R, G, B)
        }
    }
        
    if (300 >= (height*300/width)) 
    {    
        bitmapOriginal->SetBitmap(wip.Scale(300,height*300/width));
        bitmapOriginal->SetBitmap(imageIn.Scale(300,height*300/width));
    } 
    else
    {
        bitmapOriginal->SetBitmap(wip.Scale(width*300/height,300));
        bitmapOriginal->SetBitmap(imageIn.Scale(width*300/height,300));
    }
}

///-----------------------------------------------------------------
///
/// @file      fingerCountv3Frm.cpp
/// @author    Nathan Villadolid
/// Created:   10/29/2019 9:31:36 PM
/// @section   DESCRIPTION
///            fingerCountv3Frm class implementation
///
///------------------------------------------------------------------

#include "fingerCountv3Frm.h"

//Do not add custom headers between
//Header Include Start and Header Include End
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// fingerCountv3Frm
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(fingerCountv3Frm,wxFrame)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(fingerCountv3Frm::OnClose)
	EVT_BUTTON(ID_BUTTONOBTAINDEFECTS,fingerCountv3Frm::buttonObtainDefectsClick)
	EVT_BUTTON(ID_BUTTONINSERTIMAGE,fingerCountv3Frm::buttonInsertImageClick)
END_EVENT_TABLE()
////Event Table End

fingerCountv3Frm::fingerCountv3Frm(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxFrame(parent, id, title, position, size, style)
{
	CreateGUIControls();
}

fingerCountv3Frm::~fingerCountv3Frm()
{
}

void fingerCountv3Frm::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	wxInitAllImageHandlers();   //Initialize graphic format handlers

	dialogChooseImage =  new wxFileDialog(this, _("Choose a file"), _(""), _(""), _("*.bmp*"), wxFD_OPEN);

	labelFingerCount = new wxStaticText(this, ID_LABELFINGERCOUNT, _("Number of Fingers..."), wxPoint(640, 128), wxDefaultSize, 0, _("labelFingerCount"));

	buttonObtainDefects = new wxButton(this, ID_BUTTONOBTAINDEFECTS, _("Count Fingers"), wxPoint(633, 79), wxSize(125, 28), 0, wxDefaultValidator, _("buttonObtainDefects"));

	buttonObtainMask = new wxButton(this, ID_BUTTONOBTAINMASK, _("Obtain Mask"), wxPoint(632, 48), wxSize(125, 28), 0, wxDefaultValidator, _("buttonObtainMask"));

	buttonInsertImage = new wxButton(this, ID_BUTTONINSERTIMAGE, _("Insert Image"), wxPoint(632, 16), wxSize(125, 28), 0, wxDefaultValidator, _("buttonInsertImage"));

	bitmapOutput = new wxStaticBitmap(this, ID_BITMAPOUTPUT, wxNullBitmap, wxPoint(320, 16), wxSize(300, 300) );
	bitmapOutput->SetToolTip(_("Output"));

	bitmapInput = new wxStaticBitmap(this, ID_BITMAPINPUT, wxNullBitmap, wxPoint(8, 16), wxSize(300, 300) );
	bitmapInput->SetToolTip(_("Input"));
	bitmapInput->SetHelpText(_("Input"));

	SetTitle(_("Finger Counting"));
	SetIcon(wxNullIcon);
	SetSize(8,8,793,377);
	Center();
	
	////GUI Items Creation End
}

void fingerCountv3Frm::OnClose(wxCloseEvent& event)
{
	Destroy();
}
/*****************************************
FUNCTIONSSSSSSS
*******************************************/
void drawContour(int& r, int& g, int& b){
    
}





/*****************************************
EVENTS
*******************************************/

/*
 * buttonInsertImageClick
 */
 
wxImage input;
wxImage display;
wxImage bg;

bool openImageFlag = false;

void fingerCountv3Frm::buttonInsertImageClick(wxCommandEvent& event)
{
	dialogChooseImage->ShowModal(); // pops open the choose image dialog
	
    if (dialogChooseImage -> GetPath().IsEmpty())
	   return;
	
	openImageFlag = input.LoadFile(dialogChooseImage->GetPath(), wxBITMAP_TYPE_ANY);
	
	int height = input.GetHeight();
	int width = input.GetWidth();
	
	bg.Create(width, height);
	
	// creates a white panel with the same dimensions as the image
	for (int x = 0; x < width; x++) 
    {
        for (int y = 0; y < height; y++)
            bg.SetRGB(x, y, 63, 63, 63);
    }
    
    if (300 >= (height*300/width))
    {
        bitmapInput->SetBitmap(bg.Scale(300, height*300/width));
        bitmapInput->SetBitmap(input.Scale(300, height * 300 / width));
    }
    else
    {
        bitmapInput->SetBitmap(bg.Scale(300*width/height, 300));
        bitmapInput->SetBitmap(input.Scale(width*300/height, 300));
    }
}

/*
 * buttonObtainDefectsClick
 */
void fingerCountv3Frm::buttonObtainDefectsClick(wxCommandEvent& event)
{
    if (openImageFlag)
    {
        int height = input.GetHeight();
        int width = input.GetWidth();
        
        display.Create(width, height);
        bg.Create(width, height);
        
        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                int redVal = input.GetRed(x, y);
                int greenVal = input.GetGreen(x, y);
                int blueVal = input.GetBlue(x, y);
                wxImage::RGBValue rgb = wxImage::RGBValue(redVal, greenVal, blueVal);
                
                drawContour(redVal, greenVal, blueVal); //MAKE SURE THESE ARE QUERIES
                display.SetRGB(x, y, redVal, greenVal, blueVal);
                bg.SetRGB(x, y, 69, 69, 69);
    }
    else
    {
        wxMessageBox("Please load an image",_T("Image"),wxOK | wxICON_EXCLAMATION, this);
    }
}

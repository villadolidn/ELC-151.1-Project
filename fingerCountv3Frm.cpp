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
	EVT_BUTTON(ID_BUTTONOBTAINMASK,fingerCountv3Frm::buttonObtainMaskClick)
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
void nextClockwise(int x_b, int y_b, int &x, int &y, int x_p, int y_p)
{
    int xDiff = x_p - x_b;
    int yDiff = y_p - y_b;
    
    switch (xDiff)
    {
        case -1:
            switch (yDiff)
            {
                case -1:
                    x++;
                    break;
                case 0:
                    y--;
                    break;
                case 1:
                    y--;
                    break;
            }
            break;
        case 0:
            switch (yDiff)
            {
                case -1:
                    x++;
                    break;
                case 1:
                    x--;
                    break;
            }
            break;
        case 1:
            switch (yDiff)
            {
                case -1:
                    y++;
                    break;
                case 0:
                    y++;
                    break;
                case 1:
                    x--;
                    break;
            }
            break;
        
    }
    
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
    bool startSet = false;
    bool gettingContour = true;
    if (openImageFlag)
    {
        int height = input.GetHeight();
        int width = input.GetWidth();
        
        // necessary values for the contour
        int x_s = 0;
        int y_s = height-1;
        int x_b = 0;
        int y_b = height-1;
        int x_p = 0;
        int y_p = height-1;
        int x = 0;
        int y = height-1;
        
        
        display.Create(width, height);
        bg.Create(width, height);
        
        // Moore's Neighboorhood
        while (gettingContour)
        {
            // obtaining color values for a certain pixel
            int red = (input.GetRed(x,y));
            int green = (input.GetGreen(x,y));
            int blue = (input.GetBlue(x,y));
            wxImage::RGBValue rgbVal = wxImage::RGBValue(red, green, blue);
            
            if (red != 255 && green != 255 && blue != 255)
            {
                if (!startSet)
                {
                    startSet = true; // remove flag
                    
                    x_s = x; // set starting pixel
                    y_s = y;
                    
                    display.SetRGB(x_s, y_s, 255, 0, 0); // paint pixel red
                    
                    x_p = x_s;
                    y_p = y_s;
                    
                    x_b = x_s-1;
                    y_b = y_s;
                    
                    nextClockwise(x_b, y_b, x, y, x_p, y_p);
                }
                else
                {
                    display.SetRGB(x, y, 255, 0, 0);
                    x_b = x_p;
                    y_b = x_p;
                    x_p = x;
                    y_p = y;
                    nextClockwise(x_b, y_b, x, y, x_p, y_p);
                }
            }
            else if (startSet)
            {
                x_b = x;
                y_b = y;
                nextClockwise(x_b, y_b, x, y, x_p, y_p);
            }
            
            if (startSet && x_s == x && y_s == y)
                gettingContour = false;
        }
        
        // fills in the rest of the image with white
        for (int x = 0; x < width; x++) 
        {
            for (int y = 0; y < height; y++)
            {
                int red = (input.GetRed(x,y));
                int green = (input.GetGreen(x,y));
                int blue = (input.GetBlue(x,y));
                wxImage::RGBValue rgbVal = wxImage::RGBValue(red, green, blue);
                if (red != 255 && green != 0 && blue != 0)
                    display.SetRGB(x, y, 255, 255, 255);
        }
        
        // displays the image
        if (300 >= (height*300/width))
        {
            bitmapOutput->SetBitmap(bg.Scale(300, height*300/width));
            bitmapOutput->SetBitmap(display.Scale(300, height * 300 / width));
        }
        else
        {
            bitmapOutput->SetBitmap(bg.Scale(300*width/height, 300));
            bitmapOutput->SetBitmap(display.Scale(width*300/height, 300));
        }
        }
        
}
    else
    {
        wxMessageBox("Please load an image",_T("Image"),wxOK | wxICON_EXCLAMATION, this);
    }
}

/*
 * buttonObtainMaskClick
 */
void fingerCountv3Frm::buttonObtainMaskClick(wxCommandEvent& event)
{
	// insert your code here
}

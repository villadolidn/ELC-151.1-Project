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
#include <iostream> 
#include <vector>

using namespace std;

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
void clockwise(int p_x, int p_y, int b_x, int b_y, int& c_x, int& c_y)
{
    int xDiff = p_x - b_x;
    int yDiff = p_y - b_y;
    
    switch (xDiff)
    {
        case -1:
            switch (yDiff)
            {
                case -1:
                    c_x++;
                    break;
                case 0:
                    c_y--;
                    break;
                case 1:
                    c_y--;
                    break;
            }
            break;
        case 0:
            switch (yDiff)
            {
                case -1:
                    c_x++;
                    break;
                case 1:
                    c_x--;
                    break;
            }
            break;
        case 1:
            switch (yDiff)
            {
                case -1:
                    c_y++;
                    break;
                case 0:
                    c_y++;
                    break;
                case 1:
                    c_x--;
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
    if (openImageFlag)
    {
        int height = input.GetHeight();
        int width = input.GetWidth();
        
        display.Create(width, height);
        bg.Create(width, height);
        vector< vector<int> > vectThreshold(height, vector<int>(width, 1)); // 1 = white, 0 = black
        vector< vector<int> > vectContour(height, vector<int>(width, 1)); // 1 = white, 0 = red
        
        
        // storing the input pixel values in a vector
		// note: y and x start at 1 in order to add a buffer
        for (int y = 1; y < height; y++)
        {
			for (int x = 1; x < width; x++)
            {
				
				int red = (input.GetRed(x,y));
				int green = (input.GetGreen(x,y));
				int blue = (input.GetBlue(x,y));
				wxImage::RGBValue rgbVal = wxImage::RGBValue(red, green, blue);
				
				
				if (red == 0 && green == 0 && blue == 0)
				{
					vectThreshold[y][x] = 0;  // black = 0
				}
            }
        }
		
		// prepping the display image by painting it white
		for (int x = 0; x < width; x++) 
		{
			for (int y = 0; y < height; y++)
				display.SetRGB(x, y, 255, 255, 255);
		}
		
        
        /* 
        Moore's Neighboorhood Algorithm
		I.
        1. Find the first boundary pixel s
        2. Insert s in vectContour
        3. Set p = s
        4. Set b = pixe from which s was entered
        5. clockwise(c)
		II.
        while c != s
            if c = 0
                insert c in vectContour
                b = p
                p = c
                clockwise(c)
            else
                b = c
                clockwise(c)
        */
		
		int s_x, s_y, p_x, p_y, b_x, b_y, c_x, c_y;
		
		// I.
		bool startingPixelFound = false;
		for (int y = height - 1; y >=0; y--)
		{
			for (int x = 0; x < width; x++)
			{
				if (vectThreshold[y][x]== 0)
				{
					startingPixelFound = true;
					s_x = x;
					s_y = y;
					vectContour[y][x] = 0;
					p_x = s_x;
					p_y = s_y;
					b_x = s_x -1;
					b_y = s_y;
					clockwise(p_x, p_y, b_x, b_y, c_x, c_y);
					break;
				}
			}
			if (startingPixelFound)
				break;
		}
		// II.
		while (c_x != s_x && c_y != s_y)
		{
			if (vectThreshold[c_y][c_x]== 0)
			{
				vectContour[c_y][c_x] = 0;
				b_x = p_x;
				b_y = p_y;
				p_x = c_x;
				p_y = c_y;
				clockwise(p_x, p_y, b_x, b_y, c_x, c_y);
			}
			else
			{
				b_x = c_x;
				b_y = c_y;
				clockwise(p_x, p_y, b_x, b_y, c_x, c_y);
			}
        }
		
		// applying the changes to wxImage display based on the contour vector
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				if (vectContour[y][x] == 0)
					display.SetRGB(x, y, 255, 0, 0);
			}
		}
		
		
        // printing it onto bitmapOutput
        if (300 >= (height*300/width))
		{
			bitmapOutput->SetBitmap(bg.Scale(300,height*300/width));
			bitmapOutput->SetBitmap(display.Scale(300,height*300/width));
		}
		else
		{
			bitmapOutput->SetBitmap(bg.Scale(width*300/height,300));
			bitmapOutput->SetBitmap(display.Scale(width*300/height,300));
		}
        
        
    }
    else
    {
        wxMessageBox("No Image Selected :(",_T("Image"),wxOK | wxICON_EXCLAMATION, this);
    }
}

/*
 * buttonObtainMaskClick
 */
void fingerCountv3Frm::buttonObtainMaskClick(wxCommandEvent& event)
{
	// insert your code here
}

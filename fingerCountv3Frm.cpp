///-----------------------------------------------------------------
///
/// @file      fingerCountv3Frm.cpp
/// @author    Nathan Villadolid
/// Created:   10/29/2019 9:31:36 PM
/// @section   DESCRIPTION
///            fingerCountv3Frm class implementation
///
///------------------------------------------------------------------
//FINAL
#include "fingerCountv3Frm.h"
#include <iostream> 
#include <vector>
#include <wx/log.h> 
#include <wx/textfile.h>
#include <sstream>
#include <bits/stdc++.h> 

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
	
	EVT_TEXT(ID_WXEDIT3,fingerCountv3Frm::WxEdit1Updated0)
	
	EVT_TEXT(ID_WXEDIT2,fingerCountv3Frm::WxEdit1Updated0)
	
	EVT_TEXT(ID_WXEDIT1,fingerCountv3Frm::WxEdit1Updated0)
	EVT_BUTTON(ID_BUTTONCROPIMAGE,fingerCountv3Frm::buttonCropImageClick)
	EVT_BUTTON(ID_BUTTONGETCONTOUR,fingerCountv3Frm::buttonGetContourClick)
	EVT_BUTTON(ID_BUTTONSAVEIMAGE,fingerCountv3Frm::buttonSaveImageClick)
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

	bitmapInput = new wxStaticBitmap(this, ID_BITMAPINPUT, wxNullBitmap, wxPoint(8, 16), wxSize(300, 300) );
	bitmapInput->SetToolTip(_("Input"));
	bitmapInput->SetHelpText(_("Input"));

	bitmapOutput = new wxStaticBitmap(this, ID_BITMAPOUTPUT, wxNullBitmap, wxPoint(320, 16), wxSize(300, 300) );
	bitmapOutput->SetToolTip(_("Output"));

	buttonInsertImage = new wxButton(this, ID_BUTTONINSERTIMAGE, _("Insert Image"), wxPoint(632, 16), wxSize(125, 28), 0, wxDefaultValidator, _("buttonInsertImage"));

	buttonObtainMask = new wxButton(this, ID_BUTTONOBTAINMASK, _("Obtain Mask"), wxPoint(632, 48), wxSize(125, 28), 0, wxDefaultValidator, _("buttonObtainMask"));

	buttonObtainDefects = new wxButton(this, ID_BUTTONOBTAINDEFECTS, _("Count Fingers"), wxPoint(632, 110), wxSize(125, 28), 0, wxDefaultValidator, _("buttonObtainDefects"));

	WxStatusBar1 = new wxStatusBar(this, ID_WXSTATUSBAR1);

	buttonSaveImage = new wxButton(this, ID_BUTTONSAVEIMAGE, _("Save Image"), wxPoint(633, 143), wxSize(125, 28), 0, wxDefaultValidator, _("buttonSaveImage"));

	buttonGetContour = new wxButton(this, ID_BUTTONGETCONTOUR, _("Get Contour"), wxPoint(632, 79), wxSize(125, 28), 0, wxDefaultValidator, _("buttonGetContour"));

	WxStaticText1 = new wxStaticText(this, ID_WXSTATICTEXT1, _("x-coordinate"), wxPoint(8, 324), wxDefaultSize, 0, _("WxStaticText1"));

	WxStaticText2 = new wxStaticText(this, ID_WXSTATICTEXT2, _("y-coordinate"), wxPoint(8, 344), wxDefaultSize, 0, _("WxStaticText2"));

	WxStaticText3 = new wxStaticText(this, ID_WXSTATICTEXT3, _("Side Length"), wxPoint(11, 370), wxDefaultSize, 0, _("WxStaticText3"));

	buttonCropImage = new wxButton(this, ID_BUTTONCROPIMAGE, _("Crop Image"), wxPoint(248, 352), wxSize(75, 25), 0, wxDefaultValidator, _("buttonCropImage"));

	WxEdit1 = new wxTextCtrl(this, ID_WXEDIT1, _("0"), wxPoint(83, 322), wxSize(121, 19), 0, wxDefaultValidator, _("WxEdit1"));

	WxEdit2 = new wxTextCtrl(this, ID_WXEDIT2, _("0"), wxPoint(83, 346), wxSize(121, 19), 0, wxDefaultValidator, _("WxEdit2"));

	WxEdit3 = new wxTextCtrl(this, ID_WXEDIT3, _("999"), wxPoint(82, 368), wxSize(121, 19), 0, wxDefaultValidator, _("WxEdit3"));

	dialogChooseImage =  new wxFileDialog(this, _("Choose a file"), _(""), _(""), _("*.bmp*"), wxFD_OPEN);

	dialogSaveImage =  new wxFileDialog(this, _("Choose a file"), _(""), _(""), _("*.bmp*"), wxFD_SAVE);

	SetStatusBar(WxStatusBar1);
	SetTitle(_("Finger Counting"));
	SetIcon(wxNullIcon);
	SetSize(8,8,779,469);
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

int orientation(int p_x, int p_y, int q_x, int q_y, int r_x, int r_y)
{ 
    int val = (q_y - p_y) * (r_x - q_x) - 
              (q_x - p_x) * (r_y - q_y); 
  
    if (val == 0) return 0;  // colinear 
    return (val > 0)? 1: 2; // clock or counterclock wise 
} 

void maskLeftmostPixel (wxImage image, int& x_start, int& y_start)
{
    int height = image.GetHeight();
    int width = image.GetWidth();
    bool stop = false;
    
    
    // we need to start at the bottom left (y = max, x = 0)
    for (int y = height-1; y >= 0; y--)
    {
        for (int x = 0; x < width; x++)
        {
            int red = (image.GetRed(x, y));
            int green = (image.GetGreen(x, y));
            int blue = (image.GetBlue(x, y));
            if (red == 0 && green == 0 && blue == 0)
            {
                x_start = x;
                y_start = y;
                stop = true;
                break;
            }
        }
        if (stop)
            break;
    }
            
}

void maskClockwise (int bx, int by, int px, int py, int& cx, int& cy)
{
    int x_change = px - bx;
    int y_change = py - by;
    cx = bx;
    cy = by;
    
    if (x_change == 0)
    {
        cx += y_change;
    }
    else
    {
        if (y_change == x_change)
            cx += y_change;
        else
            cy -= x_change;
    }
}

/*****************************************
EVENTS
*******************************************/
bool openImageFlag = false;

/*
 * buttonInsertImageClick
 */
void fingerCountv3Frm::buttonInsertImageClick(wxCommandEvent& event)
{
	// initializing requisite variables
    
    REDLowerThreshold = 141;
    REDUpperThreshold = 255;
    
    GREENLowerThreshold = 85;
    GREENUpperThreshold = 197;
    
    BLUELowerThreshold = 50;
    BLUEUpperThreshold = 190;
    
    //Cropping Information
    xcoordinate = 0;
    ycoordinate = 0;
    sidelength = 1001;
    
    
    dialogChooseImage->ShowModal(); // pops open the choose image dialog
	
    if (dialogChooseImage -> GetPath().IsEmpty())
	   return;
	
	openImageFlag = input.LoadFile(dialogChooseImage->GetPath(), wxBITMAP_TYPE_ANY);
	
	scaledinput = input.Scale(1000,1000);
	
    bitmapInput->SetBitmap(scaledinput.Scale(300,300));
    
}

/*
 * buttonObtainDefectsClick
 */
void fingerCountv3Frm::buttonObtainDefectsClick(wxCommandEvent& event)
{
    if (openImageFlag)
    {
    	
    }

    else
    {
         wxMessageBox
        ("No Image Selected :(",_T("Image"),wxOK | wxICON_EXCLAMATION, this);
    }
}

/*
 * buttonSaveImageClick
 */
void fingerCountv3Frm::buttonSaveImageClick(wxCommandEvent& event)
{
	if (openImageFlag)
      {
        wxString filename;
        dialogSaveImage->SetFilename(filename);
        
        if (dialogSaveImage->ShowModal() == wxID_OK) // If the user clicked "OK"
        {
          wxInitAllImageHandlers();
          wxString Path = dialogSaveImage->GetPath();
          contourBMP.SaveFile(Path);
        }
        else
        {
          dialogSaveImage->Close(); 
        }
      }
    else
    {
        wxMessageBox("No Image Selected :(",_T("Image"),wxOK | wxICON_EXCLAMATION, this);
    }
}

/*
 * buttonGetContourClick
 */
void fingerCountv3Frm::buttonGetContourClick(wxCommandEvent& event)
{
	if (openImageFlag)
    {
        // CHANGE THIS BACK TO MASKBMP AFTER DEBUGGING IS OVER
        
        int height = maskBMP.GetHeight();
        int width = maskBMP.GetWidth();
        
        // variables needed for moore's
        int mask_start_x, mask_start_y;
        int b_x, b_y;
        int p_x, p_y;
        int c_x, c_y;
        vector<int>mask_x;
        vector<int>mask_y;
        
        
        contourBMP.Create(width, height);
        bg.Create(width, height);
        contourBMP.Clear(255);
        bg.Clear(255);
        
        contourBMP = maskBMP;
        
        // adding a buffer
        for (int y = 0; y < height; y ++)
        {
            for (int x = 0; x < width; x ++)
            {
                if (x==0||y==0||x==width-1||y==height-1)
                    contourBMP.SetRGB(x, y, 255, 255, 255);
            }
        }
        
        // finding the bottom-left most black pixel
        maskLeftmostPixel(contourBMP, mask_start_x, mask_start_y);
        mask_x.push_back(mask_start_x);
        mask_y.push_back(mask_start_y);
        contourBMP.SetRGB(mask_start_x, mask_start_y, 255, 0, 0);
        
        wxString answer = wxString::Format(wxT("%i"), mask_start_x);
        wxMessageBox("x coordinate: " + answer);
        answer = wxString::Format(wxT("%i"), mask_start_y);
        wxMessageBox("y coordinate: " + answer);
        
        p_x = mask_start_x;
        p_y = mask_start_y;
        
        b_x = mask_start_x - 1;
        b_y = mask_start_y;
        
        maskClockwise(b_x, b_y, p_x, p_y, c_x, c_y);
        
        answer = wxString::Format(wxT("%i"), c_x);
        wxMessageBox("c_x: " + answer);
        answer = wxString::Format(wxT("%i"), c_y);
        wxMessageBox("c_y: " + answer);
        
        bool test = false;
        
        while (c_x != mask_start_x && c_y != mask_start_y)
        {
            
            int red = (contourBMP.GetRed(c_x, c_y));
            int green = (contourBMP.GetGreen(c_x, c_y));
            int blue = (contourBMP.GetBlue(c_x, c_y));
            
            if (red != 255 && green != 255 && blue != 255)
            {
                mask_x.push_back(c_x);
                mask_y.push_back(c_y);
                contourBMP.SetRGB(c_x, c_y, 255, 0, 0);
                b_x = p_x;
                b_y = p_y;
                p_x = c_x;
                p_y = c_y;
                maskClockwise(b_x, b_y, p_x, p_y, c_x, c_y);
            }
            else
            {
                b_x = c_x;
                b_y = c_y;
                maskClockwise(b_x, b_y, p_x, p_y, c_x, c_y);
                if (!test)
                {
                    test = true;
                    wxMessageBox("red val = " + wxString::Format(wxT("%i"), c_x));
                }
            }
        }
        
        answer = wxString::Format(wxT("%i"), mask_x.size());
        wxMessageBox("number of contour points: " + answer);
        
        // display
        if (300 >= (height*300/width))
        {
            bitmapOutput->SetBitmap(bg.Scale(300, height*300/width));
            bitmapOutput->SetBitmap(contourBMP.Scale(300, height * 300 / width));
        }
        else
        {
            bitmapOutput->SetBitmap(bg.Scale(300*width/height, 300));
            bitmapOutput->SetBitmap(contourBMP.Scale(width*300/height, 300));
            
        }
    }
    else
    {
        wxMessageBox
        ("No Image Selected :(",_T("Image"),wxOK | wxICON_EXCLAMATION, this);
    }
}

/*
 * fingerCountv3FrmActivate
 */
void fingerCountv3Frm::fingerCountv3FrmActivate(wxActivateEvent& event)
{
	// insert your code here
}

/*
 * buttonGetHullClick
 */
void fingerCountv3Frm::buttonGetHullClick(wxCommandEvent& event)
{
    
}

/*
 * buttonObtainMaskImageClick
 */
void fingerCountv3Frm::buttonObtainMaskClick(wxCommandEvent& event)
{
    int R;
    int G;
    int B;
    
        
    maskBMP.Create(300,300);
        
    cropBMP = cropcanvas.Scale(300,300);
        
    for(int row=0; row<=299; row++)
    {
        for(int col=0; col<=299; col++)
        {
            R = cropBMP.GetRed(col,row);
            G = cropBMP.GetGreen(col,row);
            B = cropBMP.GetBlue(col,row);
            
            // change the 2nd bound to < when DEBUGGING is over
            if(R>REDLowerThreshold && R<REDUpperThreshold && G>GREENLowerThreshold && G<GREENUpperThreshold && B>BLUELowerThreshold && B<BLUEUpperThreshold)
            {
                maskBMP.SetRGB(col,row,0,0,0);
            }
            else
            {
                maskBMP.SetRGB(col,row,255,255,255);
            }
        } 
    }           
        bitmapOutput->SetBitmap(maskBMP.Scale(300,300));               
                           
}

/*
 * buttonCropImageClick
 */
void fingerCountv3Frm::buttonCropImageClick(wxCommandEvent& event)
{
    int R;
    int G;
    int B;
    int inputwidth;
    int inputheight;
    
    //WxEdit1->GetValue().ToDouble(&xcoordinate);
    //WxEdit2->GetValue().ToDouble(&ycoordinate);
    //WxEdit3->GetValue().ToDouble(&sidelength);
    
    cropcanvas.Create(sidelength,sidelength);
    cropcanvas.Clear(255);
    
    if(xcoordinate+sidelength<=1000)
    {
        for(int row=0; row<sidelength; row++)
        {
            for(int col=0; col<sidelength; col++)
            {
                 R = scaledinput.GetRed(xcoordinate+col,ycoordinate+row);
                 G = scaledinput.GetGreen(xcoordinate+col,ycoordinate+row);
                 B = scaledinput.GetBlue(xcoordinate+col,ycoordinate+row);   
                cropcanvas.SetRGB(col,row,R,G,B);            
            }
        }
    
        bitmapOutput->SetBitmap(cropcanvas.Scale(300,300));      
    }
    else
    {
        bitmapOutput->SetBitmap(cropcanvas.Scale(300,300));
        
    }
    

}

/*
 * WxEdit1Updated0
 */
void fingerCountv3Frm::WxEdit1Updated0(wxCommandEvent& event)
{
	// insert your code here
	WxEdit1->GetValue().ToDouble(&xcoordinate);
    WxEdit2->GetValue().ToDouble(&ycoordinate);
    WxEdit3->GetValue().ToDouble(&sidelength);
}

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

	WxEdit3 = new wxTextCtrl(this, ID_WXEDIT3, _("1000"), wxPoint(82, 368), wxSize(121, 19), 0, wxDefaultValidator, _("WxEdit3"));

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
    	int height = contourBMP.GetHeight();
        int width = contourBMP.GetWidth();
        
        convexBMP.Create(width, height);
        bg.Create(width, height);
        convexBMP.Clear(255);
        bg.Clear(255);
        
        // obtain all the points from the contour
        
        vector<int> contour_x;
        vector<int> contour_y;
        int smol_x = width+1, chunky_x = 0;
        int smol_x_element, chunky_x_element;
        int smol_y = height+1, chunky_y = 0;
        int smol_y_element, chunky_y_element;
        for (int y = 1; y < height-1; y++)
        {
            for (int x = 1; x < width-1; x++)
            {
                int red = (contourBMP.GetRed(x, y));
                int green = (contourBMP.GetGreen(x, y));
                int blue = (contourBMP.GetBlue(x, y));
                if (red==255 && green == 0 && blue == 0)
                {
                    if (x < smol_x)
                    {
                        smol_x = x;
                        smol_x_element = contour_x.size();
                    }
                    else if (x > chunky_x)
                    {
                        chunky_x = x;
                        chunky_x_element = contour_x.size();
                    }
                    if (y < smol_y)
                    {
                        smol_y = y;
                        smol_y_element = contour_y.size();
                    }
                    else if (y > chunky_y)
                    {
                        chunky_y = y;
                        chunky_y_element = contour_y.size();
                    }
                    contour_x.push_back(x);
                    contour_y.push_back(y);
                    convexBMP.SetRGB(x, y, 255, 0, 255);
                }
            }
        }
        /*******************convex hull****************************************
        // left line
        for (int y = smol_y; y <= chunky_y; y++)
            convexBMP.SetRGB(smol_x, y, 0, 0, 255);
        
        // top line
        for (int x = smol_x; x <= chunky_x; x++)
            convexBMP.SetRGB(x, smol_y, 0, 0, 255);
        
        // right line
        for (int y = smol_y; y <= chunky_y; y++)
            convexBMP.SetRGB(chunky_x, y, 0, 0, 255);
        
        // bottom line
        for (int x = smol_x; x <= chunky_x; x++)
            convexBMP.SetRGB(x, chunky_y, 0, 0, 255);
        **********************************************************************/
        
        // measure the distance from the left to the contour-------------------
        
        // change these thresholds if there are false positives
        //int min_defect_dist = (int)(0.4*height);
       // int max_defect_dist = (int)(0.8*height);
        //int finger_width = (int)(0.1*width);
        int defect_threshold = (int)(width*0.05);
        int y0_length = 0;
        int y_new_length = 0;
        int defects_count = 1; // middle finger
        int end_of_line = 0;
        
        // initializing y0_length
        for (int x = 0; x < width; x++)
        {
            int red = (contourBMP.GetRed(x, chunky_y));
            int green = (contourBMP.GetGreen(x, chunky_y));
            int blue = (contourBMP.GetBlue(x, chunky_y));
            
            if (red == 255 && green == 0 && blue == 0)
                break;
            else
                y0_length++;
        }
        
        
        for (int y = chunky_y-1; y >= smol_y; y--)
        {
            // obtain length for curr line
            for (int x = 0; x < width; x++)
            {
                int red = (contourBMP.GetRed(x, y));
                int green = (contourBMP.GetGreen(x, y));
                int blue = (contourBMP.GetBlue(x, y));
                
                if (red == 255 && green == 0 && blue == 0)
                {
                    end_of_line = x;
                    break;
                }
                else
                    y_new_length++;
            }
                
            // compare to prev length
                // diff too large? defect++
                // else continue
            if (abs(y_new_length-y0_length) > defect_threshold)
            {
                defects_count++;
                for (int x = 0; x < end_of_line; x++)
                    convexBMP.SetRGB(x, y, 0, 255, 0);
            }
        
            // prev length = curr length
            y0_length = y_new_length;
            y_new_length = 0;
        }
        
        
        // right limit to contour----------------------------------------------
        
        y0_length = 0;
        y_new_length = 0;
        
        // initializing y0_length
        for (int x = width; x >= 0; x--)
        {
            int red = (contourBMP.GetRed(x, chunky_y-9));
            int green = (contourBMP.GetGreen(x, chunky_y-9));
            int blue = (contourBMP.GetBlue(x, chunky_y-9));
            
            if (red == 255 && green == 0 && blue == 0)
                break;
            else
                y0_length++;
        }
        
        for (int y = chunky_y-10; y >= smol_y; y--)
        {
            // obtain length for curr line
            for (int x = width; x > 0; x--)
            {
                int red = (contourBMP.GetRed(x, y));
                int green = (contourBMP.GetGreen(x, y));
                int blue = (contourBMP.GetBlue(x, y));
                
                if (red == 255 && green == 0 && blue == 0)
                {
                    end_of_line = x;
                    break;
                }
                else
                    y_new_length++;
            }
                
            // compare to prev length
                // diff too large? defect++
                // else continue
            if (abs(y_new_length-y0_length) > defect_threshold)
            {
                defects_count++;
                for (int x = width; x > end_of_line; x--)
                    convexBMP.SetRGB(x, y, 0, 255, 255);
            }
        
            // prev length = curr length
            y0_length = y_new_length;
            y_new_length = 0;
        }
        
        // displaying the answer------------------------------------------------
        wxString answer = wxString::Format(wxT("%i"), defects_count);
        wxMessageBox("The number of fingers being held up is: " + answer);
        
        if (300 >= (height*300/width))
        {
            bitmapOutput->SetBitmap(bg.Scale(300, height*300/width));
            bitmapOutput->SetBitmap(convexBMP.Scale(300, height * 300 / width));
        }
        else
        {
            bitmapOutput->SetBitmap(bg.Scale(300*width/height, 300));
            bitmapOutput->SetBitmap(convexBMP.Scale(width*300/height, 300));
        }
        
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
          convexBMP.SaveFile(Path);
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
        int height = maskBMP.GetHeight();
        int width = maskBMP.GetWidth();
        
        contourBMP.Create(width, height);
        bg.Create(width, height);
        contourBMP.Clear(255);
        bg.Clear(255);
        
        
        // top to bottom
        for (int x = 1; x < width-1; x++) 
        {
            for (int y = 1; y < height-1; y++)
            {
                int red = (maskBMP.GetRed(x,y));
                int green = (maskBMP.GetGreen(x,y));
                int blue = (maskBMP.GetBlue(x,y));
                
                if (red == 0 && green == 0 && blue == 0)
                {
                    contourBMP.SetRGB(x, y, 255, 0, 0);
                    // scans right after hitting boundary point
                    for (int i = x+1; i < width-1; i++)
                    {
                        int red = (maskBMP.GetRed(i, y));
                        int green = (maskBMP.GetGreen(i, y));
                        int blue = (maskBMP.GetBlue(i, y));
                        
                        if (red == 0 && green == 0 && blue == 0)
                        {
                            contourBMP.SetRGB(i, y, 255, 0, 0);
                            
                            // scans up after going right
                            for (int j = y-1; j > 0; j--)
                            {
                                int red = (maskBMP.GetRed(i, j));
                                int green = (maskBMP.GetGreen(i, j));
                                int blue = (maskBMP.GetBlue(i, j));
                                
                                if (red == 0 && green == 0 && blue == 0)
                                {
                                    contourBMP.SetRGB(i, j, 255, 0, 0);
                                    break;
                                }
                            } 
                            
                            break;
                        }
                        
                    }
                    
                    // scans left after hittign boundary point
                    for (int i = x-1; i >0; i--)
                    {
                        int red = (maskBMP.GetRed(i, y));
                        int green = (maskBMP.GetGreen(i, y));
                        int blue = (maskBMP.GetBlue(i, y));
                        
                        if (red == 0 && green == 0 && blue == 0)
                        {
                            contourBMP.SetRGB(i, y, 255, 0, 0);
                            
                            // scans up after going left
                            for (int j = y-1; j > 0; j--)
                            {
                                int red = (maskBMP.GetRed(i, j));
                                int green = (maskBMP.GetGreen(i, j));
                                int blue = (maskBMP.GetBlue(i, j));
                                
                                if (red == 0 && green == 0 && blue == 0)
                                {
                                    contourBMP.SetRGB(i, j, 255, 0, 0);
                                    break;
                                }
                            } 
                            
                            break;
                        }
                        
                    }
                    break;
                }
                   
            }
        }
        
        // left to right
        for (int y = 1; y < height-1; y++) 
        {
            for (int x = 1; x < width-1; x++)
            {
                int red = (maskBMP.GetRed(x,y));
                int green = (maskBMP.GetGreen(x,y));
                int blue = (maskBMP.GetBlue(x,y));
                
                if (red == 0 && green == 0 && blue == 0)
                {
                    contourBMP.SetRGB(x, y, 255, 0, 0);
                    
                    // this scans downward after hitting a boundary point
                    for (int i = y+1; i < height-1; i++)
                    {
                        int red = (maskBMP.GetRed(x,i));
                        int green = (maskBMP.GetGreen(x,i));
                        int blue = (maskBMP.GetBlue(x,i));
                        
                        if (red == 0 && green == 0 && blue == 0)
                        {
                            contourBMP.SetRGB(x, i, 255, 0, 0);
                            break;
                        }
                        
                    }
                    
                    // this scans upwards after hitting a boundary point
                    for (int i = y-1; i >0; i--)
                    {
                        int red = (maskBMP.GetRed(x,i));
                        int green = (maskBMP.GetGreen(x,i));
                        int blue = (maskBMP.GetBlue(x,i));
                        
                        if (red == 0 && green == 0 && blue == 0)
                        {
                            contourBMP.SetRGB(x, i, 255, 0, 0);
                            break;
                        }
                        
                    }
                    break;
                }
            }
        }
        // right to left
        for (int y = 1; y < height-1; y++) 
        {
            for (int x = width-1; x > 0; x--)
            {
                int red = (maskBMP.GetRed(x,y));
                int green = (maskBMP.GetGreen(x,y));
                int blue = (maskBMP.GetBlue(x,y));
                
                if (red == 0 && green == 0 && blue == 0)
                {
                    contourBMP.SetRGB(x, y, 255, 0, 0);
                    
                    // scan down
                    for (int i = y+1; i < height-1; i++)
                    {
                        int red = (maskBMP.GetRed(x,i));
                        int green = (maskBMP.GetGreen(x,i));
                        int blue = (maskBMP.GetBlue(x,i));
                        
                        if (red == 0 && green == 0 && blue == 0)
                        {
                            contourBMP.SetRGB(x, i, 255, 0, 0);
                            break;
                        }
                        
                    }
                    
                    // this scans upwards after hitting a boundary point
                    for (int i = y-1; i >0; i--)
                    {
                        int red = (maskBMP.GetRed(x,i));
                        int green = (maskBMP.GetGreen(x,i));
                        int blue = (maskBMP.GetBlue(x,i));
                        
                        if (red == 0 && green == 0 && blue == 0)
                        {
                            contourBMP.SetRGB(x, i, 255, 0, 0);
                            break;
                        }
                        
                    }
                    break;
                }
                   
            }
        }
        
        // bottom to top
        for (int x = 1; x < width-1; x++) 
        {
            for (int y = height-1; y > 0; y--)
            {
                int red = (maskBMP.GetRed(x,y));
                int green = (maskBMP.GetGreen(x,y));
                int blue = (maskBMP.GetBlue(x,y));
                
                if (red == 0 && green == 0 && blue == 0)
                {
                    contourBMP.SetRGB(x, y, 255, 0, 0);
                    
                    // scans right after hitting boundary point
                    for (int i = x+1; i < width-1; i++)
                    {
                        int red = (maskBMP.GetRed(i, y));
                        int green = (maskBMP.GetGreen(i, y));
                        int blue = (maskBMP.GetBlue(i, y));
                        
                        if (red == 0 && green == 0 && blue == 0)
                        {
                            contourBMP.SetRGB(i, y, 255, 0, 0);
                            // scans down after going right
                            for (int j = y+1; j < height-1; j++)
                            {
                                int red = (maskBMP.GetRed(i, j));
                                int green = (maskBMP.GetGreen(i, j));
                                int blue = (maskBMP.GetBlue(i, j));
                                
                                if (red == 0 && green == 0 && blue == 0)
                                {
                                    contourBMP.SetRGB(i, j, 255, 0, 0);
                                    break;
                                }
                            } //
                            break;
                        }
                        
                    }
                    
                    // scans left after hittign boundary point
                    for (int i = x-1; i >0; i--)
                    {
                        int red = (maskBMP.GetRed(i, y));
                        int green = (maskBMP.GetGreen(i, y));
                        int blue = (maskBMP.GetBlue(i, y));
                        
                        if (red == 0 && green == 0 && blue == 0)
                        {
                            contourBMP.SetRGB(i, y, 255, 0, 0);
                            // scans down after going left
                            for (int j = y+1; j < height-1; j++)
                            {
                                int red = (maskBMP.GetRed(i, j));
                                int green = (maskBMP.GetGreen(i, j));
                                int blue = (maskBMP.GetBlue(i, j));
                                
                                if (red == 0 && green == 0 && blue == 0)
                                {
                                    contourBMP.SetRGB(i, j, 255, 0, 0);
                                    break;
                                }
                            }//
                            break;
                        }
                        
                    }
                    break;
                }
                   
            }
        }
        
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

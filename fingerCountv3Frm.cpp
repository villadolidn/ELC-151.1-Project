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
	EVT_BUTTON(ID_BUTTONGETHULL,fingerCountv3Frm::buttonGetHullClick)
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

	buttonObtainDefects = new wxButton(this, ID_BUTTONOBTAINDEFECTS, _("Count Fingers"), wxPoint(632, 144), wxSize(125, 28), 0, wxDefaultValidator, _("buttonObtainDefects"));

	labelFingerCount = new wxStaticText(this, ID_LABELFINGERCOUNT, _("Number of Fingers..."), wxPoint(640, 208), wxDefaultSize, 0, _("labelFingerCount"));

	WxStatusBar1 = new wxStatusBar(this, ID_WXSTATUSBAR1);

	buttonSaveImage = new wxButton(this, ID_BUTTONSAVEIMAGE, _("Save Image"), wxPoint(632, 176), wxSize(125, 28), 0, wxDefaultValidator, _("buttonSaveImage"));

	buttonGetContour = new wxButton(this, ID_BUTTONGETCONTOUR, _("Get Contour"), wxPoint(632, 76), wxSize(125, 28), 0, wxDefaultValidator, _("buttonGetContour"));

	buttonGetHull = new wxButton(this, ID_BUTTONGETHULL, _("Get Hull"), wxPoint(632, 112), wxSize(125, 28), 0, wxDefaultValidator, _("buttonGetHull"));

	dialogChooseImage =  new wxFileDialog(this, _("Choose a file"), _(""), _(""), _("*.bmp*"), wxFD_OPEN);

	dialogSaveImage =  new wxFileDialog(this, _("Choose a file"), _(""), _(""), _("*.bmp*"), wxFD_SAVE);

	SetStatusBar(WxStatusBar1);
	SetTitle(_("Finger Counting"));
	SetIcon(wxNullIcon);
	SetSize(8,8,793,406);
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
    return (val > 0)? 2: 1; // clock or counterclock wise 
} 



/*****************************************
EVENTS
*******************************************/

/*
 * buttonInsertImageClick
 */
 
wxImage input;
wxImage maskBMP;
wxImage contourBMP;
wxImage convexBMP;
wxImage defectsBMP;
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
	bg.Clear(255);  // white bucket tool	
    
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
        int height = input.GetHeight();
        int width = input.GetWidth();
        
        contourBMP.Create(width, height);
        bg.Create(width, height);
        contourBMP.Clear(255);
        bg.Clear(255);
        
        
        // top to bottom
        for (int x = 1; x < width-1; x++) 
        {
            for (int y = 1; y < height-1; y++)
            {
                int red = (input.GetRed(x,y));
                int green = (input.GetGreen(x,y));
                int blue = (input.GetBlue(x,y));
                
                if (red == 0 && green == 0 && blue == 0)
                {
                    contourBMP.SetRGB(x, y, 255, 0, 0);
                    // scans right after hitting boundary point
                    for (int i = x+1; i < width-1; i++)
                    {
                        int red = (input.GetRed(i, y));
                        int green = (input.GetGreen(i, y));
                        int blue = (input.GetBlue(i, y));
                        
                        if (red == 0 && green == 0 && blue == 0)
                        {
                            contourBMP.SetRGB(i, y, 255, 0, 0);
                            
                            // scans up after going right
                            for (int j = y-1; j > 0; j--)
                            {
                                int red = (input.GetRed(i, j));
                                int green = (input.GetGreen(i, j));
                                int blue = (input.GetBlue(i, j));
                                
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
                        int red = (input.GetRed(i, y));
                        int green = (input.GetGreen(i, y));
                        int blue = (input.GetBlue(i, y));
                        
                        if (red == 0 && green == 0 && blue == 0)
                        {
                            contourBMP.SetRGB(i, y, 255, 0, 0);
                            
                            // scans up after going left
                            for (int j = y-1; j > 0; j--)
                            {
                                int red = (input.GetRed(i, j));
                                int green = (input.GetGreen(i, j));
                                int blue = (input.GetBlue(i, j));
                                
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
                int red = (input.GetRed(x,y));
                int green = (input.GetGreen(x,y));
                int blue = (input.GetBlue(x,y));
                
                if (red == 0 && green == 0 && blue == 0)
                {
                    contourBMP.SetRGB(x, y, 255, 0, 0);
                    
                    // this scans downward after hitting a boundary point
                    for (int i = y+1; i < height-1; i++)
                    {
                        int red = (input.GetRed(x,i));
                        int green = (input.GetGreen(x,i));
                        int blue = (input.GetBlue(x,i));
                        
                        if (red == 0 && green == 0 && blue == 0)
                        {
                            contourBMP.SetRGB(x, i, 255, 0, 0);
                            
                            /*scans left after down
                            for (int j = x-1; j > 0; j--)
                            {
                                int red = (input.GetRed(i, j));
                                int green = (input.GetGreen(i, j));
                                int blue = (input.GetBlue(i, j));
                                
                                if (red == 0 && green == 0 && blue == 0)
                                {
                                    contourBMP.SetRGB(i, j, 255, 0, 0);
                                    break;
                                }
                            }*/
                            break;
                        }
                        
                    }
                    
                    // this scans upwards after hitting a boundary point
                    for (int i = y-1; i >0; i--)
                    {
                        int red = (input.GetRed(x,i));
                        int green = (input.GetGreen(x,i));
                        int blue = (input.GetBlue(x,i));
                        
                        if (red == 0 && green == 0 && blue == 0)
                        {
                            contourBMP.SetRGB(x, i, 255, 0, 0);
                            /*scan left after up
                            for (int j = x-1; j > 0; j--)
                            {
                                int red = (input.GetRed(i, j));
                                int green = (input.GetGreen(i, j));
                                int blue = (input.GetBlue(i, j));
                                
                                if (red == 0 && green == 0 && blue == 0)
                                {
                                    contourBMP.SetRGB(i, j, 255, 0, 0);
                                    break;
                                }
                            }*/
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
                int red = (input.GetRed(x,y));
                int green = (input.GetGreen(x,y));
                int blue = (input.GetBlue(x,y));
                
                if (red == 0 && green == 0 && blue == 0)
                {
                    contourBMP.SetRGB(x, y, 255, 0, 0);
                    
                    // scan down
                    for (int i = y+1; i < height-1; i++)
                    {
                        int red = (input.GetRed(x,i));
                        int green = (input.GetGreen(x,i));
                        int blue = (input.GetBlue(x,i));
                        
                        if (red == 0 && green == 0 && blue == 0)
                        {
                            contourBMP.SetRGB(x, i, 255, 0, 0);
                            
                            /*scan right after down BUG BUG BUG
                            for (int j = x; j < width -1; j++)
                            {
                                int red = (input.GetRed(i, j));
                                int green = (input.GetGreen(i, j));
                                int blue = (input.GetBlue(i, j));
                                
                                if (red == 0 && green == 0 && blue == 0)
                                {
                                    contourBMP.SetRGB(i, j, 255, 0, 0);
                                    break;
                                }
                            }*/
                            break;
                        }
                        
                    }
                    
                    // this scans upwards after hitting a boundary point
                    for (int i = y-1; i >0; i--)
                    {
                        int red = (input.GetRed(x,i));
                        int green = (input.GetGreen(x,i));
                        int blue = (input.GetBlue(x,i));
                        
                        if (red == 0 && green == 0 && blue == 0)
                        {
                            contourBMP.SetRGB(x, i, 255, 0, 0);
                            
                            /*scan right after up
                            for (int j = x+1; j < width -1; j++)
                            {
                                int red = (input.GetRed(i, j));
                                int green = (input.GetGreen(i, j));
                                int blue = (input.GetBlue(i, j));
                                
                                if (red == 0 && green == 0 && blue == 0)
                                {
                                    contourBMP.SetRGB(i, j, 255, 0, 0);
                                    break;
                                }
                            }*/
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
                int red = (input.GetRed(x,y));
                int green = (input.GetGreen(x,y));
                int blue = (input.GetBlue(x,y));
                
                if (red == 0 && green == 0 && blue == 0)
                {
                    contourBMP.SetRGB(x, y, 255, 0, 0);
                    
                    // scans right after hitting boundary point
                    for (int i = x+1; i < width-1; i++)
                    {
                        int red = (input.GetRed(i, y));
                        int green = (input.GetGreen(i, y));
                        int blue = (input.GetBlue(i, y));
                        
                        if (red == 0 && green == 0 && blue == 0)
                        {
                            contourBMP.SetRGB(i, y, 255, 0, 0);
                            // scans down after going right
                            for (int j = y+1; j < height-1; j++)
                            {
                                int red = (input.GetRed(i, j));
                                int green = (input.GetGreen(i, j));
                                int blue = (input.GetBlue(i, j));
                                
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
                        int red = (input.GetRed(i, y));
                        int green = (input.GetGreen(i, y));
                        int blue = (input.GetBlue(i, y));
                        
                        if (red == 0 && green == 0 && blue == 0)
                        {
                            contourBMP.SetRGB(i, y, 255, 0, 0);
                            // scans down after going left
                            for (int j = y+1; j < height-1; j++)
                            {
                                int red = (input.GetRed(i, j));
                                int green = (input.GetGreen(i, j));
                                int blue = (input.GetBlue(i, j));
                                
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
    if (openImageFlag)
    {
    	int height = input.GetHeight();
        int width = input.GetWidth();
        
        convexBMP.Create(width, height);
        bg.Create(width, height);
        convexBMP.Clear(255);
        bg.Clear(255);
        
        // obtain all the points from the contour
        
        vector<int> contour_x;
        vector<int> contour_y;
        int smol_x = width+1;
        int smol_x_element;
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
                    contour_x.push_back(x);
                    contour_y.push_back(y);
                    convexBMP.SetRGB(x, y, 255, 0, 255);
                }
            }
        }
        convexBMP.SetRGB(smol_x, contour_y[smol_x_element], 0, 255, 255);
        
        
        wxString debug1 = wxString::Format(wxT("%i"), smol_x);
        wxMessageBox(debug1);
        
        wxString debug4 = wxString::Format(wxT("%i"), contour_x[smol_x_element]);
        wxMessageBox(debug4);
        
        int n = contour_x.size();
        
        vector<int> convex_x;
        vector<int> convex_y;
        
        //Jarvis' Algorithm
            
        // Obtain element containing the leftmost point
        int l = smol_x_element;
        wxString debug2 = wxString::Format(wxT("%i"), l);
        wxMessageBox(debug2);
        
        wxString debug3 = wxString::Format(wxT("%i"), contour_x[l]);
        wxMessageBox(debug3);
        
        int p = l;
        int q;
        int min_x = 30, min_y = 30, max_x = width-30, max_y = height;
        bool skipFlag = false;
        do
        {
            if (contour_x[p] < min_x || contour_x[p] > max_x || 
                contour_y[p] < min_y || contour_y[p] > max_y)
                skipFlag = true;
            if (!skipFlag)
            {
                convex_x.push_back(contour_x[p]);
                convex_y.push_back(contour_y[p]);
            }
            q = (p+1)%n;
            for (int i = 0; i < n; i++)
            {
                if (orientation(contour_x[p], contour_y[p], contour_x[i], 
                contour_y[i], contour_x[q], contour_y[q])==2)
                {
                    q = i;
                }
            }
            
            p = q;
            skipFlag = false;
        } while (p!=l);
        wxMessageBox
        ("Mishon compree",_T("Image"),wxOK | wxICON_EXCLAMATION, this);
        
        // use the points obtained from the algorithm to draw the convex hull
        
        int x = 0, y = 0, x2 = 0, y2 = 0;
        
        for (int i = 1; i < contour_x.size(); i++)
        {
            //shitty exception handler
            if (x < 0 || x > width || y < 0 || y > height)
                continue;
            // variables
            x = convex_x[i-1];
            y = convex_y[i-1];
            x2 = convex_x[i];
            y2 = convex_y[i];
            int rise = y - y2;
            int run = x2 - x;
            if (rise > 0 && run > 0)// decrease y, increase x done
            {
                while(y2 < y)
                {
                    if (x < 0 || x > width || y < 0 || y > height)
                        continue;
                    convexBMP.SetRGB(x, y, 0, 0, 255);
                    y--;
                }
                y+=1;
                while (x2 > x)
                {
                    if (x < 0 || x > width || y < 0 || y > height)
                        continue;
                    convexBMP.SetRGB(x, y, 0, 0, 255);
                    x++;
                }
                    
            }
            else if (rise > 0 && run < 0) // decrease y, decrease x done
            {
                while(y2 < y)
                {
                    if (x < 0 || x > width || y < 0 || y > height)
                        continue;
                    convexBMP.SetRGB(x, y, 0, 0, 255);
                    y--;
                }
                y+=1;
                while (x2 < x)
                {
                    if (x < 0 || x > width || y < 0 || y > height)
                        continue;
                    convexBMP.SetRGB(x, y, 0, 0, 255);
                    x--;
                }
            }
            else if (rise < 0 && run > 0) // increase y, increase x done
            {
                while(y2 > y)
                {
                    if (x < 0 || x > width || y < 0 || y > height)
                        continue;
                    convexBMP.SetRGB(x, y, 0, 0, 255);
                    y++;
                }
                y-=1;
                while (x2 > x)
                {
                    if (x < 0 || x > width || y < 0 || y > height)
                        continue;
                    convexBMP.SetRGB(x, y, 0, 0, 255);
                    x++;
                }
            }
            else if (rise < 0 && run < 0) // increase y, dec x done
            {
                while(y2 > y)
                {
                    if (x < 0 || x > width || y < 0 || y > height)
                        continue;
                    convexBMP.SetRGB(x, y, 0, 0, 255);
                    y++;
                }
                y-=1;
                while (x2 < x)
                {
                    if (x < 0 || x > width || y < 0 || y > height)
                        continue;
                    convexBMP.SetRGB(x, y, 0, 0, 255);
                    x--;
                }
            }
            else if (rise == 0 && run > 0) // only increase x
            {
                while (x2 > x)
                {
                    if (x < 0 || x > width || y < 0 || y > height)
                        continue;
                    convexBMP.SetRGB(x, y, 0, 0, 255);
                    x++;
                }
            }
            else if (rise == 0 && run < 0) // only dec x
            {
                while (x2 < x)
                {
                    if (x < 0 || x > width || y < 0 || y > height)
                        continue;
                    convexBMP.SetRGB(x, y, 0, 0, 255);
                    x--;
                }
            }
            else if (rise < 0 && run == 0) // only increase y
            {
                while(y2 > y)
                {
                    if (x < 0 || x > width || y < 0 || y > height)
                        continue;
                    convexBMP.SetRGB(x, y, 0, 0, 255);
                    y++;
                }
            }
            else if (rise > 0 && run == 0) // only dec y
            {
                while(y2 < y)
                {
                    if (x < 0 || x > width || y < 0 || y > height)
                        continue;
                    convexBMP.SetRGB(x, y, 0, 0, 255);
                    y--;
                }
            }
            else
                continue;
        }    
        // display onto static bitmap
        
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

void fingerCountv3Frm::buttonObtainMaskClick(wxCommandEvent& event)
{
    
}

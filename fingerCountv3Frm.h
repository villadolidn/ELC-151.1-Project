///-----------------------------------------------------------------
///
/// @file      fingerCountv3Frm.h
/// @author    Nathan Villadolid
/// Created:   10/29/2019 9:31:36 PM
/// @section   DESCRIPTION
///            fingerCountv3Frm class declaration
///
///------------------------------------------------------------------

#ifndef __FINGERCOUNTV3FRM_H__
#define __FINGERCOUNTV3FRM_H__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/frame.h>
#else
	#include <wx/wxprec.h>
#endif

//Do not add custom headers between 
//Header Include Start and Header Include End.
//wxDev-C++ designer will remove them. Add custom headers after the block.
////Header Include Start
#include <wx/filedlg.h>
#include <wx/textctrl.h>
#include <wx/stattext.h>
#include <wx/statusbr.h>
#include <wx/button.h>
#include <wx/statbmp.h>
////Header Include End

////Dialog Style Start
#undef fingerCountv3Frm_STYLE
#define fingerCountv3Frm_STYLE wxCAPTION | wxSYSTEM_MENU | wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxCLOSE_BOX
////Dialog Style End

class fingerCountv3Frm : public wxFrame
{
	private:
		void buttonInsertImageClick(wxCommandEvent& event);
		DECLARE_EVENT_TABLE();
		
	public:
		fingerCountv3Frm(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("Finger Counting"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = fingerCountv3Frm_STYLE);
		virtual ~fingerCountv3Frm();
		void buttonObtainDefectsClick(wxCommandEvent& event);
		void buttonObtainMaskClick(wxCommandEvent& event);
		void buttonSaveImageClick(wxCommandEvent& event);
		void buttonGetContourClick(wxCommandEvent& event);
		void fingerCountv3FrmActivate(wxActivateEvent& event);
		void buttonGetHullClick(wxCommandEvent& event);
		void WxButton1Click(wxCommandEvent& event);
		void WxEdit1Updated(wxCommandEvent& event);
		void WxEdit2Updated(wxCommandEvent& event);
		void WxEdit3Updated(wxCommandEvent& event);
		void buttonCropImageClick(wxCommandEvent& event);
		void WxEdit1Updated0(wxCommandEvent& event);
		
	private:
		//Do not add custom control declarations between
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxFileDialog *dialogSaveImage;
		wxFileDialog *dialogChooseImage;
		wxTextCtrl *WxEdit3;
		wxTextCtrl *WxEdit2;
		wxTextCtrl *WxEdit1;
		wxButton *buttonCropImage;
		wxStaticText *WxStaticText3;
		wxStaticText *WxStaticText2;
		wxStaticText *WxStaticText1;
		wxButton *buttonGetContour;
		wxButton *buttonSaveImage;
		wxStatusBar *WxStatusBar1;
		wxButton *buttonObtainDefects;
		wxButton *buttonObtainMask;
		wxButton *buttonInsertImage;
		wxStaticBitmap *bitmapOutput;
		wxStaticBitmap *bitmapInput;
		////GUI Control Declaration End
		
		
		
		//Color Mask Thresholds:

        int REDLowerThreshold;
        int REDUpperThreshold;
        
        int GREENLowerThreshold;
        int GREENUpperThreshold;
        
        int BLUELowerThreshold;
        int BLUEUpperThreshold;
        
        //Cropping Information
        double xcoordinate;
        double ycoordinate;
        double sidelength;
        
        //wxImage Declarations
        wxImage input;
        wxImage scaledinput;
        wxImage maskBMP;
        wxImage cropcanvas;
        wxImage cropBMP;
        wxImage contourBMP;
        wxImage convexBMP;
        wxImage defectsBMP;
        wxImage bg;
        
        //Error image
        int cropready;
        wxImage error;
        
        bool openImageFlag;
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			ID_WXEDIT3 = 1022,
			ID_WXEDIT2 = 1021,
			ID_WXEDIT1 = 1020,
			ID_BUTTONCROPIMAGE = 1019,
			ID_WXSTATICTEXT3 = 1018,
			ID_WXSTATICTEXT2 = 1017,
			ID_WXSTATICTEXT1 = 1016,
			ID_BUTTONGETCONTOUR = 1010,
			ID_BUTTONSAVEIMAGE = 1009,
			ID_WXSTATUSBAR1 = 1007,
			ID_BUTTONOBTAINDEFECTS = 1005,
			ID_BUTTONOBTAINMASK = 1004,
			ID_BUTTONINSERTIMAGE = 1003,
			ID_BITMAPOUTPUT = 1002,
			ID_BITMAPINPUT = 1001,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
		
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
};

#endif

///-----------------------------------------------------------------
///
/// @file      fingerCountFrm.h
/// @author    Nathan Villadolid
/// Created:   10/28/2019 12:49:45 PM
/// @section   DESCRIPTION
///            fingerCountFrm class declaration
///
///------------------------------------------------------------------

#ifndef __FINGERCOUNTFRM_H__
#define __FINGERCOUNTFRM_H__

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
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/statbmp.h>
////Header Include End

////Dialog Style Start
#undef fingerCountFrm_STYLE
#define fingerCountFrm_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxCLOSE_BOX
////Dialog Style End

class fingerCountFrm : public wxFrame
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		fingerCountFrm(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("Finger Counting"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = fingerCountFrm_STYLE);
		virtual ~fingerCountFrm();
		void buttonSelectImageClick(wxCommandEvent& event);
		
	private:
		//Do not add custom control declarations between
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxFileDialog *WxOpenFileDialog1;
		wxStaticText *actualFingerCount;
		wxStaticText *labelFingerCount;
		wxStaticText *actualDefectCount;
		wxStaticText *labelDefectCount;
		wxButton *buttonCountFingers;
		wxButton *buttonThreshold;
		wxButton *buttonSelectImage;
		wxStaticBitmap *bitmapDefects;
		wxStaticBitmap *bitmapThreshold;
		wxStaticBitmap *bitmapOriginal;
		wxStaticBitmap *WxStaticBitmap2;
		////GUI Control Declaration End
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			ID_ACTUALFINGERCOUNT = 1013,
			ID_LABELFINGERCOUNT = 1012,
			ID_ACTUALDEFECTCOUNT = 1011,
			ID_LABELDEFECTCOUNT = 1010,
			ID_BUTTONCOUNTFINGERS = 1009,
			ID_BUTTONTHRESHOLD = 1008,
			ID_BUTTONSELECTIMAGE = 1007,
			ID_BITMAPDEFECTS = 1005,
			ID_BITMAPTHRESHOLD = 1004,
			ID_BITMAPORIGINAL = 1003,
			ID_WXSTATICBITMAP2 = 1002,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
		
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
};

#endif

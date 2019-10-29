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
<<<<<<< Updated upstream:fingerCountFrm.h
=======
#include <wx/filedlg.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/statbmp.h>
>>>>>>> Stashed changes:fingerCountv3Frm.h
////Header Include End

////Dialog Style Start
#define fingerCountFrm_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxDIALOG_NO_PARENT | wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxCLOSE_BOX
////Dialog Style End

class fingerCountFrm : public wxFrame
{
	private:
		void buttonInsertImageClick(wxCommandEvent& event);
		DECLARE_EVENT_TABLE();
		
	public:
<<<<<<< Updated upstream:fingerCountFrm.h
		fingerCountFrm(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("Finger Counting"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = fingerCountFrm_STYLE);
		virtual ~fingerCountFrm();
=======
		fingerCountv3Frm(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("Finger Counting"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = fingerCountv3Frm_STYLE);
		virtual ~fingerCountv3Frm();
		void buttonObtainDefectsClick(wxCommandEvent& event);
>>>>>>> Stashed changes:fingerCountv3Frm.h
		
	private:
		//Do not add custom control declarations between
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
<<<<<<< Updated upstream:fingerCountFrm.h
=======
		wxFileDialog *dialogChooseImage;
		wxStaticText *labelFingerCount;
		wxButton *buttonObtainDefects;
		wxButton *buttonObtainMask;
		wxButton *buttonInsertImage;
		wxStaticBitmap *bitmapOutput;
		wxStaticBitmap *bitmapInput;
>>>>>>> Stashed changes:fingerCountv3Frm.h
		////GUI Control Declaration End
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
		
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
};

#endif

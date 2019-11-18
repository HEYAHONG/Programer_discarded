///-----------------------------------------------------------------
///
/// @file      Address_manualDlg.h
/// @author    ºÎÑÇºì
/// Created:   2019-11-14 12:47:23
/// @section   DESCRIPTION
///            Address_manual class declaration
///
///------------------------------------------------------------------

#ifndef __ADDRESS_MANUAL_H__
#define __ADDRESS_MANUAL_H__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/dialog.h>
#else
	#include <wx/wxprec.h>
#endif

//Do not add custom headers between 
//Header Include Start and Header Include End.
//wxDev-C++ designer will remove them. Add custom headers after the block.
////Header Include Start
#include <wx/textctrl.h>
#include <wx/stattext.h>
#include <wx/button.h>
////Header Include End

////Dialog Style Start
#undef Address_manual_STYLE
#define Address_manual_STYLE wxCAPTION
////Dialog Style End

class Address_manual : public wxDialog
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		Address_manual(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("Set Address"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = Address_manual_STYLE);
		virtual ~Address_manual();
		wxString              symbol_ret;
        uint32_t              symbol_start_ret;
        uint32_t              symbol_length_ret;
		void WxButton1Click(wxCommandEvent& event);
		void WxEdit1Updated(wxCommandEvent& event);
		void WxEdit3Updated(wxCommandEvent& event);
		void WxEdit2Updated(wxCommandEvent& event);
	
	private:
		//Do not add custom control declarations between 
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxTextCtrl *WxEdit3;
		wxTextCtrl *WxEdit2;
		wxTextCtrl *WxEdit1;
		wxStaticText *WxStaticText3;
		wxStaticText *WxStaticText2;
		wxStaticText *WxStaticText1;
		wxButton *WxButton1;
		////GUI Control Declaration End
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			ID_WXEDIT3 = 1007,
			ID_WXEDIT2 = 1006,
			ID_WXEDIT1 = 1005,
			ID_WXSTATICTEXT3 = 1004,
			ID_WXSTATICTEXT2 = 1003,
			ID_WXSTATICTEXT1 = 1002,
			ID_WXBUTTON1 = 1001,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
	
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
};

#endif

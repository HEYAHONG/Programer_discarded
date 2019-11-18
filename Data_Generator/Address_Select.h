///-----------------------------------------------------------------
///
/// @file      Address_Select.h
/// @author    ºÎÑÇºì
/// Created:   2019-11-13 15:36:56
/// @section   DESCRIPTION
///            Address_Select class declaration
///
///------------------------------------------------------------------

#ifndef __ADDRESS_SELECT_H__
#define __ADDRESS_SELECT_H__

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
#include <wx/button.h>
#include <wx/combobox.h>
#include <wx/textctrl.h>
////Header Include End

#include <vector>
#include "stdint.h"

////Dialog Style Start
#undef Address_Select_STYLE
#define Address_Select_STYLE wxCAPTION
////Dialog Style End

class Address_Select : public wxDialog
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		Address_Select(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT(" "), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = Address_Select_STYLE);
		virtual ~Address_Select();
		void WxButton1Click(wxCommandEvent& event);
		std::vector<wxString> symbol_table;
		std::vector<uint32_t> symbol_start_table;
        std::vector<uint32_t> symbol_length_table;
        wxString              symbol_ret;
        uint32_t              symbol_start_ret;
        uint32_t              symbol_length_ret;
        void Update_Data();
		void WxComboBox1Updated(wxCommandEvent& event );
		void WxComboBox1Selected(wxCommandEvent& event );
	
	private:
		//Do not add custom control declarations between 
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxButton *WxButton1;
		wxComboBox *WxComboBox1;
		wxTextCtrl *WxEdit1;
		////GUI Control Declaration End
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			ID_WXBUTTON1 = 1003,
			ID_WXCOMBOBOX1 = 1002,
			ID_WXEDIT1 = 1001,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
	
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
};

#endif

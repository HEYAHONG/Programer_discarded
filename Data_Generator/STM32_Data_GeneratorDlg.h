///-----------------------------------------------------------------
///
/// @file      STM32_Data_GeneratorDlg.h
/// @author    ºÎÑÇºì
/// Created:   2019-11-13 10:00:42
/// @section   DESCRIPTION
///            STM32_Data_GeneratorDlg class declaration
///
///------------------------------------------------------------------

#ifndef __STM32_DATA_GENERATORDLG_H__
#define __STM32_DATA_GENERATORDLG_H__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/dialog.h>
#else
	#include <wx/wxprec.h>
#endif
extern "C"
{ 
#include "nettle/aes.h" 
}

#include "Address_Select.h"
#include "Address_manualDlg.h"

//Do not add custom headers between 
//Header Include Start and Header Include End.
//wxDev-C++ designer will remove them. Add custom headers after the block.
////Header Include Start
#include <wx/richtext/richtextctrl.h>
#include <wx/button.h>
////Header Include End

////Dialog Style Start
#undef STM32_Data_GeneratorDlg_STYLE
#define STM32_Data_GeneratorDlg_STYLE wxCAPTION | wxSYSTEM_MENU | wxDIALOG_NO_PARENT | wxMINIMIZE_BOX | wxCLOSE_BOX
////Dialog Style End

class STM32_Data_GeneratorDlg : public wxDialog
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		STM32_Data_GeneratorDlg(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("STM32_Data_Generator"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = STM32_Data_GeneratorDlg_STYLE);
		virtual ~STM32_Data_GeneratorDlg();
		void WxButton_SaveClick(wxCommandEvent& event);
		void WxButton_OpenClick(wxCommandEvent& event);
		void ErrorMessage(wxString msg,wxString title="´íÎó"); 
		
		wxString FilePath;
		wxString type;
		wxString symbol;
		uint32_t symbol_start;
		uint32_t symbol_length;
	
	private:
		//Do not add custom control declarations between 
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxRichTextCtrl *WxRichTextCtrl1;
		wxButton *WxButton_Save;
		wxButton *WxButton_Open;
		////GUI Control Declaration End
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			ID_WXRICHTEXTCTRL1 = 1003,
			ID_WXBUTTON2 = 1002,
			ID_WXBUTTON1_OPEN = 1001,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
	
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
};

#endif

///-----------------------------------------------------------------
///
/// @file      STM32_Data_ProgramerDlg.h
/// @author    ºÎÑÇºì
/// Created:   2019-11-18 13:18:06
/// @section   DESCRIPTION
///            STM32_Data_ProgramerDlg class declaration
///
///------------------------------------------------------------------

#ifndef __STM32_DATA_PROGRAMERDLG_H__
#define __STM32_DATA_PROGRAMERDLG_H__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/dialog.h>
#else
	#include <wx/wxprec.h>
#endif

#include "dlfcn.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "dir.h"
#include "dirent.h"
#include "unistd.h"
#ifdef WIN32
#include "windows.h"
#endif

#include "aes.h"
 
//Do not add custom headers between 
//Header Include Start and Header Include End.
//wxDev-C++ designer will remove them. Add custom headers after the block.
////Header Include Start
#include <wx/stattext.h>
#include <wx/timer.h>
#include <wx/button.h>
#include <wx/textctrl.h>
////Header Include End

////Dialog Style Start
#undef STM32_Data_ProgramerDlg_STYLE
#define STM32_Data_ProgramerDlg_STYLE wxCAPTION | wxSYSTEM_MENU | wxDIALOG_NO_PARENT | wxDIALOG_EX_CONTEXTHELP | wxMINIMIZE_BOX | wxCLOSE_BOX
////Dialog Style End

class STM32_Data_ProgramerDlg : public wxDialog
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		STM32_Data_ProgramerDlg(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("STM32_Data_Programer"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = STM32_Data_ProgramerDlg_STYLE);
		virtual ~STM32_Data_ProgramerDlg();
		wxString DataDir;
		void     Data_Init();
	    uint8_t *hex_data; 
		void STM32_Data_ProgramerDlgEnterWindow(wxMouseEvent& event);
		void STM32_Data_ProgramerDlgInitDialog(wxInitDialogEvent& event);
		void WxButton1Click(wxCommandEvent& event);
		void STM32_Data_ProgramerDlgSetFocus(wxFocusEvent& event);
		void STM32_Data_ProgramerDlgActivate(wxActivateEvent& event);
		void WxTimer1Timer(wxTimerEvent& event);
		void WxEdit1Updated(wxCommandEvent& event);
	
	private:
		//Do not add custom control declarations between 
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxTextCtrl *WxEdit1;
		wxStaticText *WxStaticText1;
		wxTimer *WxTimer1;
		wxButton *WxButton1;
		wxTextCtrl *Info;
		////GUI Control Declaration End
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			ID_WXEDIT1 = 1005,
			ID_WXSTATICTEXT1 = 1004,
			ID_WXTIMER1 = 1003,
			ID_WXBUTTON1 = 1002,
			ID_WXEDIT1_Info = 1001,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
	
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
};

#endif

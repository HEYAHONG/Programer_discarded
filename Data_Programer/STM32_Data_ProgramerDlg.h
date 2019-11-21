///-----------------------------------------------------------------
///
/// @file      STM32_Data_ProgramerDlg.h
/// @author    何亚红
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

#include "nettle/aes.h"

//包含插件定义头文件
#include "plugin.h"

 
//Do not add custom headers between 
//Header Include Start and Header Include End.
//wxDev-C++ designer will remove them. Add custom headers after the block.
////Header Include Start
#include <wx/checkbox.h>
#include <wx/statline.h>
#include <wx/combobox.h>
#include <wx/timer.h>
#include <wx/stattext.h>
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
	    void search_plugin(); 
	    void start_flash(); 
	    wxTextCtrl * Get_Info_Ctl(); 
		void STM32_Data_ProgramerDlgEnterWindow(wxMouseEvent& event);
		void STM32_Data_ProgramerDlgInitDialog(wxInitDialogEvent& event);
		void WxButton1Click(wxCommandEvent& event);
		void STM32_Data_ProgramerDlgSetFocus(wxFocusEvent& event);
		void STM32_Data_ProgramerDlgActivate(wxActivateEvent& event);
		void WxTimer1Timer(wxTimerEvent& event);
		void WxEdit1Updated(wxCommandEvent& event);
		void WxButton2Click(wxCommandEvent& event);
		void WxButton3Click(wxCommandEvent& event);
	
	public:
		//Do not add custom control declarations between 
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxButton *WxButton3;
		wxCheckBox *WxCheckBox2;
		wxCheckBox *WxCheckBox1;
		wxStaticLine *WxStaticLine2;
		wxStaticLine *WxStaticLine1;
		wxButton *WxButton2;
		wxStaticText *WxStaticText3;
		wxStaticText *WxStaticText2;
		wxComboBox *WxComboBox2;
		wxComboBox *WxComboBox1;
		wxTimer *WxTimer1;
		wxTextCtrl *WxEdit1;
		wxStaticText *WxStaticText1;
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
			ID_WXBUTTON3 = 1016,
			ID_WXCHECKBOX2 = 1014,
			ID_WXCHECKBOX1 = 1013,
			ID_WXSTATICLINE2 = 1012,
			ID_WXSTATICLINE1 = 1011,
			ID_WXBUTTON2 = 1010,
			ID_WXSTATICTEXT3 = 1009,
			ID_WXSTATICTEXT2 = 1008,
			ID_WXCOMBOBOX2 = 1007,
			ID_WXCOMBOBOX1 = 1006,
			ID_WXTIMER1 = 1003,
			ID_WXEDIT1 = 1005,
			ID_WXSTATICTEXT1 = 1004,
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

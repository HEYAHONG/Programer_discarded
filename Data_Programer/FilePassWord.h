///-----------------------------------------------------------------
///
/// @file      FilePassWord.h
/// @author    ºÎÑÇºì
/// Created:   2019-11-18 15:26:07
/// @section   DESCRIPTION
///            FilePassWord class declaration
///
///------------------------------------------------------------------

#ifndef __FILEPASSWORD_H__
#define __FILEPASSWORD_H__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/dialog.h>
#else
	#include <wx/wxprec.h>
#endif
#include "aes.h"
typedef union
{
uint8_t buff[32];
struct 
{
    size_t   hex_size;
	size_t   hex_data_size; 
	size_t   dat_size;
	size_t   flag;
} data;
} Dat_header;

//Do not add custom headers between 
//Header Include Start and Header Include End.
//wxDev-C++ designer will remove them. Add custom headers after the block.
////Header Include Start
#include <wx/button.h>
#include <wx/textctrl.h>
////Header Include End

////Dialog Style Start
#undef FilePassWord_STYLE
#define FilePassWord_STYLE wxCAPTION
////Dialog Style End

class FilePassWord : public wxDialog
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		FilePassWord(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("FilePassWord"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = FilePassWord_STYLE);
		virtual ~FilePassWord();
		void WxEdit1Updated(wxCommandEvent& event);
		void WxButton1Click(wxCommandEvent& event);
		void WxButton2Click(wxCommandEvent& event);
		void WxButton2Click0(wxCommandEvent& event);
	
	private:
		//Do not add custom control declarations between 
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxButton *WxButton2;
		wxTextCtrl *WxEdit2;
		wxButton *WxButton1;
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
			ID_WXBUTTON2 = 1004,
			ID_WXEDIT2 = 1003,
			ID_WXBUTTON1 = 1002,
			ID_WXEDIT1 = 1001,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
	
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
};

#endif

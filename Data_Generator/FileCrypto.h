///-----------------------------------------------------------------
///
/// @file      FileCrypto.h
/// @author    ºÎÑÇºì
/// Created:   2019-11-15 11:44:28
/// @section   DESCRIPTION
///            FileCrypto class declaration
///
///------------------------------------------------------------------

#ifndef __FILECRYPTO_H__
#define __FILECRYPTO_H__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/dialog.h>
#else
	#include <wx/wxprec.h>
#endif

#include "nettle/aes.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "dir.h"
#include "dirent.h"
#include "unistd.h"
#ifdef WIN32
#include "windows.h"
#endif 
//Do not add custom headers between 
//Header Include Start and Header Include End.
//wxDev-C++ designer will remove them. Add custom headers after the block.
////Header Include Start
#include <wx/button.h>
#include <wx/textctrl.h>
////Header Include End

////Dialog Style Start
#undef FileCrypto_STYLE
#define FileCrypto_STYLE wxCAPTION
////Dialog Style End
#include "stdint.h"
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

class FileCrypto : public wxDialog
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		FileCrypto(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("FileCrypto"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = FileCrypto_STYLE);
		virtual ~FileCrypto();
		void WxButton1Click(wxCommandEvent& event);
		void WxEdit1Updated(wxCommandEvent& event);
	
	private:
		//Do not add custom control declarations between 
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxTextCtrl *WxEdit2;
		wxButton *WxButton1;
		wxTextCtrl *WxEdit1;
		////GUI Control Declaration End
		
		FILE * hex;
		size_t hex_size;
		size_t hex_data_size;
		FILE * dat;
		size_t dat_size;
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
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

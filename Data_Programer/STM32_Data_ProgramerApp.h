//---------------------------------------------------------------------------
//
// Name:        STM32_Data_ProgramerApp.h
// Author:      ºÎÑÇºì
// Created:     2019-11-18 13:18:05
// Description: 
//
//---------------------------------------------------------------------------

#ifndef __STM32_DATA_PROGRAMERDLGApp_h__
#define __STM32_DATA_PROGRAMERDLGApp_h__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#else
	#include <wx/wxprec.h>
#endif

class STM32_Data_ProgramerDlgApp : public wxApp
{
	public:
		bool OnInit();
		void SetEnvironment();
		int OnExit();
};

#endif

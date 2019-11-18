//---------------------------------------------------------------------------
//
// Name:        STM32_Data_GeneratorApp.h
// Author:      ºÎÑÇºì
// Created:     2019-11-13 10:00:42
// Description: 
//
//---------------------------------------------------------------------------

#ifndef __STM32_DATA_GENERATORDLGApp_h__
#define __STM32_DATA_GENERATORDLGApp_h__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#else
	#include <wx/wxprec.h>
#endif

class STM32_Data_GeneratorDlgApp : public wxApp
{
	public:
        void SetEnvironment(); 
		bool OnInit();
		int OnExit();
};

#endif

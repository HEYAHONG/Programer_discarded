/***************************************************************
 * Name:      Jlink_plugin_backendApp.cpp
 * Purpose:   Code for Application Class
 * Author:    HYH (2229388563@qq.com)
 * Created:   2019-11-22
 * Copyright: HYH ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "MainWindow.h"
#include "Jlink_plugin_backendApp.h"
//(*AppHeaders
#include "MainWindow.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(Jlink_plugin_backendApp);

bool Jlink_plugin_backendApp::OnInit()
{
	//(*AppInitialize
	bool wxsOK = true;
	wxInitAllImageHandlers();
	if ( wxsOK )
	{
		MainWindow Dlg(0);
		SetTopWindow(&Dlg);
		Dlg.ShowModal();
		wxsOK = false;
	}
	//*)
    return wxsOK;
}

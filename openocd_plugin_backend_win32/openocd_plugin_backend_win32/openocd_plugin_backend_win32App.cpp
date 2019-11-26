/***************************************************************
 * Name:      openocd_plugin_backend_win32App.cpp
 * Purpose:   Code for Application Class
 * Author:    HYH (2229388563@qq.com)
 * Created:   2019-11-26
 * Copyright: HYH ()
 * License:
 **************************************************************/

#include "openocd_plugin_backend_win32App.h"

//(*AppHeaders
#include "openocd_plugin_backend_win32Main.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(openocd_plugin_backend_win32App);

bool openocd_plugin_backend_win32App::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	openocd_plugin_backend_win32Dialog Dlg(0);
    	SetTopWindow(&Dlg);
    	Dlg.ShowModal();
    	wxsOK = false;
    }
    //*)
    return wxsOK;

}

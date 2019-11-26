/***************************************************************
 * Name:      openocd_plugin_backend_win32App.h
 * Purpose:   Defines Application Class
 * Author:    HYH (2229388563@qq.com)
 * Created:   2019-11-26
 * Copyright: HYH ()
 * License:
 **************************************************************/

#ifndef OPENOCD_PLUGIN_BACKEND_WIN32APP_H
#define OPENOCD_PLUGIN_BACKEND_WIN32APP_H

#include <wx/app.h>

class openocd_plugin_backend_win32App : public wxApp
{
    public:
        virtual bool OnInit();
};

#endif // OPENOCD_PLUGIN_BACKEND_WIN32APP_H

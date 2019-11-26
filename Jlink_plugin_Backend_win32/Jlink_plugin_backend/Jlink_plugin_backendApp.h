/***************************************************************
 * Name:      Jlink_plugin_backendApp.h
 * Purpose:   Defines Application Class
 * Author:    HYH (2229388563@qq.com)
 * Created:   2019-11-22
 * Copyright: HYH ()
 * License:
 **************************************************************/

#ifndef JLINK_PLUGIN_BACKENDAPP_H
#define JLINK_PLUGIN_BACKENDAPP_H

#include <wx/app.h>

class Jlink_plugin_backendApp : public wxApp
{
    public:
        virtual bool OnInit();
};

#endif // JLINK_PLUGIN_BACKENDAPP_H

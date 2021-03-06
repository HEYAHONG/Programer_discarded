/***************************************************************
 * Name:      openocd_plugin_backend_win32Main.h
 * Purpose:   Defines Application Frame
 * Author:    HYH (2229388563@qq.com)
 * Created:   2019-11-26
 * Copyright: HYH ()
 * License:
 **************************************************************/
#include "openocd_wxthread.h"
#ifndef OPENOCD_PLUGIN_BACKEND_WIN32MAIN_H
#define OPENOCD_PLUGIN_BACKEND_WIN32MAIN_H

//(*Headers(openocd_plugin_backend_win32Dialog)
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/combobox.h>
#include <wx/dialog.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/timer.h>
//*)

class openocd_plugin_backend_win32Dialog: public wxDialog
{
    public:

        openocd_plugin_backend_win32Dialog(wxWindow* parent,wxWindowID id = -1);
        virtual ~openocd_plugin_backend_win32Dialog();
        Openocd_wxThread *thread;
        HANDLE Is_Started;//判断是否已经运行
        void Data_Init();//初始化控件上的数据
    private:

        //(*Handlers(openocd_plugin_backend_win32Dialog)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnTextCtrl1TextEnter(wxCommandEvent& event);
        void OnTimer2Trigger(wxTimerEvent& event);
        void OnTimer1Trigger(wxTimerEvent& event);
        void OnTextCtrl3Text(wxCommandEvent& event);
        void OnTextCtrl2Text(wxCommandEvent& event);
        void OnTimer3Trigger(wxTimerEvent& event);
        void OnButton1Click(wxCommandEvent& event);
        void OnButton2Click(wxCommandEvent& event);
        void OnCheckBox2Click(wxCommandEvent& event);
        //*)

        //(*Identifiers(openocd_plugin_backend_win32Dialog)
        static const long ID_STATICBOX1;
        static const long ID_COMBOBOX1;
        static const long ID_STATICBOX2;
        static const long ID_COMBOBOX2;
        static const long ID_STATICBOX3;
        static const long ID_COMBOBOX3;
        static const long ID_STATICBOX4;
        static const long ID_TEXTCTRL1;
        static const long ID_TEXTCTRL2;
        static const long ID_STATICBOX5;
        static const long ID_STATICTEXT1;
        static const long ID_STATICTEXT2;
        static const long ID_TEXTCTRL3;
        static const long ID_TEXTCTRL4;
        static const long ID_STATICTEXT3;
        static const long ID_STATICTEXT4;
        static const long ID_STATICBOX6;
        static const long ID_BUTTON1;
        static const long ID_BUTTON2;
        static const long ID_CHECKBOX1;
        static const long ID_CHECKBOX2;
        static const long ID_STATICTEXT5;
        static const long ID_TIMER1;
        static const long ID_TIMER2;
        static const long ID_TIMER3;
        //*)

        //(*Declarations(openocd_plugin_backend_win32Dialog)
        wxButton* Button1;
        wxButton* Button2;
        wxCheckBox* CheckBox1;
        wxCheckBox* CheckBox2;
        wxComboBox* interface1;
        wxComboBox* target1;
        wxComboBox* transport1;
        wxStaticBox* StaticBox1;
        wxStaticBox* StaticBox2;
        wxStaticBox* StaticBox3;
        wxStaticBox* StaticBox4;
        wxStaticBox* StaticBox5;
        wxStaticBox* StaticBox6;
        wxStaticText* StaticText1;
        wxStaticText* StaticText2;
        wxStaticText* StaticText3;
        wxStaticText* StaticText4;
        wxStaticText* StaticText5;
        wxTextCtrl* TextCtrl1;
        wxTextCtrl* TextCtrl2;
        wxTextCtrl* TextCtrl3;
        wxTextCtrl* log2;
        wxTimer Timer1;
        wxTimer Timer2;
        wxTimer Timer3;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // OPENOCD_PLUGIN_BACKEND_WIN32MAIN_H

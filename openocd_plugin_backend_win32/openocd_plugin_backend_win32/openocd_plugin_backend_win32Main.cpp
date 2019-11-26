/***************************************************************
 * Name:      openocd_plugin_backend_win32Main.cpp
 * Purpose:   Code for Application Frame
 * Author:    HYH (2229388563@qq.com)
 * Created:   2019-11-26
 * Copyright: HYH ()
 * License:
 **************************************************************/

#include "openocd_plugin_backend_win32Main.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(openocd_plugin_backend_win32Dialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(openocd_plugin_backend_win32Dialog)
const long openocd_plugin_backend_win32Dialog::ID_STATICBOX1 = wxNewId();
const long openocd_plugin_backend_win32Dialog::ID_COMBOBOX1 = wxNewId();
const long openocd_plugin_backend_win32Dialog::ID_STATICBOX2 = wxNewId();
const long openocd_plugin_backend_win32Dialog::ID_COMBOBOX2 = wxNewId();
const long openocd_plugin_backend_win32Dialog::ID_STATICBOX3 = wxNewId();
const long openocd_plugin_backend_win32Dialog::ID_COMBOBOX3 = wxNewId();
const long openocd_plugin_backend_win32Dialog::ID_STATICBOX4 = wxNewId();
const long openocd_plugin_backend_win32Dialog::ID_TEXTCTRL1 = wxNewId();
const long openocd_plugin_backend_win32Dialog::ID_TEXTCTRL2 = wxNewId();
const long openocd_plugin_backend_win32Dialog::ID_STATICBOX5 = wxNewId();
const long openocd_plugin_backend_win32Dialog::ID_STATICTEXT1 = wxNewId();
const long openocd_plugin_backend_win32Dialog::ID_STATICTEXT2 = wxNewId();
const long openocd_plugin_backend_win32Dialog::ID_TIMER1 = wxNewId();
const long openocd_plugin_backend_win32Dialog::ID_TIMER2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(openocd_plugin_backend_win32Dialog,wxDialog)
    //(*EventTable(openocd_plugin_backend_win32Dialog)
    //*)
END_EVENT_TABLE()

openocd_plugin_backend_win32Dialog::openocd_plugin_backend_win32Dialog(wxWindow* parent,wxWindowID id)
{
    thread=NULL;
    //(*Initialize(openocd_plugin_backend_win32Dialog)
    Create(parent, id, _("openocd_backend"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
    SetClientSize(wxSize(556,367));
    StaticBox1 = new wxStaticBox(this, ID_STATICBOX1, _("接口"), wxPoint(8,8), wxSize(152,48), 0, _T("ID_STATICBOX1"));
    interface1 = new wxComboBox(this, ID_COMBOBOX1, wxEmptyString, wxPoint(16,24), wxSize(136,22), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_COMBOBOX1"));
    StaticBox2 = new wxStaticBox(this, ID_STATICBOX2, _("目标"), wxPoint(168,8), wxSize(144,48), 0, _T("ID_STATICBOX2"));
    target1 = new wxComboBox(this, ID_COMBOBOX2, wxEmptyString, wxPoint(176,24), wxSize(128,22), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_COMBOBOX2"));
    StaticBox3 = new wxStaticBox(this, ID_STATICBOX3, _("传输类型"), wxPoint(8,64), wxSize(152,56), 0, _T("ID_STATICBOX3"));
    transport1 = new wxComboBox(this, ID_COMBOBOX3, wxEmptyString, wxPoint(16,80), wxSize(136,22), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_COMBOBOX3"));
    StaticBox4 = new wxStaticBox(this, ID_STATICBOX4, _("GDB连接端口"), wxPoint(168,64), wxSize(144,56), 0, _T("ID_STATICBOX4"));
    TextCtrl1 = new wxTextCtrl(this, ID_TEXTCTRL1, _("55555"), wxPoint(176,80), wxSize(128,24), wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    log2 = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxPoint(0,128), wxSize(552,232), wxTE_MULTILINE|wxVSCROLL|wxHSCROLL, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    StaticBox5 = new wxStaticBox(this, ID_STATICBOX5, _("日志框选项"), wxPoint(328,16), wxSize(184,104), 0, _T("ID_STATICBOX5"));
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("清理间隔时间:"), wxPoint(344,40), wxSize(80,24), 0, _T("ID_STATICTEXT1"));
    StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("日志缓冲大小:"), wxPoint(344,80), wxSize(80,16), 0, _T("ID_STATICTEXT2"));
    Timer1.SetOwner(this, ID_TIMER1);
    Timer1.Start(2000, false);
    Timer1.Start();
    Timer2.SetOwner(this, ID_TIMER2);
    Timer2.Start(2, false);

    Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&openocd_plugin_backend_win32Dialog::OnTextCtrl1TextEnter);
    Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&openocd_plugin_backend_win32Dialog::OnTextCtrl1TextEnter);
    Connect(ID_TIMER1,wxEVT_TIMER,(wxObjectEventFunction)&openocd_plugin_backend_win32Dialog::OnTimer1Trigger);
    Connect(ID_TIMER2,wxEVT_TIMER,(wxObjectEventFunction)&openocd_plugin_backend_win32Dialog::OnTimer2Trigger);
    //*)
    Data_Init();

}

openocd_plugin_backend_win32Dialog::~openocd_plugin_backend_win32Dialog()
{
    //(*Destroy(openocd_plugin_backend_win32Dialog)
    //*)
    if(thread!=NULL)
        delete thread;
}

void openocd_plugin_backend_win32Dialog::OnQuit(wxCommandEvent& event)
{
    Close();
}

void openocd_plugin_backend_win32Dialog::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void openocd_plugin_backend_win32Dialog::Data_Init()
{

    {//添加接口数据
        interface1->Insert("stlink-v1",0);
        interface1->Insert("stlink-v2",0);
        interface1->Insert("stlink-v2-1",0);
        interface1->Insert("cmsis-dap",0);
        interface1->Select(0);//选中cmsis-dap
    }
    {//添加目标数据
        target1->Insert("stm32_stlink",0);
        target1->Insert("stm32xl",0);
        target1->Insert("stm32w108_stlink",0);
        target1->Insert("stm32w108xx",0);
        target1->Insert("stm32lx_stlink",0);
        target1->Insert("stm32l4x",0);
        target1->Insert("stm32l1x_dual_bank",0);
        target1->Insert("stm32l1",0);
        target1->Insert("stm32l0",0);
        target1->Insert("stm32f7x",0);
        target1->Insert("stm32f4x_stlink",0);
        target1->Insert("stm32f4x",0);
        target1->Insert("stm32f3x_stlink",0);
        target1->Insert("stm32f3x",0);
        target1->Insert("stm32f2x_stlink",0);
        target1->Insert("stm32f2x",0);
        target1->Insert("stm32f1x_stlink",0);
        target1->Insert("stm32f1x",0);
        target1->Insert("stm32f0x_stlink",0);
        target1->Insert("stm32f0x",0);
        target1->Select(2); //选中stm32f1x
    }
    {//添加传输类型
        transport1->Insert("jtag",0);
        transport1->Insert("aice_jtag",0);
        transport1->Insert("swd",0);
        transport1->Insert("stlink_swim",0);
        transport1->Insert("hla_jtag",0);
        transport1->Insert("hla_swd",0);
        transport1->Select(3);//选中swd
    }
}

void openocd_plugin_backend_win32Dialog::OnTextCtrl1TextEnter(wxCommandEvent& event)
{
    wxString num=TextCtrl1->GetValue();
    long val=0;
    if(num.empty())
    {
        TextCtrl1->SetValue("55555");
        return;
    }
    if(num.ToLong(&val,10))
    {
        if(val>65535) //端口非法
        {
            TextCtrl1->SetValue("55555");
            return;
        }
    }
    else
    {
        TextCtrl1->SetValue("55555");
        return;
    }
}

void openocd_plugin_backend_win32Dialog::OnTimer2Trigger(wxTimerEvent& event)
{
    //日志定时器
    if(thread!=NULL)
    {
        if(thread->GetStatus()==1)//进程正常存活
        {
            unsigned char buff[8192];
            memset(buff,0,sizeof(buff));
            if(thread->ReadStdout(buff,sizeof(buff))>0)
                log2->AppendText(buff);
            memset(buff,0,sizeof(buff));
            if(thread->ReadStderr(buff,sizeof(buff))>0)
                log2->AppendText((wxString)buff);
        }
    }

}
#include "windows.h"
void openocd_plugin_backend_win32Dialog::OnTimer1Trigger(wxTimerEvent& event)
{//延迟启动

    if(thread==NULL)
    {
         thread=new Openocd_wxThread;
         Timer2.Start();//启动定时器

    }
    if(thread->GetStatus()==-1)
    {
        Timer1.Stop();
        wxMessageBox("openocd运行失败!请检查以下内容：\n1.硬件是否正确连接。\n2.设置是否正确。\n3.是否有其它软件与openocd冲突(如占用openocd端口或误杀openocd进程)。\n","警告",wxICON_ERROR);
        Close();
    }

}

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
extern char cmdline[];

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
const long openocd_plugin_backend_win32Dialog::ID_TEXTCTRL3 = wxNewId();
const long openocd_plugin_backend_win32Dialog::ID_TEXTCTRL4 = wxNewId();
const long openocd_plugin_backend_win32Dialog::ID_STATICTEXT3 = wxNewId();
const long openocd_plugin_backend_win32Dialog::ID_STATICTEXT4 = wxNewId();
const long openocd_plugin_backend_win32Dialog::ID_STATICBOX6 = wxNewId();
const long openocd_plugin_backend_win32Dialog::ID_BUTTON1 = wxNewId();
const long openocd_plugin_backend_win32Dialog::ID_BUTTON2 = wxNewId();
const long openocd_plugin_backend_win32Dialog::ID_CHECKBOX1 = wxNewId();
const long openocd_plugin_backend_win32Dialog::ID_CHECKBOX2 = wxNewId();
const long openocd_plugin_backend_win32Dialog::ID_STATICTEXT5 = wxNewId();
const long openocd_plugin_backend_win32Dialog::ID_TIMER1 = wxNewId();
const long openocd_plugin_backend_win32Dialog::ID_TIMER2 = wxNewId();
const long openocd_plugin_backend_win32Dialog::ID_TIMER3 = wxNewId();
//*)

BEGIN_EVENT_TABLE(openocd_plugin_backend_win32Dialog,wxDialog)
    //(*EventTable(openocd_plugin_backend_win32Dialog)
    //*)
END_EVENT_TABLE()

openocd_plugin_backend_win32Dialog::openocd_plugin_backend_win32Dialog(wxWindow* parent,wxWindowID id)
{
    thread=NULL;
    Is_Started=CreateMutexA(NULL,TRUE,"openocd_plugin_backend_win32_running");
    if(Is_Started)
    {
        if(GetLastError()==ERROR_ALREADY_EXISTS)
        {
            wxMessageBox("ֻ����һ��ʵ��������!\n","����");
            CloseHandle(Is_Started);
            exit(255);
        }
    }
    else
    {
        wxMessageBox("�ж�ʧ��!\n","����");
        CloseHandle(Is_Started);
        exit(255);
    }
    //(*Initialize(openocd_plugin_backend_win32Dialog)
    Create(parent, id, _("openocd_backend"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxCLOSE_BOX|wxMINIMIZE_BOX, _T("id"));
    SetClientSize(wxSize(556,422));
    Move(wxPoint(-1,-1));
    StaticBox1 = new wxStaticBox(this, ID_STATICBOX1, _("�ӿ�"), wxPoint(8,8), wxSize(152,48), 0, _T("ID_STATICBOX1"));
    interface1 = new wxComboBox(this, ID_COMBOBOX1, wxEmptyString, wxPoint(16,24), wxSize(136,22), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_COMBOBOX1"));
    StaticBox2 = new wxStaticBox(this, ID_STATICBOX2, _("Ŀ��"), wxPoint(168,8), wxSize(144,48), 0, _T("ID_STATICBOX2"));
    target1 = new wxComboBox(this, ID_COMBOBOX2, wxEmptyString, wxPoint(176,24), wxSize(128,22), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_COMBOBOX2"));
    StaticBox3 = new wxStaticBox(this, ID_STATICBOX3, _("��������"), wxPoint(8,64), wxSize(152,56), 0, _T("ID_STATICBOX3"));
    transport1 = new wxComboBox(this, ID_COMBOBOX3, wxEmptyString, wxPoint(16,80), wxSize(136,22), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_COMBOBOX3"));
    StaticBox4 = new wxStaticBox(this, ID_STATICBOX4, _("GDB���Ӷ˿�"), wxPoint(168,64), wxSize(144,56), 0, _T("ID_STATICBOX4"));
    TextCtrl1 = new wxTextCtrl(this, ID_TEXTCTRL1, _("55555"), wxPoint(176,80), wxSize(128,24), wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    log2 = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxPoint(0,192), wxSize(552,224), wxTE_MULTILINE|wxTE_READONLY|wxVSCROLL|wxHSCROLL, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    StaticBox5 = new wxStaticBox(this, ID_STATICBOX5, _("��־��ѡ��"), wxPoint(328,16), wxSize(224,104), 0, _T("ID_STATICBOX5"));
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("������ʱ��:"), wxPoint(344,40), wxSize(80,24), 0, _T("ID_STATICTEXT1"));
    StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("��־�����С:"), wxPoint(344,80), wxSize(80,16), 0, _T("ID_STATICTEXT2"));
    TextCtrl2 = new wxTextCtrl(this, ID_TEXTCTRL3, _("3000"), wxPoint(424,40), wxSize(72,22), 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    TextCtrl3 = new wxTextCtrl(this, ID_TEXTCTRL4, _("300000"), wxPoint(424,80), wxSize(72,22), 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
    StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("����"), wxPoint(504,40), wxSize(40,24), 0, _T("ID_STATICTEXT3"));
    StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("�ֽ�"), wxPoint(504,80), wxSize(32,24), 0, _T("ID_STATICTEXT4"));
    StaticBox6 = new wxStaticBox(this, ID_STATICBOX6, _("����"), wxPoint(8,128), wxSize(536,56), 0, _T("ID_STATICBOX6"));
    Button1 = new wxButton(this, ID_BUTTON1, _("����"), wxPoint(48,144), wxSize(80,32), 0, wxDefaultValidator, _T("ID_BUTTON1"));
    Button2 = new wxButton(this, ID_BUTTON2, _("ֹͣ"), wxPoint(144,144), wxSize(72,32), 0, wxDefaultValidator, _T("ID_BUTTON2"));
    CheckBox1 = new wxCheckBox(this, ID_CHECKBOX1, _("����ʧ���Զ�����"), wxPoint(240,144), wxSize(128,32), 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    CheckBox1->SetValue(false);
    CheckBox2 = new wxCheckBox(this, ID_CHECKBOX2, _("�Զ�����"), wxPoint(384,144), wxSize(72,32), 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
    CheckBox2->SetValue(true);
    StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("5"), wxPoint(456,152), wxSize(48,16), wxST_NO_AUTORESIZE|wxALIGN_LEFT, _T("ID_STATICTEXT5"));
    Timer1.SetOwner(this, ID_TIMER1);
    Timer1.Start(1000, false);
    Timer1.Start();
    Timer2.SetOwner(this, ID_TIMER2);
    Timer2.Start(20, false);
    Timer3.SetOwner(this, ID_TIMER3);
    Timer3.Start(3000, false);
    Timer3.Start();
    Center();

    Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&openocd_plugin_backend_win32Dialog::OnTextCtrl1TextEnter);
    Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&openocd_plugin_backend_win32Dialog::OnTextCtrl1TextEnter);
    Connect(ID_TEXTCTRL3,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&openocd_plugin_backend_win32Dialog::OnTextCtrl2Text);
    Connect(ID_TEXTCTRL3,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&openocd_plugin_backend_win32Dialog::OnTextCtrl2Text);
    Connect(ID_TEXTCTRL4,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&openocd_plugin_backend_win32Dialog::OnTextCtrl3Text);
    Connect(ID_TEXTCTRL4,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&openocd_plugin_backend_win32Dialog::OnTextCtrl3Text);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&openocd_plugin_backend_win32Dialog::OnButton1Click);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&openocd_plugin_backend_win32Dialog::OnButton2Click);
    Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&openocd_plugin_backend_win32Dialog::OnCheckBox2Click);
    Connect(ID_TIMER1,wxEVT_TIMER,(wxObjectEventFunction)&openocd_plugin_backend_win32Dialog::OnTimer1Trigger);
    Connect(ID_TIMER2,wxEVT_TIMER,(wxObjectEventFunction)&openocd_plugin_backend_win32Dialog::OnTimer2Trigger);
    Connect(ID_TIMER3,wxEVT_TIMER,(wxObjectEventFunction)&openocd_plugin_backend_win32Dialog::OnTimer3Trigger);
    //*)
    Data_Init();

}

openocd_plugin_backend_win32Dialog::~openocd_plugin_backend_win32Dialog()
{
    //(*Destroy(openocd_plugin_backend_win32Dialog)
    //*)
    CloseHandle(Is_Started);
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

    {//��ӽӿ�����
        interface1->Insert("stlink-v1",0);
        interface1->Insert("stlink-v2",0);
        interface1->Insert("stlink-v2-1",0);
        interface1->Insert("cmsis-dap",0);
        interface1->Select(0);//ѡ��cmsis-dap
    }
    {//���Ŀ������
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
        target1->Select(2); //ѡ��stm32f1x
    }
    {//��Ӵ�������
        transport1->Insert("jtag",0);
        transport1->Insert("aice_jtag",0);
        transport1->Insert("swd",0);
        transport1->Insert("stlink_swim",0);
        transport1->Insert("hla_jtag",0);
        transport1->Insert("hla_swd",0);
        transport1->Select(3);//ѡ��swd
    }
    {//��ѡ�����������
        sprintf(cmdline,"openocd.exe -c \"telnet_port 55556\" -c \"gdb_port %s\" -f interface/%s.cfg -c \"transport select %s\" -f target/%s.cfg ",
                ((std::string)TextCtrl1->GetValue().c_str()).c_str(),
                ((std::string)interface1->GetValue().c_str()).c_str(),
                ((std::string)transport1->GetValue().c_str()).c_str(),
                ((std::string)target1->GetValue().c_str()).c_str()
                );
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
        if(val>65535) //�˿ڷǷ�
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
    //��־��ʱ��
    if(thread!=NULL)
    {
        if(thread->GetStatus()==1)//�����������
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
{//������ʱ��
     {//��ѡ�����������
        sprintf(cmdline,"openocd.exe -c \"telnet_port 55556\" -c \"gdb_port %s\" -f interface/%s.cfg -c \"transport select %s\" -f target/%s.cfg ",
                ((std::string)TextCtrl1->GetValue().c_str()).c_str(),
                ((std::string)interface1->GetValue().c_str()).c_str(),
                ((std::string)transport1->GetValue().c_str()).c_str(),
                ((std::string)target1->GetValue().c_str()).c_str()
                );
    }

    {//�Զ�����
    if(CheckBox2->IsChecked())
    {
        if(thread == NULL)
        {
                static int i=5;
                char buff[10];
                sprintf(buff,"%d",i);
                StaticText5->SetLabel(buff);
                if(i==0)
                {
                    thread=new Openocd_wxThread;
                    StaticText5->SetLabel("������");
                }
                i--;
        }
        else
        {
            CheckBox2->SetValue(false);
            CheckBox2->Disable();
            StaticText5->SetLabel("");
        }
    }

    }
    if(thread==NULL)
    {
        Button1->Enable();
        Button2->Disable();
    }
    else
    {
        Button1->Disable();
        Button2->Enable();
    }
    if(thread!=NULL)
        if(thread->GetStatus()==-1)
        {
        if(CheckBox1->IsChecked())
        {
            Openocd_wxThread *org=thread;
            thread=new Openocd_wxThread;
            delete org;
        }
        else
        {
            Timer1.Stop();
            wxMessageBox("openocd����ʧ��!�����������ݣ�\n1.Ӳ���Ƿ���ȷ���ӡ�\n2.�����Ƿ���ȷ��\n3.�Ƿ������������openocd��ͻ(��ռ��openocd�˿ڻ���ɱopenocd����)��\n","����",wxICON_ERROR);
            Close();
        }
        }
}

void openocd_plugin_backend_win32Dialog::OnTextCtrl3Text(wxCommandEvent& event)
{
    wxString val=TextCtrl3->GetValue();
    unsigned long i;
    if(!val.ToULong(&i,10))
    {
       TextCtrl3->SetValue("300000");
    }
}

void openocd_plugin_backend_win32Dialog::OnTextCtrl2Text(wxCommandEvent& event)
{
    wxString val=TextCtrl2->GetValue();
    unsigned long i;
    if(!val.ToULong(&i,10))
    {
       TextCtrl2->SetValue("3000");
    }
    else
    {
        Timer3.Start(i);
    }
}

void openocd_plugin_backend_win32Dialog::OnTimer3Trigger(wxTimerEvent& event)
{//��־����ʱ��
wxString val=TextCtrl3->GetValue();
unsigned long i;
if(!val.ToULong(&i,10))
{
    TextCtrl3->SetValue("300000");
}
else
{
    if(log2->GetValue().Len()>i)
    {
        wxString data=log2->GetValue();
        log2->SetValue(data.substr(data.length()-i,i));
    }
}

}

void openocd_plugin_backend_win32Dialog::OnButton1Click(wxCommandEvent& event)
{
     if(thread==NULL)
    {
         thread=new Openocd_wxThread;
         Timer2.Start();//������ʱ��

    }
}

void openocd_plugin_backend_win32Dialog::OnButton2Click(wxCommandEvent& event)
{
    Openocd_wxThread * org=thread;
    thread=NULL;
    if(org!=NULL)
        {
            delete org;
        }
}

void openocd_plugin_backend_win32Dialog::OnCheckBox2Click(wxCommandEvent& event)
{
    CheckBox2->Disable();
}

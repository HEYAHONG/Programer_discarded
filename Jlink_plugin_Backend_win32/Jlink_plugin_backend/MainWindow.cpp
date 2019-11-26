#include "MainWindow.h"

//(*InternalHeaders(MainWindow)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(MainWindow)
const long MainWindow::ID_RICHTEXTCTRL1 = wxNewId();
const long MainWindow::ID_BUTTON1 = wxNewId();
const long MainWindow::ID_TIMER1 = wxNewId();
const long MainWindow::ID_TIMER2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(MainWindow,wxDialog)
	//(*EventTable(MainWindow)
	//*)
END_EVENT_TABLE()

MainWindow::MainWindow(wxWindow* parent,wxWindowID id)
{
	//(*Initialize(MainWindow)
	Create(parent, id, _("Jlink_plugin_backend"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxCLOSE_BOX|wxMINIMIZE_BOX|wxSTATIC_BORDER, _T("id"));
	SetClientSize(wxSize(410,274));
	Info = new wxRichTextCtrl(this, ID_RICHTEXTCTRL1, wxEmptyString, wxPoint(0,72), wxSize(408,192), wxRE_MULTILINE|wxRE_READONLY, wxDefaultValidator, _T("ID_RICHTEXTCTRL1"));
	wxRichTextAttr rchtxtAttr_1;
	rchtxtAttr_1.SetBulletStyle(wxTEXT_ATTR_BULLET_STYLE_ALIGN_LEFT);
	Button1 = new wxButton(this, ID_BUTTON1, _("Connect"), wxPoint(0,8), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	Timer1.SetOwner(this, ID_TIMER1);
	Timer1.Start(1000, false);
	Timer1.Start();
	InfoTimer.SetOwner(this, ID_TIMER2);
	InfoTimer.Start(100, false);
	InfoTimer.Start();
	Center();

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MainWindow::OnButton1Click);
	Connect(ID_TIMER1,wxEVT_TIMER,(wxObjectEventFunction)&MainWindow::OnTimer1Trigger);
	Connect(ID_TIMER2,wxEVT_TIMER,(wxObjectEventFunction)&MainWindow::OnInfoTimerTrigger);
	Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&MainWindow::OnClose);
	//*)

    jlink_thread=NULL;
    //thread->Run();
}

MainWindow::~MainWindow()
{
	//(*Destroy(MainWindow)
	//*)
	Timer1.Stop();
	if(jlink_thread!=NULL)
        delete jlink_thread;
}




void MainWindow::OnTimer1Trigger(wxTimerEvent& event)
{
//Timer1.Stop();
//wxMessageBox("ok");
if(jlink_thread==NULL)
    {
        jlink_thread=new Jlink_wxThread;
    }
else
    {
        if(jlink_thread->GetStatus()==-1)
        {
            delete jlink_thread;
            jlink_thread=NULL;
        }
    }
//while(1);
}

void MainWindow::OnPanel1Paint(wxPaintEvent& event)
{
}



void MainWindow::OnClose(wxCloseEvent& event)
{
    EndModal(wxID_ABORT);
}

void MainWindow::OnInfoTimerTrigger(wxTimerEvent& event)
{
    static bool Is_Init=false;
    if(!Is_Init)
    {
        if(jlink_thread!=NULL && jlink_thread->GetStatus()==1)
            {
                Is_Init=true;

                unsigned char cmd[]="\n";

                jlink_thread->WriteStdin(cmd,sizeof(cmd));
                //ShowWindow(FindWindowA(NULL,jlink_thread->jlink_title),SW_HIDE);//显示窗口
                //Sleep(300);
                //ShowWindow(GetWindow(FindWindowA(NULL,jlink_thread->jlink_title),GW_CHILD),SW_SHOW);//显示窗口
            }

    }
    if(jlink_thread!=NULL)
    {
        if(jlink_thread->GetStatus()==1)
        {
            char buff[8192];
            memset(buff,0,sizeof(buff));
           if(jlink_thread->ReadStdout((unsigned char *)buff,sizeof(buff))>0)
            {
               // if(!jlink_thread->log.empty()) Info->AppendText(jlink_thread->log);
                //jlink_thread->log.clear();
                Info->AppendText(buff);
            }
            memset(buff,0,sizeof(buff));
            if(jlink_thread->ReadStderr((unsigned char *)buff,sizeof(buff))>0)
            {
                Info->AppendText((wxString)buff+"(ERROR)");
            }

        }
    }
}

void MainWindow::OnButton1Click(wxCommandEvent& event)
{
    //wxMessageBox(jlink_thread->log);
    unsigned char cmd[]="device ?\n";

    jlink_thread->WriteStdin(cmd,sizeof(cmd));
}

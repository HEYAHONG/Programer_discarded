///-----------------------------------------------------------------
///
/// @file      STM32_Data_ProgramerDlg.cpp
/// @author    ���Ǻ�
/// Created:   2019-11-18 13:18:06
/// @section   DESCRIPTION
///            STM32_Data_ProgramerDlg class implementation
///
///------------------------------------------------------------------

#include "STM32_Data_ProgramerDlg.h"

#include "FilePassWord.h"

//Do not add custom headers
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// STM32_Data_ProgramerDlg
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(STM32_Data_ProgramerDlg,wxDialog)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(STM32_Data_ProgramerDlg::OnClose)
END_EVENT_TABLE()
////Event Table End

STM32_Data_ProgramerDlg::STM32_Data_ProgramerDlg(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style)
{
	CreateGUIControls();
	Data_Init();
	
}

STM32_Data_ProgramerDlg::~STM32_Data_ProgramerDlg()
{
} 

void STM32_Data_ProgramerDlg::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End.
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	Info = new wxTextCtrl(this, ID_WXEDIT1_Info, _(""), wxPoint(3, 48), wxSize(338, 248), wxTE_READONLY | wxTE_LEFT | wxTE_MULTILINE, wxDefaultValidator, _("Info"));

	SetTitle(_("STM32_Data_Programer"));
	SetIcon(wxNullIcon);
	SetSize(8,8,357,334);
	Center();
	
	////GUI Items Creation End
}

void STM32_Data_ProgramerDlg::OnClose(wxCloseEvent& /*event*/)
{
	Destroy();
}

#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "dir.h"
#include "dirent.h"
#include "unistd.h"
#ifdef WIN32
#include "windows.h"
#endif
void STM32_Data_ProgramerDlg::Data_Init()
{
    DataDir="data/";
    while(access(((std::string)(DataDir+"/config.cfg").c_str()).c_str(),R_OK) )
    {
        Info->AppendText("ԭ����Ŀ¼������config.cfg\n");
        wxDirDialog dlg(this,"ѡ�����ݴ��Ŀ¼","data",wxDD_DIR_MUST_EXIST|wxDD_DEFAULT_STYLE);
        if(dlg.ShowModal()==wxID_OK) 
        {
            DataDir=dlg.GetPath();
            Info->AppendText((wxString)"�޸�����Ŀ¼Ϊ:"+DataDir+"\n");
        }
    }
    {//��DataDir���뻷������
        char buff[8192];
        sprintf(buff,"DataDir=%s",((std::string)DataDir.c_str()).c_str());
        putenv(buff); 
    } 
    
    {//��config������ʹ��putenv��ӵ���������
        FILE *fp=NULL;
        char buff[8192];
        memset(buff,0,sizeof(buff)); 
        fp=fopen(((std::string)(DataDir+"/config.cfg").c_str()).c_str(),"r");
        if(fp==NULL)
            {
                Info->AppendText("config.cfg����δ֪ԭ���޷���\n");
                return;
            }
        while(NULL != fgets(buff,sizeof(buff),fp))
        {
            if((buff[0]=='#') || (buff[0]==';') || (buff[0]=='/'))
                    continue;//����ע����
            for(size_t i=0;i<strlen(buff);i++)
                {//��ȥ��β�Ļس���
                    if(buff[i]=='\n' || buff[i] == '\r')
                        buff[i]=0; 
                }
            
            if(strstr(buff,"=")!= NULL)
                        if(putenv(buff))//�����еȺŵ�����ӵ��������� 
                            {
                                Info->AppendText("��ӻ�������ʧ��"); 
                            }
           // //���Զ�ȡ����
//            Info->AppendText(buff); 
            
            memset(buff,0,sizeof(buff));
        }
        fclose(fp);
         
    } 
    {
        wxString data=getenv("data");
        wxString sub="hex";
        if(!(data.Mid(data.Len()-3)).CmpNoCase(sub))
                {                     
                   Info->AppendText((wxString)"����:�����ļ�"+data+"δ����!\n");
                }
        else
            {//�����
                FilePassWord dlg(this);
                if(dlg.ShowModal()!= wxID_OK)
                    {
                        Info->AppendText("����:������֤���ִ���,������Ҫ������������Ŀ¼\n");
                    }; 
                dlg.Destroy();               
            } 
    }
    {//���Ի�������
    #ifdef WIN32
    //WinExec("cmd.exe",SW_SHOW);
    #endif 
    } 
}

///-----------------------------------------------------------------
///
/// @file      STM32_Data_ProgramerDlg.cpp
/// @author    何亚红
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
        Info->AppendText("原数据目录不存在config.cfg\n");
        wxDirDialog dlg(this,"选择数据存放目录","data",wxDD_DIR_MUST_EXIST|wxDD_DEFAULT_STYLE);
        if(dlg.ShowModal()==wxID_OK) 
        {
            DataDir=dlg.GetPath();
            Info->AppendText((wxString)"修改数据目录为:"+DataDir+"\n");
        }
    }
    {//将DataDir放入环境变量
        char buff[8192];
        sprintf(buff,"DataDir=%s",((std::string)DataDir.c_str()).c_str());
        putenv(buff); 
    } 
    
    {//将config的内容使用putenv添加到环境变量
        FILE *fp=NULL;
        char buff[8192];
        memset(buff,0,sizeof(buff)); 
        fp=fopen(((std::string)(DataDir+"/config.cfg").c_str()).c_str(),"r");
        if(fp==NULL)
            {
                Info->AppendText("config.cfg由于未知原因无法打开\n");
                return;
            }
        while(NULL != fgets(buff,sizeof(buff),fp))
        {
            if((buff[0]=='#') || (buff[0]==';') || (buff[0]=='/'))
                    continue;//跳过注释行
            for(size_t i=0;i<strlen(buff);i++)
                {//除去结尾的回车符
                    if(buff[i]=='\n' || buff[i] == '\r')
                        buff[i]=0; 
                }
            
            if(strstr(buff,"=")!= NULL)
                        if(putenv(buff))//将含有等号的行添加到环境变量 
                            {
                                Info->AppendText("添加环境变量失败"); 
                            }
           // //测试读取内容
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
                   Info->AppendText((wxString)"警告:数据文件"+data+"未加密!\n");
                }
        else
            {//密码框
                FilePassWord dlg(this);
                if(dlg.ShowModal()!= wxID_OK)
                    {
                        Info->AppendText("警告:密码验证出现错误,可能需要重新设置数据目录\n");
                    }; 
                dlg.Destroy();               
            } 
    }
    {//测试环境变量
    #ifdef WIN32
    //WinExec("cmd.exe",SW_SHOW);
    #endif 
    } 
}

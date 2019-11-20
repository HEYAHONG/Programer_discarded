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
	EVT_SET_FOCUS(STM32_Data_ProgramerDlg::STM32_Data_ProgramerDlgSetFocus)
	EVT_ENTER_WINDOW(STM32_Data_ProgramerDlg::STM32_Data_ProgramerDlgEnterWindow)
	EVT_INIT_DIALOG(STM32_Data_ProgramerDlg::STM32_Data_ProgramerDlgInitDialog)
	EVT_ACTIVATE(STM32_Data_ProgramerDlg::STM32_Data_ProgramerDlgActivate)
	
	EVT_TEXT(ID_WXEDIT1,STM32_Data_ProgramerDlg::WxEdit1Updated)
	EVT_TIMER(ID_WXTIMER1,STM32_Data_ProgramerDlg::WxTimer1Timer)
	EVT_BUTTON(ID_WXBUTTON1,STM32_Data_ProgramerDlg::WxButton1Click)
END_EVENT_TABLE()
////Event Table End

STM32_Data_ProgramerDlg::STM32_Data_ProgramerDlg(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style)
{
    hex_data=NULL;//赋初值 
	CreateGUIControls();
	
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

	WxEdit1 = new wxTextCtrl(this, ID_WXEDIT1, _("data/"), wxPoint(69, 2), wxSize(272, 26), wxTE_LEFT, wxDefaultValidator, _("WxEdit1"));

	WxStaticText1 = new wxStaticText(this, ID_WXSTATICTEXT1, _("数据目录："), wxPoint(5, 6), wxDefaultSize, 0, _("WxStaticText1"));

	WxTimer1 = new wxTimer();
	WxTimer1->SetOwner(this, ID_WXTIMER1);
	WxTimer1->Start(500);

	WxButton1 = new wxButton(this, ID_WXBUTTON1, _("打开"), wxPoint(348, 1), wxSize(70, 26), 0, wxDefaultValidator, _("WxButton1"));

	Info = new wxTextCtrl(this, ID_WXEDIT1_Info, _(""), wxPoint(3, 70), wxSize(415, 342), wxTE_READONLY | wxTE_LEFT | wxTE_MULTILINE, wxDefaultValidator, _("Info"));

	SetTitle(_("STM32_Data_Programer"));
	SetIcon(wxNullIcon);
	SetSize(8,8,436,449);
	Center();
	
	////GUI Items Creation End
}

void STM32_Data_ProgramerDlg::OnClose(wxCloseEvent& /*event*/)
{
    WxTimer1->Stop(); 
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
    //DataDir="data/";
    while(access(((std::string)(DataDir+"/config.cfg").c_str()).c_str(),R_OK) )
    {
        Info->AppendText("原数据目录不存在config.cfg\n");
        wxDirDialog dlg(this,"选择数据存放目录","data",wxDD_DIR_MUST_EXIST|wxDD_DEFAULT_STYLE);
        if(dlg.ShowModal()==wxID_OK) 
        {
            DataDir=dlg.GetPath();
            	{//更新数据目录显示框 
                	wxString Temp=DataDir;
    	            WxEdit1->Clear();
    	            WxEdit1->AppendText(Temp); 
                }
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
                    
                   {//打开hex文件
                     FILE *fp=fopen(((std::string) (DataDir+"/"+data).c_str()).c_str(),"rb");
                     if(fp == NULL)
                        {
                            Info->AppendText("hex文件不存在!\n");
                            return;
                        } 
                    if(hex_data!=NULL)
                             {
                                    free(hex_data);
                                    hex_data=NULL;
                             }
                    fseek(fp,0,SEEK_END);
                    size_t len = ftell(fp);
                    fseek(fp,0,SEEK_SET);                       
                    uint8_t *   data=(uint8_t *)malloc(len+50);
                    memset(data,0,len+50);
                     { 
                        size_t pos=0,read_num=0;
                        while(len-pos>=1)
                          {
                               read_num=fread(data+pos,1,32,fp); 
                               pos+=read_num;
                          };
                     }
                    if(strlen((const char *)data)>=len)
                        {
                            hex_data=data;
                            
                        }
                    fclose(fp);
                        
                   }
                    {
                     char buff[100];
                     memset(buff,0,sizeof(buff));
                     sprintf(buff,"%d",strlen((const char *)hex_data));                 
                     Info->AppendText((wxString)"警告:数据文件"+data+"(长度:"+buff+")未加密!\n");
                    }
                }
        else
            {//密码框
                FilePassWord dlg(this);
                if(dlg.ShowModal()!= wxID_OK)
                    {
                        Info->AppendText("警告:密码验证出现错误,可能需要重新设置数据目录\n");
                        dlg.Destroy();
                    }
                else
                    {//密码验证成功,将文件加载至内存
                         dlg.Destroy();
                         char *password=getenv("data_password");                         
                         uint8_t *data=NULL;
                         if(password==NULL)
                            {
                                Info->AppendText("内部错误,找不到密码项\n");
                                return;
                            } 
                          uint8_t aes_in[32],aes_out[32],aes_key[32];
                          memset(aes_key,0,sizeof(aes_key));
                          strcpy((char *)aes_key,password);
                          {
                                //uint8_t *w=aes_init(32);
                                //aes_key_expansion(aes_key,w);
                                struct aes256_ctx ctx;
                                aes256_set_decrypt_key(&ctx,aes_key);
                                {
                                    FILE *fp=fopen(((std::string)(DataDir+"/"+getenv("data")).c_str()).c_str(),"rb");
                                    if(fp != NULL)
                                    {
                                        fseek(fp,0,SEEK_END);
                                        size_t size=ftell(fp),pos=0;
                                        fseek(fp,0,SEEK_SET);                                                                                
                                        //fseek(fp,32,SEEK_SET);//跳过文件头
                                        fread(aes_out,32,1,fp);//跳过文件开头 
                                        if((size%32)!=0)
                                            { 
                                               Info->AppendText("文件可能存在错误!\n"); 
                                            } 
                                        data=(uint8_t *)malloc(size);
                                        memset(data,0,sizeof(data));
                                        do
                                        {
                                            memset(aes_in,0,sizeof(aes_in));
                                            memset(aes_out,0,sizeof(aes_out));
                                            size_t read_num=fread(aes_in,1,32,fp);
                                            if(read_num != 32)
                                                {
                                                    Info->AppendText("读取错误\n");
                                                }
                                            //aes_key_expansion(aes_key,w);
                                            //aes_inv_cipher(aes_in,aes_out,w);
                                            aes256_decrypt(&ctx,32,aes_out,aes_in);                                            
                                            //Info->AppendText(aes_out);                                             
                                            memcpy((char *)data+pos,(char *)aes_out,32);
                                            pos+=32;
                                            
                                        } while(size-pos>32);
                                        fclose(fp);
                                        
                                        {
                                            if(hex_data != NULL)
                                                {
                                                    free(hex_data);
                                                }
                                            hex_data=data;
                                            {
                                                char buff[100];
                                                memset(buff,0,sizeof(buff));
                                                sprintf(buff,"%d",strlen((char *)hex_data)); 
                                                
                                                //Info->AppendText(hex_data);
                                                
                                                Info->AppendText((wxString)"加密数据hex大小:"+buff+"B\n"); 
                                            }
                                        }
                                    }
                                                                        
                                }
                                
                               // free(w);
                          }                     
                    };                
            } 
    }
    {//测试环境变量
    #ifdef WIN32
    //WinExec("cmd.exe",SW_SHOW);
    #endif 
    } 
}




/*
 * STM32_Data_ProgramerDlgEnterWindow
 */
void STM32_Data_ProgramerDlg::STM32_Data_ProgramerDlgEnterWindow(wxMouseEvent& event)
{
	// insert your code here
		
}

/*
 * STM32_Data_ProgramerDlgInitDialog
 */
void STM32_Data_ProgramerDlg::STM32_Data_ProgramerDlgInitDialog(wxInitDialogEvent& event)
{
	// insert your code here
	//Data_Init();
}

/*
 * WxButton1Click
 */
void STM32_Data_ProgramerDlg::WxButton1Click(wxCommandEvent& event)
{
	// insert your code here
	Data_Init();

}

/*
 * STM32_Data_ProgramerDlgSetFocus
 */
void STM32_Data_ProgramerDlg::STM32_Data_ProgramerDlgSetFocus(wxFocusEvent& event)
{
	// insert your code here
	
}

/*
 * STM32_Data_ProgramerDlgActivate
 */
void STM32_Data_ProgramerDlg::STM32_Data_ProgramerDlgActivate(wxActivateEvent& event)
{
	// insert your code here
	
}

/*
 * WxTimer1Timer
 */
void STM32_Data_ProgramerDlg::WxTimer1Timer(wxTimerEvent& event)
{
	// insert your code here
	{
        static bool Is_Init=false;
        if(!Is_Init)
        {
            Is_Init=true;
            WxEdit1->Clear();
            WxEdit1->AppendText("data/");
            Data_Init();
            
        }
    }
}

/*
 * WxEdit1Updated
 */
void STM32_Data_ProgramerDlg::WxEdit1Updated(wxCommandEvent& event)
{
	// insert your code here
	DataDir=WxEdit1->GetValue();
}

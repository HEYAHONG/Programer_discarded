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
	EVT_BUTTON(ID_WXBUTTON3,STM32_Data_ProgramerDlg::WxButton3Click)
	EVT_BUTTON(ID_WXBUTTON2,STM32_Data_ProgramerDlg::WxButton2Click)
	EVT_TIMER(ID_WXTIMER1,STM32_Data_ProgramerDlg::WxTimer1Timer)
	
	EVT_TEXT(ID_WXEDIT1,STM32_Data_ProgramerDlg::WxEdit1Updated)
	EVT_BUTTON(ID_WXBUTTON1,STM32_Data_ProgramerDlg::WxButton1Click)
END_EVENT_TABLE()
////Event Table End

STM32_Data_ProgramerDlg::STM32_Data_ProgramerDlg(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style)
{
    hex_data=NULL;//赋初值 
    {//将窗口指针地址放入环境变量
        uint64_t Dialog_Ptr=(uint64_t)this;
        char env[200];
        memset(env,0,sizeof(env));
        sprintf(env,"Dialog_Ptr=%016X",Dialog_Ptr); 
        putenv(env);
    } 
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

	WxButton3 = new wxButton(this, ID_WXBUTTON3, _("烧录"), wxPoint(242, 70), wxSize(101, 29), 0, wxDefaultValidator, _("WxButton3"));

	WxCheckBox2 = new wxCheckBox(this, ID_WXCHECKBOX2, _("循环烧录"), wxPoint(158, 77), wxSize(73, 16), 0, wxDefaultValidator, _("WxCheckBox2"));

	WxCheckBox1 = new wxCheckBox(this, ID_WXCHECKBOX1, _("更新hex"), wxPoint(71, 77), wxSize(73, 16), 0, wxDefaultValidator, _("WxCheckBox1"));
	WxCheckBox1->SetValue(true);

	WxStaticLine2 = new wxStaticLine(this, ID_WXSTATICLINE2, wxPoint(0, 106), wxSize(414, -1), wxLI_HORIZONTAL);
	WxStaticLine2->SetForegroundColour(wxColour(0,0,0));

	WxStaticLine1 = new wxStaticLine(this, ID_WXSTATICLINE1, wxPoint(1, 65), wxSize(414, -1), wxLI_HORIZONTAL);
	WxStaticLine1->SetForegroundColour(wxColour(0,0,0));

	WxButton2 = new wxButton(this, ID_WXBUTTON2, _("搜索插件"), wxPoint(353, 33), wxSize(64, 24), 0, wxDefaultValidator, _("WxButton2"));

	WxStaticText3 = new wxStaticText(this, ID_WXSTATICTEXT3, _("烧录插件："), wxPoint(185, 35), wxDefaultSize, 0, _("WxStaticText3"));

	WxStaticText2 = new wxStaticText(this, ID_WXSTATICTEXT2, _("更新插件："), wxPoint(2, 35), wxDefaultSize, 0, _("WxStaticText2"));

	wxArrayString arrayStringFor_WxComboBox2;
	WxComboBox2 = new wxComboBox(this, ID_WXCOMBOBOX2, _(""), wxPoint(242, 33), wxSize(107, 25), arrayStringFor_WxComboBox2, wxTE_READONLY, wxDefaultValidator, _("WxComboBox2"));

	wxArrayString arrayStringFor_WxComboBox1;
	WxComboBox1 = new wxComboBox(this, ID_WXCOMBOBOX1, _(""), wxPoint(60, 33), wxSize(121, 25), arrayStringFor_WxComboBox1, wxTE_READONLY, wxDefaultValidator, _("WxComboBox1"));

	WxTimer1 = new wxTimer();
	WxTimer1->SetOwner(this, ID_WXTIMER1);
	WxTimer1->Start(300);

	WxEdit1 = new wxTextCtrl(this, ID_WXEDIT1, _("data/"), wxPoint(69, 2), wxSize(272, 26), wxTE_LEFT, wxDefaultValidator, _("WxEdit1"));

	WxStaticText1 = new wxStaticText(this, ID_WXSTATICTEXT1, _("数据目录："), wxPoint(5, 6), wxDefaultSize, 0, _("WxStaticText1"));

	WxButton1 = new wxButton(this, ID_WXBUTTON1, _("打开"), wxPoint(348, 1), wxSize(70, 26), 0, wxDefaultValidator, _("WxButton1"));

	Info = new wxTextCtrl(this, ID_WXEDIT1_Info, _(""), wxPoint(2, 116), wxSize(415, 172), wxTE_READONLY | wxTE_LEFT | wxTE_MULTILINE, wxDefaultValidator, _("Info"));

	SetTitle(_("STM32_Data_Programer"));
	SetIcon(wxNullIcon);
	SetSize(8,8,436,330);
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
            WxTimer1->Stop();
            WxTimer1->Start(3000);
            WxEdit1->Clear();
            WxEdit1->AppendText("data/");
            Data_Init();
            search_plugin();
            
        }
    }
    {   
        static bool Is_Running=false;
        if(!Is_Running)//不执行重复烧写  
            if(WxCheckBox2->IsChecked() && WxButton3->IsEnabled())//循环烧写被选中 
            {
                Is_Running=true;
                WxButton3->Disable();
                start_flash(); 
                Is_Running=false;
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
#include "unistd.h"
#include "dirent.h"
void STM32_Data_ProgramerDlg::search_plugin()
{//搜索plugin目录，类型为1的放入WxComboBox1，类型为2的放入WxComboBox2
if(access("plugin/",4))
{
    Info->AppendText("指定插件目录不存在!\n");
    return;
}
{//遍历目录
  DIR *dir=NULL;
  if((dir=opendir("plugin/"))==NULL)
  {
    Info->AppendText("打开插件目录失败!\n");
    return;
  } 
  struct dirent * file=NULL;
  {//清空控件上原有的内容
    WxComboBox1->Clear();
    WxComboBox2->Clear(); 
  }
  while((file=readdir(dir))!=NULL)
  { 
        //if(file->d_type==DT_REG)//正常文件 
        {
            char path[8192];
            memset(path,0,sizeof(path));
            sprintf(path,"plugin/%s",file->d_name);
            void *dll=dlopen(path,RTLD_GLOBAL);
            if(dll==NULL)
                {
                    continue;
                }
             get_plugin_type_t  get_plugin_type=(get_plugin_type_t)dlsym(dll,"get_plugin_type");
             if(dlerror()==NULL)
                 {
                        unsigned int type=(*get_plugin_type)();
                        if(type==1)
                        {
                          WxComboBox1->Insert(file->d_name,0); 
                          WxComboBox1->Select(0);                             
                        };
                        if(type==2)
                        {
                          WxComboBox2->Insert(file->d_name,0);  
                          WxComboBox2->Select(0); 
                        };
                 }
             dlclose(dll);            
        }
        
  }
  closedir(dir); 
}    
}

/*
 * WxButton2Click
 */
void STM32_Data_ProgramerDlg::WxButton2Click(wxCommandEvent& event)
{
	// insert your code here
	search_plugin(); 
}

void STM32_Data_ProgramerDlg::start_flash()
{
	// insert your code here
	process_hex_t       process_hex=NULL;
    process_program_t   process_program=NULL;
    void * dll_hex=NULL;
    void * dll_program=NULL;
    
    
	WxButton3->Disable();
	WxButton3->SetBackgroundColour(wxNullColour);
	
	Info->Clear();
	Info->AppendText("开始烧写\n");
    {
        Info->AppendText("检查hex数据\n");
        if((hex_data==NULL) || (strlen((char *)hex_data) ==0) )
            {
                Info->AppendText("hex数据不存在\n");
                WxButton3->SetBackgroundColour(wxColor(255,0,0));
                goto EndOfStart_Flash;
            }  
        size_t pos;
        for(pos=0;pos<strlen((char *)hex_data);pos++)
        {
            if(!((hex_data[pos] >= 'A' && hex_data[pos] <='F')||
                 (hex_data[pos] >= 'a' && hex_data[pos] <='f')||
                 (hex_data[pos] >= '0' && hex_data[pos] <='9')||
                 (hex_data[pos] == ':' || hex_data[pos]=='\n' ||
                  hex_data[pos] =='\r') ))
            {//检测到非法字符 
                Info->AppendText("hex数据中检测到非法字符\n");
                WxButton3->SetBackgroundColour(wxColor(255,0,0));
                goto EndOfStart_Flash; 
            }
        } 
        {
            char buff[8192];
            sprintf(buff,"hex数据长度:%d\n",strlen((char *)hex_data));
            Info->AppendText(buff);
        }       
    }
    //加载插件
    if(WxCheckBox1->IsChecked())
    {//加载更新hex插件
        char path[8192];
        sprintf(path,"plugin/%s",((std::string)WxComboBox1->GetValue().c_str()).c_str());
        if((dll_hex=dlopen(path,RTLD_GLOBAL))==NULL)
        {
            Info->AppendText("打开更新插件失败！\n"); 
            WxButton3->SetBackgroundColour(wxColor(255,0,0));
            goto EndOfStart_Flash;
        } 
        process_hex=(process_hex_t)dlsym(dll_hex,"process_hex");
        if(dlerror()!=NULL)
        {
            dlclose(dll_hex);
            Info->AppendText("加载更新插件失败！\n");
            WxButton3->SetBackgroundColour(wxColor(255,0,0));
            goto EndOfStart_Flash;
        }
        Info->AppendText("更新插件加载成功！\n");
    }
    
    {//加载烧录插件
        char path[8192];
        sprintf(path,"plugin/%s",((std::string)WxComboBox2->GetValue().c_str()).c_str());
        if((dll_hex=dlopen(path,RTLD_GLOBAL))==NULL)
        {
            Info->AppendText("打开烧录插件失败！\n"); 
            WxButton3->SetBackgroundColour(wxColor(255,0,0));
            goto EndOfStart_Flash;
        } 
        process_program=(process_program_t)dlsym(dll_hex,"process_program");
        if(dlerror()!=NULL)
        {
            dlclose(dll_hex);
            Info->AppendText("加载烧录插件失败！\n");
            WxButton3->SetBackgroundColour(wxColor(255,0,0));
            goto EndOfStart_Flash;
        }
        Info->AppendText("烧录插件加载成功！\n"); 
    }
    
    {//执行更新
        if(WxCheckBox1->IsChecked())
        {
            Info->AppendText("开始更新\n");
            if(process_hex(hex_data)<=0)
            {
              Info->AppendText("更新失败\n"); 
              WxButton3->SetBackgroundColour(wxColor(255,0,0));
              goto AbortOp;  
            } 
        } 
         
    }
    
    {//执行烧录
        Info->AppendText("开始烧录\n");
        if(process_program(hex_data)<=0)
        {
            Info->AppendText("烧录失败\n"); 
            WxButton3->SetBackgroundColour(wxColor(255,0,0));
            goto AbortOp;
        } 
        
    } 
            
     
    WxButton3->SetBackgroundColour(wxColor(0,255,0));
    Info->AppendText("操作完成!\n");
AbortOp:
	//卸载插件
    if(dll_hex != NULL)
        dlclose(dll_hex);
    if(dll_program!=NULL)
        dlclose(dll_program); 
EndOfStart_Flash:
	WxButton3->Enable();
}

/*
 * WxButton3Click
 */
void STM32_Data_ProgramerDlg::WxButton3Click(wxCommandEvent& event)
{
	// insert your code here
	start_flash(); 
}
wxTextCtrl * STM32_Data_ProgramerDlg::Get_Info_Ctl()
{
    return Info; 
}

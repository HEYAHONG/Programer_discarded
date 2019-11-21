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
    hex_data=NULL;//����ֵ 
    {//������ָ���ַ���뻷������
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

	WxButton3 = new wxButton(this, ID_WXBUTTON3, _("��¼"), wxPoint(242, 70), wxSize(101, 29), 0, wxDefaultValidator, _("WxButton3"));

	WxCheckBox2 = new wxCheckBox(this, ID_WXCHECKBOX2, _("ѭ����¼"), wxPoint(158, 77), wxSize(73, 16), 0, wxDefaultValidator, _("WxCheckBox2"));

	WxCheckBox1 = new wxCheckBox(this, ID_WXCHECKBOX1, _("����hex"), wxPoint(71, 77), wxSize(73, 16), 0, wxDefaultValidator, _("WxCheckBox1"));
	WxCheckBox1->SetValue(true);

	WxStaticLine2 = new wxStaticLine(this, ID_WXSTATICLINE2, wxPoint(0, 106), wxSize(414, -1), wxLI_HORIZONTAL);
	WxStaticLine2->SetForegroundColour(wxColour(0,0,0));

	WxStaticLine1 = new wxStaticLine(this, ID_WXSTATICLINE1, wxPoint(1, 65), wxSize(414, -1), wxLI_HORIZONTAL);
	WxStaticLine1->SetForegroundColour(wxColour(0,0,0));

	WxButton2 = new wxButton(this, ID_WXBUTTON2, _("�������"), wxPoint(353, 33), wxSize(64, 24), 0, wxDefaultValidator, _("WxButton2"));

	WxStaticText3 = new wxStaticText(this, ID_WXSTATICTEXT3, _("��¼�����"), wxPoint(185, 35), wxDefaultSize, 0, _("WxStaticText3"));

	WxStaticText2 = new wxStaticText(this, ID_WXSTATICTEXT2, _("���²����"), wxPoint(2, 35), wxDefaultSize, 0, _("WxStaticText2"));

	wxArrayString arrayStringFor_WxComboBox2;
	WxComboBox2 = new wxComboBox(this, ID_WXCOMBOBOX2, _(""), wxPoint(242, 33), wxSize(107, 25), arrayStringFor_WxComboBox2, wxTE_READONLY, wxDefaultValidator, _("WxComboBox2"));

	wxArrayString arrayStringFor_WxComboBox1;
	WxComboBox1 = new wxComboBox(this, ID_WXCOMBOBOX1, _(""), wxPoint(60, 33), wxSize(121, 25), arrayStringFor_WxComboBox1, wxTE_READONLY, wxDefaultValidator, _("WxComboBox1"));

	WxTimer1 = new wxTimer();
	WxTimer1->SetOwner(this, ID_WXTIMER1);
	WxTimer1->Start(300);

	WxEdit1 = new wxTextCtrl(this, ID_WXEDIT1, _("data/"), wxPoint(69, 2), wxSize(272, 26), wxTE_LEFT, wxDefaultValidator, _("WxEdit1"));

	WxStaticText1 = new wxStaticText(this, ID_WXSTATICTEXT1, _("����Ŀ¼��"), wxPoint(5, 6), wxDefaultSize, 0, _("WxStaticText1"));

	WxButton1 = new wxButton(this, ID_WXBUTTON1, _("��"), wxPoint(348, 1), wxSize(70, 26), 0, wxDefaultValidator, _("WxButton1"));

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
        Info->AppendText("ԭ����Ŀ¼������config.cfg\n");
        wxDirDialog dlg(this,"ѡ�����ݴ��Ŀ¼","data",wxDD_DIR_MUST_EXIST|wxDD_DEFAULT_STYLE);
        if(dlg.ShowModal()==wxID_OK) 
        {
            DataDir=dlg.GetPath();
            	{//��������Ŀ¼��ʾ�� 
                	wxString Temp=DataDir;
    	            WxEdit1->Clear();
    	            WxEdit1->AppendText(Temp); 
                }
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
                    
                   {//��hex�ļ�
                     FILE *fp=fopen(((std::string) (DataDir+"/"+data).c_str()).c_str(),"rb");
                     if(fp == NULL)
                        {
                            Info->AppendText("hex�ļ�������!\n");
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
                     Info->AppendText((wxString)"����:�����ļ�"+data+"(����:"+buff+")δ����!\n");
                    }
                }
        else
            {//�����
                FilePassWord dlg(this);
                if(dlg.ShowModal()!= wxID_OK)
                    {
                        Info->AppendText("����:������֤���ִ���,������Ҫ������������Ŀ¼\n");
                        dlg.Destroy();
                    }
                else
                    {//������֤�ɹ�,���ļ��������ڴ�
                         dlg.Destroy();
                         char *password=getenv("data_password");                         
                         uint8_t *data=NULL;
                         if(password==NULL)
                            {
                                Info->AppendText("�ڲ�����,�Ҳ���������\n");
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
                                        //fseek(fp,32,SEEK_SET);//�����ļ�ͷ
                                        fread(aes_out,32,1,fp);//�����ļ���ͷ 
                                        if((size%32)!=0)
                                            { 
                                               Info->AppendText("�ļ����ܴ��ڴ���!\n"); 
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
                                                    Info->AppendText("��ȡ����\n");
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
                                                
                                                Info->AppendText((wxString)"��������hex��С:"+buff+"B\n"); 
                                            }
                                        }
                                    }
                                                                        
                                }
                                
                               // free(w);
                          }                     
                    };                
            } 
    }
    {//���Ի�������
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
        if(!Is_Running)//��ִ���ظ���д  
            if(WxCheckBox2->IsChecked() && WxButton3->IsEnabled())//ѭ����д��ѡ�� 
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
{//����pluginĿ¼������Ϊ1�ķ���WxComboBox1������Ϊ2�ķ���WxComboBox2
if(access("plugin/",4))
{
    Info->AppendText("ָ�����Ŀ¼������!\n");
    return;
}
{//����Ŀ¼
  DIR *dir=NULL;
  if((dir=opendir("plugin/"))==NULL)
  {
    Info->AppendText("�򿪲��Ŀ¼ʧ��!\n");
    return;
  } 
  struct dirent * file=NULL;
  {//��տؼ���ԭ�е�����
    WxComboBox1->Clear();
    WxComboBox2->Clear(); 
  }
  while((file=readdir(dir))!=NULL)
  { 
        //if(file->d_type==DT_REG)//�����ļ� 
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
	Info->AppendText("��ʼ��д\n");
    {
        Info->AppendText("���hex����\n");
        if((hex_data==NULL) || (strlen((char *)hex_data) ==0) )
            {
                Info->AppendText("hex���ݲ�����\n");
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
            {//��⵽�Ƿ��ַ� 
                Info->AppendText("hex�����м�⵽�Ƿ��ַ�\n");
                WxButton3->SetBackgroundColour(wxColor(255,0,0));
                goto EndOfStart_Flash; 
            }
        } 
        {
            char buff[8192];
            sprintf(buff,"hex���ݳ���:%d\n",strlen((char *)hex_data));
            Info->AppendText(buff);
        }       
    }
    //���ز��
    if(WxCheckBox1->IsChecked())
    {//���ظ���hex���
        char path[8192];
        sprintf(path,"plugin/%s",((std::string)WxComboBox1->GetValue().c_str()).c_str());
        if((dll_hex=dlopen(path,RTLD_GLOBAL))==NULL)
        {
            Info->AppendText("�򿪸��²��ʧ�ܣ�\n"); 
            WxButton3->SetBackgroundColour(wxColor(255,0,0));
            goto EndOfStart_Flash;
        } 
        process_hex=(process_hex_t)dlsym(dll_hex,"process_hex");
        if(dlerror()!=NULL)
        {
            dlclose(dll_hex);
            Info->AppendText("���ظ��²��ʧ�ܣ�\n");
            WxButton3->SetBackgroundColour(wxColor(255,0,0));
            goto EndOfStart_Flash;
        }
        Info->AppendText("���²�����سɹ���\n");
    }
    
    {//������¼���
        char path[8192];
        sprintf(path,"plugin/%s",((std::string)WxComboBox2->GetValue().c_str()).c_str());
        if((dll_hex=dlopen(path,RTLD_GLOBAL))==NULL)
        {
            Info->AppendText("����¼���ʧ�ܣ�\n"); 
            WxButton3->SetBackgroundColour(wxColor(255,0,0));
            goto EndOfStart_Flash;
        } 
        process_program=(process_program_t)dlsym(dll_hex,"process_program");
        if(dlerror()!=NULL)
        {
            dlclose(dll_hex);
            Info->AppendText("������¼���ʧ�ܣ�\n");
            WxButton3->SetBackgroundColour(wxColor(255,0,0));
            goto EndOfStart_Flash;
        }
        Info->AppendText("��¼������سɹ���\n"); 
    }
    
    {//ִ�и���
        if(WxCheckBox1->IsChecked())
        {
            Info->AppendText("��ʼ����\n");
            if(process_hex(hex_data)<=0)
            {
              Info->AppendText("����ʧ��\n"); 
              WxButton3->SetBackgroundColour(wxColor(255,0,0));
              goto AbortOp;  
            } 
        } 
         
    }
    
    {//ִ����¼
        Info->AppendText("��ʼ��¼\n");
        if(process_program(hex_data)<=0)
        {
            Info->AppendText("��¼ʧ��\n"); 
            WxButton3->SetBackgroundColour(wxColor(255,0,0));
            goto AbortOp;
        } 
        
    } 
            
     
    WxButton3->SetBackgroundColour(wxColor(0,255,0));
    Info->AppendText("�������!\n");
AbortOp:
	//ж�ز��
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

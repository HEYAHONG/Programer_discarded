///-----------------------------------------------------------------
///
/// @file      STM32_Data_GeneratorDlg.cpp
/// @author    ���Ǻ�
/// Created:   2019-11-13 10:00:42
/// @section   DESCRIPTION
///            STM32_Data_GeneratorDlg class implementation
///
///------------------------------------------------------------------

#include "STM32_Data_GeneratorDlg.h"

//Do not add custom headers
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// STM32_Data_GeneratorDlg
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(STM32_Data_GeneratorDlg,wxDialog)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(STM32_Data_GeneratorDlg::OnClose)
	EVT_BUTTON(ID_WXBUTTON2,STM32_Data_GeneratorDlg::WxButton_SaveClick)
	EVT_BUTTON(ID_WXBUTTON1_OPEN,STM32_Data_GeneratorDlg::WxButton_OpenClick)
END_EVENT_TABLE()
////Event Table End

STM32_Data_GeneratorDlg::STM32_Data_GeneratorDlg(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style)
{
	CreateGUIControls();
}

STM32_Data_GeneratorDlg::~STM32_Data_GeneratorDlg()
{
} 

void STM32_Data_GeneratorDlg::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End.
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	WxRichTextCtrl1 = new wxRichTextCtrl(this, ID_WXRICHTEXTCTRL1, _(""), wxPoint(10, 46), wxSize(373, 183), wxRE_READONLY, wxDefaultValidator, _("WxRichTextCtrl1"));
	WxRichTextCtrl1->SetMaxLength(0);
	WxRichTextCtrl1->AppendText(_("����Ѿ�ʹ��IAR 7����õĳ����ļ�����������"));
	WxRichTextCtrl1->AppendText(_("��ʽ:"));
	WxRichTextCtrl1->AppendText(_("*.out |"));
	WxRichTextCtrl1->AppendText(_("*.hex |"));
	WxRichTextCtrl1->AppendText(_("*.bin |"));
	WxRichTextCtrl1->AppendText(_("*.elf  "));
	WxRichTextCtrl1->SetFocus();
	WxRichTextCtrl1->SetInsertionPointEnd();

	WxButton_Save = new wxButton(this, ID_WXBUTTON2, _("���������ļ�"), wxPoint(194, 8), wxSize(186, 33), 0, wxDefaultValidator, _("WxButton_Save"));
	WxButton_Save->Enable(false);

	WxButton_Open = new wxButton(this, ID_WXBUTTON1_OPEN, _("���ļ�"), wxPoint(12, 7), wxSize(180, 33), 0, wxDefaultValidator, _("WxButton_Open"));

	SetTitle(_("STM32_Data_Generator"));
	SetIcon(wxNullIcon);
	SetSize(8,8,403,275);
	Center();
	
	////GUI Items Creation End
}

void STM32_Data_GeneratorDlg::OnClose(wxCloseEvent& /*event*/)
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
#include "FileCrypto.h"
/*
 * WxButton_SaveClick
 */
void STM32_Data_GeneratorDlg::WxButton_SaveClick(wxCommandEvent& event)
{
	// insert your code here
	mkdir("data");
	if(access("data",0))
	   {
            ErrorMessage("��װĿ¼���ܲ���д!\n","����");
            return; 
        }
    {//ת��elf�ļ�Ϊhex�ļ�
        if(!type.compare("out") || !type.compare("elf"))
        {
            char cmd[8192];
            remove("data/data.hex");//ɾ��ԭ�еĳ����ļ� 
            sprintf(cmd,"objcopy -I elf32-little -O ihex \"%s\" data/data.hex",((std::string)FilePath.c_str()).c_str());
            #ifdef WIN32
            WinExec(cmd,SW_HIDE);
            Sleep(3000); 
            #else
            system(cmd);
            #endif 
            
        } 
        else
        {
          if(!type.compare("hex"))
            {
                char cmd[8192];
                remove("data/data.hex");//ɾ��ԭ�еĳ����ļ� 
                sprintf(cmd,"objcopy -I ihex -O ihex \"%s\" data/data.hex",((std::string)FilePath.c_str()).c_str());
                #ifdef WIN32
                WinExec(cmd,SW_HIDE);
                Sleep(3000); 
                #else
                system(cmd);
                #endif 
            }
          else if(!type.compare("bin"))
            {
                char cmd[8192];
                remove("data/data.hex");//ɾ��ԭ�еĳ����ļ� 
                sprintf(cmd,"objcopy  --change-addresses 0x08000000 -I binary -O ihex \"%s\" data/data.hex",((std::string)FilePath.c_str()).c_str());
                #ifdef WIN32
                WinExec(cmd,SW_HIDE);
                Sleep(3000); 
                #else
                system(cmd);
                #endif  
                ErrorMessage("��bin�ļ�ת����hex�������ڵ��ԣ�ֻ����������!","˵��"); 
            }
        }
        {
            if(access("data/data.hex",6))
            {
              ErrorMessage("����װĿ¼���ܲ���д!","����");
              return;  
            } 
        } 
        
    } 
    
    remove("data/config.cfg");
    {//���������ļ�data/config.cfg
        FILE *fp=fopen("data/config.cfg","w");
        if(fp == NULL)
            {
               ErrorMessage("����װĿ¼���ܲ���д!\n","����");
               return;   
            } 
        fprintf(fp,"FilePath=%s\n",((std::string)FilePath.c_str()).c_str());
        fprintf(fp,"Type=%s\n",((std::string)type.c_str()).c_str());
        fprintf(fp,"symbol=%s\n",((std::string)symbol.c_str()).c_str());
        fprintf(fp,"symbol_start=%08X\n",symbol_start);
        fprintf(fp,"symbol_length=%u\n",symbol_length);
      //  fprintf(fp,"data=data.Dat");
        
        
        fclose(fp);
        
    }
    {//��������
        {//ѯ���Ƿ����
            wxMessageDialog msg(this,"�Ƿ�Գ�����м���!","ѡ��",wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
            if(wxID_YES==msg.ShowModal())
            {
                
                {
                    FileCrypto dlg(this);
                    dlg.ShowModal();
                    dlg.Destroy();
                }
                
               remove("data/data.hex");//ɾ��hex�ļ� 
               
               //�����ļ�λ�� 
               FILE *fp=fopen("data/config.cfg","a");
                if(fp == NULL)
                    {
                       ErrorMessage("����װĿ¼���ܲ���д!\n","����");
                       return;   
                    } 
                fprintf(fp,"data=data.Dat");
                fclose(fp);
            }
            else
            {
                //�����ļ�λ�� 
                 FILE *fp=fopen("data/config.cfg","a");
                if(fp == NULL)
                    {
                       ErrorMessage("����װĿ¼���ܲ���д!\n","����");
                       return;   
                    } 
                fprintf(fp,"data=data.hex");
                fclose(fp);
                
                remove("data/data.Dat");//ɾ��Dat�ļ�
                ErrorMessage("δ���ܣ�ֱ��ʹ��hex�ļ���","˵��");
            }
             
        } 
        
    }
	{//��data�ļ��� 
	   #ifdef WIN32
	   char buff[100];
	   sprintf(buff,"explorer.exe data\\");
	   WinExec(buff,SW_SHOW);
       #endif 
    }
	
}

void STM32_Data_GeneratorDlg:: ErrorMessage(wxString msg,wxString title)
{
    wxMessageDialog temp(this,msg,title);
    temp.ShowModal();
} 

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include "config.h" 
#include <bfd.h>
/*
 * WxButton_OpenClick
 */
void STM32_Data_GeneratorDlg::WxButton_OpenClick(wxCommandEvent& event)
{
	// insert your code here
	WxButton_Save->Disable();//�رձ��水ť 
	
	FilePath="";
    type="";
	{//��ȡ�ļ�·��
     wxFileDialog temp(this,"ѡ������ļ��������elf��ʽ��:","","","out files|*.out|hex files|*.hex|bin files|*.bin|elf files|*.elf|axf files|*.axf",wxFD_DEFAULT_STYLE|wxFD_FILE_MUST_EXIST);
     if(temp.ShowModal()!=wxID_OK)
        {
           ErrorMessage("����ȡ��!\n","����");
           return; 
        }
        {   //������ļ��Ի����ȡ������ 
            switch(temp.GetFilterIndex())
            {
                case 0:
                        type="out";
                        break;
                case 1:
                        type="hex";
                        break;
                case 2:
                        type="bin";
                        break;
                case 3:
                case 4:     //axf��ʽҲ��elf 
                        type="elf";
                        break;
                default:
                    ErrorMessage("��֧�ֵ��ļ�����!\n","����");
                    return;
                    
            }
            {
                FilePath=temp.GetPath();
            }
            
        }
        {//��������
                //ErrorMessage(FilePath,type); 
        }
    }
    
   /* {//�ݲ�֧��hex��bin�ļ�
        if(!type.compare("hex") || !type.compare("bin"))
        {
            ErrorMessage("��ʱֻ֧��elf�ļ���ʽ(out�ļ���elf�ļ�)","����");
            return;
        } 
             
    }*/
    //�����Ӧ�ı���
    symbol="";
    symbol_start=0;
    symbol_length=0; 
    
    {//�������ű�
        
    if(!type.compare("out") || !type.compare("elf")) 
        {//elf�ļ�
            //{ //����symbol.txt 
//             char cmd[8192];
//             remove("symbol.txt");
//             sprintf(cmd,"objdump -t %s > symbol.txt",((std::string)(FilePath.c_str())).c_str());
//             #ifdef WIN32
//             char cmd_win[8192];
//             sprintf(cmd_win,"cmd.exe /c \"%s\"",cmd);
//             if(WinExec(cmd_win,SW_HIDE)<32)
//                {
//                    ErrorMessage((wxString)"ִ��"+cmd_win+"ʧ��!","����");
//                    return;        
//                };
//             Sleep(3000); 
//             #else
//             system(cmd);
//             #endif
//            }
//            {//�ж��ļ��Ƿ���� 
//               if(access("symbol.txt",0)) 
//                {
//                    ErrorMessage("�����ļ����ܲ����ڣ����鰲װλ���Ƿ��д!\n","����"); 
//                    return; 
//                }
//            }
            {//�򿪱���ѡ�񴰿� 
               Address_Select temp(this);
               
               {//ʹ��libbfd����elf32�ļ�
               #define MIN(a,b) ((a)>(b)?(b):(a))
               #define ABS(a)  ((a)>0?(a):(-(a)))
               bfd_init();
                  bfd *ibfd;
                  ibfd = bfd_openr(((std::string)FilePath.c_str()).c_str(),NULL);
                  if(ibfd==NULL)
                    {
                        ErrorMessage("�򿪳����ļ�ʧ��!\n");
                        return;
                    };
                   //����ʽ 
                  char **matching;
                  bfd_check_format_matches(ibfd, bfd_object, &matching);
                  {//��������
                      long storage_needed;
                      asymbol **symbol_table;
                      long number_of_symbols;
                      long i;
              
                      storage_needed = bfd_get_symtab_upper_bound(ibfd);
              
                      symbol_table =  (asymbol **)(unsigned long)malloc(storage_needed);
                      number_of_symbols =  bfd_canonicalize_symtab (ibfd, symbol_table);
                     for(i=0;i<number_of_symbols;i++)
                     {
                             if (symbol_table[i]->section==NULL) continue; //����Ч 
                             if(!(symbol_table[i]->section->flags & SEC_READONLY)) continue; //ֻ������ 
                             if(symbol_table[i]->flags & BSF_FUNCTION)                continue; //�Ǻ������� 
                             if(!(symbol_table[i]->flags & BSF_GLOBAL))               continue; //ȫ�ַ��� 
                        //     printf("Section %s,size:%d, Name:%s,Value:%X\n",symbol_table[i]->section->name,
//                                                                            symbol_table[i]->udata.i,
//                                                                            bfd_asymbol_name(symbol_table[i]),
//                                                                            bfd_asymbol_value(symbol_table[i]));
                             if((strstr(bfd_asymbol_name(symbol_table[i]),"$") != NULL) || (strstr(bfd_asymbol_name(symbol_table[i]),"?") != NULL))
                                                                                        continue;//���У��Ż���$�� 
                                temp.symbol_table.push_back(bfd_asymbol_name(symbol_table[i]));
                                temp.symbol_start_table.push_back(bfd_asymbol_value(symbol_table[i]));
                                
                                
                            {
                                static long int size=INT_MAX,count=0;
                                size=symbol_table[i]->section->size-symbol_table[i]->value;
                                for(count=0;count<number_of_symbols;count++)
                                {
                                    if(strcmp(symbol_table[count]->section->name,symbol_table[i]->section->name)) continue;//�ڲ�ͬ 
                                    
                                    if((bfd_asymbol_value(symbol_table[count])-bfd_asymbol_value(symbol_table[i])) >0)//����ķ��� 
                                        size=MIN(size,ABS(bfd_asymbol_value(symbol_table[count])-bfd_asymbol_value(symbol_table[i])));  
                                }
                                //printf("\tsize=%ld\n",size);
                                temp.symbol_length_table.push_back(size);
                                
                            }
                             
                            
                     }
                     free(symbol_table);
                    
                   
                  } 
                  bfd_close(ibfd);
                
                    
                }
                temp.Update_Data();//�������� 
               if(temp.ShowModal() == wxID_OK)
               {
                  symbol=temp.symbol_ret;
                  symbol_start=temp.symbol_start_ret;
                  symbol_length=temp.symbol_length_ret;       
               }
               else
               {
                    ErrorMessage("δ֪����ѡ�񴰿��˳���!\n","����");
                    return; 
               }
               temp.Destroy(); 
            }
         }
    }
    
    {//�Զ�����ŵ�ַ 
    if(symbol_length==0)
        {
            //ErrorMessage("�Զ�����ŵ�ַ","˵��");
            Address_manual temp(this);
            if(temp.ShowModal() == wxID_OK)
               {
                  symbol=temp.symbol_ret;
                  symbol_start=temp.symbol_start_ret;
                  symbol_length=temp.symbol_length_ret;       
               }
               else
               {
                    ErrorMessage("δ֪�������ô����˳���!\n","����");
                    return; 
               }
               temp.Destroy(); 
             
        }
    }
    WxButton_Save->Enable();
    {
        {//��ʾ��ǰ����
        char buff[81920];
        sprintf(buff,"�ļ�·��:\n%s \n�ļ�����:%s \n��������:%s \n��ַ:%08X \n����:%u",
                        ((std::string)FilePath.c_str()).c_str(),
                        ((std::string)type.c_str()).c_str(),
                        ((std::string)symbol.c_str()).c_str(),
                        symbol_start,
                        symbol_length);
        WxRichTextCtrl1->Clear();
        WxRichTextCtrl1->AppendText(buff);
        } 
    }
}

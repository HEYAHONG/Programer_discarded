//---------------------------------------------------------------------------
//
// Name:        STM32_Data_ProgramerApp.cpp
// Author:      ���Ǻ�
// Created:     2019-11-18 13:18:05
// Description: 
//
//---------------------------------------------------------------------------

#include "STM32_Data_ProgramerApp.h"
#include "STM32_Data_ProgramerDlg.h"

IMPLEMENT_APP(STM32_Data_ProgramerDlgApp)

bool STM32_Data_ProgramerDlgApp::OnInit()
{
    SetEnvironment();	
	STM32_Data_ProgramerDlg* dialog = new STM32_Data_ProgramerDlg(NULL);
	SetTopWindow(dialog);
	dialog->Show(true);	
	return true;
}
 
int STM32_Data_ProgramerDlgApp::OnExit()
{
	return 0;
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

void STM32_Data_ProgramerDlgApp::SetEnvironment()
{
char path[PATH_MAX+1];
strcpy(path,argv[0]);
memset(path,0,sizeof(path));

//��ȥ�ļ������õ����г����·�� 
for(size_t i=0;i<=strlen(path);i++)
{
size_t pos=strlen(argv[0])-i;
if(path[pos] == '\\' || path[pos]== '/')
        {
        path[pos]=0;
        break;
        }
}

if(strlen(path) > 0)
    { 
    //���ù���Ŀ¼Ϊ��������Ŀ¼ 
    if(chdir(path))
        {
            wxMessageDialog temp(NULL,"���ù���Ŀ¼ʧ��,�������ܲ�����!\n","����");
            temp.ShowModal(); 
            
        }
    }

{//����path����
     char env_path[81920];
     strcpy(env_path,(char *)"toolchain/bin");
     #ifdef WIN32
     strcat(env_path,(char *)";");
     #else
     strcat(env_path,(char *)":");
     #endif
     strcat(env_path,getenv("PATH"));
     #ifdef WIN32
     char env[82000];
     strcpy(env,"PATH=");
     strcat(env,env_path);
     putenv(env);
     #else
     setenv("PATH",env_path,1);
     #endif
}

//{
////���Թ����Ƿ���� 
//  #ifdef WIN32
//  if(WinExec("objdump.exe -v",SW_HIDE)<32)
//    {
//        wxMessageDialog temp(NULL,"�����Ĺ��߲�����!\n","����");
//        temp.ShowModal();
//        Exit(); 
//    };
//  #else
//  #error ������δʵ��!
//  #endif 
//} 
{
//�������� 
//memset(path,0,sizeof(path));
//getcwd(path,sizeof(path)); 
//wxMessageDialog temp(NULL,argv[0]);
//temp.ShowModal();



 
}    
    
}

//---------------------------------------------------------------------------
//
// Name:        STM32_Data_ProgramerApp.cpp
// Author:      何亚红
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

//除去文件名，得到运行程序的路径 
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
    //设置工作目录为程序所在目录 
    if(chdir(path))
        {
            wxMessageDialog temp(NULL,"设置工作目录失败,工作可能不正常!\n","警告");
            temp.ShowModal(); 
            
        }
    }

{//更新path变量
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
////测试工具是否存在 
//  #ifdef WIN32
//  if(WinExec("objdump.exe -v",SW_HIDE)<32)
//    {
//        wxMessageDialog temp(NULL,"依赖的工具不存在!\n","警告");
//        temp.ShowModal();
//        Exit(); 
//    };
//  #else
//  #error 功能尚未实现!
//  #endif 
//} 
{
//测试数据 
//memset(path,0,sizeof(path));
//getcwd(path,sizeof(path)); 
//wxMessageDialog temp(NULL,argv[0]);
//temp.ShowModal();



 
}    
    
}

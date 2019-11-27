#include "openocd_wxthread.h"
#include "wx/wx.h"
#include "wx/thread.h"
#include "windows.h"


Openocd_wxThread::Openocd_wxThread()
{
    //ctor
    status=0;
    SECURITY_ATTRIBUTES sa;
    memset(&sa,0,sizeof(sa));
    memset(&si,0,sizeof(si));
    memset(&pi,0,sizeof(pi));
    memset(openocd_title,0,sizeof(openocd_title));
    sa.nLength=sizeof(sa);
    sa.bInheritHandle=TRUE;
    sa.lpSecurityDescriptor=NULL;
    if(!CreatePipe(&hStdin_r,&hStdin_w,&sa,409600))
    {
        MessageBoxA(NULL,"创建管道失败!\n","错误",MB_OK);
        status=-1;
    }
    if(!CreatePipe(&hStdout_r,&hStdout_w,&sa,4096))
    {
        MessageBoxA(NULL,"创建管道失败!\n","错误",MB_OK);
        status=-1;
    }
    if(!CreatePipe(&hStderr_r,&hStderr_w,&sa,4096))
    {
        MessageBoxA(NULL,"创建管道失败!\n","错误",MB_OK);
        status=-1;
    }
    if(!SetHandleInformation(hStderr_r,HANDLE_FLAG_INHERIT,0))
    {
        MessageBoxA(NULL,"设置管道信息失败!\n","错误",MB_OK);
        status=-1;
    }
    if(!SetHandleInformation(hStdout_r,HANDLE_FLAG_INHERIT,0))
    {
        MessageBoxA(NULL,"设置管道信息失败!\n","错误",MB_OK);
        status=-1;
    }
    if(!SetHandleInformation(hStdin_w,HANDLE_FLAG_INHERIT,0))
    {
        MessageBoxA(NULL,"设置管道信息失败!\n","错误",MB_OK);
        status=-1;
    }

    si.cb=sizeof(si);
    si.hStdError=hStderr_w;
    si.hStdInput=hStdin_r;
    si.hStdOutput=hStdout_w;
    si.wShowWindow=SW_HIDE;
    si.dwFlags=STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
    strcpy(openocd_title,"openocd_background_process");
    si.lpTitle=openocd_title;
    pi.hProcess=0;
    pi.dwProcessId=0;
    Run();
}

int Openocd_wxThread::GetStatus()
{
    return status;
}

char cmdline[8192];

Openocd_wxThread::ExitCode Openocd_wxThread::Entry()
{
    if(status!=-1)
    {
        if(!CreateProcessA(NULL,cmdline,NULL,NULL,TRUE,0,NULL,NULL,&si,&pi))
        {
            //MessageBoxA(NULL,"创建进程出错!\n","错误",MB_OK);
            status=-1;
        }
        else
        {
            status=1;
            while(WAIT_TIMEOUT==WaitForSingleObject(pi.hProcess,1))
            {
                Sleep(200);
                //char buff[32];
                //memset(buff,0,sizeof(buff));
                //if(ReadStdout((unsigned char *)buff,sizeof(buff))>0)
                    {
                  //      log+=buff;
                    }
            }
            status=0;
        }
    }
    status=-1;
    while(status!=-2)
        getchar();//等待确认退出，防止指针/变量失效
    return NULL;
}

void  Openocd_wxThread::ConfirmExit()
{
    if(status==-1)
        status=-2;
}

size_t Openocd_wxThread::ReadStderr(unsigned char buff[],size_t length)
{
    if(status == 1)
    {
        DWORD i=0,j=0;
        if(PeekNamedPipe(hStderr_r,buff,length,&j,&i,NULL))
            {
                if(i>0)
                    {
                        ReadFile(hStderr_r,buff,length,&i,NULL);
                    }
            }

        return i;
    }
    else
    {
        return 0;
    }
}
size_t Openocd_wxThread::ReadStdout(unsigned char buff[],size_t length)
{
    if(status == 1)
    {
        DWORD i=0,j=0;
        if(PeekNamedPipe(hStdout_r,buff,length,&j,&i,NULL))
            {
                if(i>0)
                    {
                        ReadFile(hStdout_r,buff,length,&i,NULL);
                    }
            }
        return i;
    }
    else
    {
        return 0;
    }
}
size_t Openocd_wxThread::WriteStdin(unsigned char buff[],size_t length)
{
    if(status == 1)
    {
        DWORD i=0;
        WriteFile(hStdin_w,buff,length,&i,NULL);
        return i;
    }
    else
    {
        return 0;
    }
}
Openocd_wxThread::~Openocd_wxThread()
{
    //dtor
    if(pi.hProcess!=0)
        {
            TerminateProcess(pi.hProcess,0);
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
        }
    //关闭所有句柄
    CloseHandle(hStderr_r);
    CloseHandle(hStderr_w);
    CloseHandle(hStdin_r);
    CloseHandle(hStdin_w);
    CloseHandle(hStdout_r);
    CloseHandle(hStdout_w);
}

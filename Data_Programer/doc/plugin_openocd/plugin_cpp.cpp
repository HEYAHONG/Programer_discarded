#include "wx/wx.h"
#include "wx/filedlg.h"
#include "wx/msgdlg.h"
#include "wx/socket.h"
#include "thread"
#include "stdio.h"
//#include "windows.h"
#include "string.h"
//#include "unistd.h"
#include "unistd.h"
//#include "thread"
#include "STM32_Data_ProgramerDlg.h"



#ifdef __cplusplus
extern "C"
{
 int  cpp_plug_process_program_cpp(const uint8_t *hex);
}
#endif // __cplusplus


static int ret=0;
STM32_Data_ProgramerDlg *Dialog=NULL;
void  program_thread()
{
        ret=0;
        int file_size=0;
        {//校验前置条件
            HANDLE h=0;
            if(!(h=OpenMutexA(SYNCHRONIZE,FALSE,"openocd_plugin_backend_win32_running")))
            {
                Dialog->Info->AppendText("openocd未启动,即将尝试启动openocd!\n");
                {
                    if(WinExec("openocd_plugin_backend_win32.exe",SW_SHOWMINNOACTIVE)>32)
                    {
                        Dialog->Info->AppendText("等待10s\n");
                        Sleep(10000);
                        if(!(h=OpenMutexA(SYNCHRONIZE,FALSE,"openocd_plugin_backend_win32_running")))
                        {
                            Dialog->Info->AppendText("openocd启动失败!\n");
                            ret=0;
                            return;
                        }
                        else
                        {
                            Dialog->Info->AppendText("启动openocd成功!\n");
                            CloseHandle(h);
                        }
                    }
                    else
                    {
                        Dialog->Info->AppendText("启动openocd失败!\n");
                        ret=0;
                        return;
                    }
                }
            }
            else
            {
                CloseHandle(h);
            }
        }

        //设置地址
        struct sockaddr_in serveraddr;
        memset(&serveraddr,0,sizeof(serveraddr));
        serveraddr.sin_family = AF_INET;
        serveraddr.sin_port=htons(55556);
        //设置IP
        serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");

        //连接openocd
        Dialog->Info->AppendText("准备连接openocd服务!\n");
        int openocd_socket=0;
        if((openocd_socket=socket(AF_INET,SOCK_STREAM,0))==-1)
        {
            Dialog->Info->AppendText("创建socket失败!\n");
            ret=0;
            return;
        }
        if(connect(openocd_socket,(const sockaddr *)&serveraddr,sizeof(serveraddr))==-1)
        {
            Dialog->Info->AppendText("连接openocd服务失败!\n");
            ret=0;
            close(openocd_socket);
            return;
        }


        //保存hex文件
        char hex_file_path[8192];
        memset(hex_file_path,0,sizeof(8192));
        {
            //Dialog->Info->AppendText((wxString)"保存路径为:"+dlg.GetPath()+"\n");
            char buff[4096];
            memset(buff,0,sizeof(buff));
            if(!GetTempPathA(sizeof(buff),buff))
            {
                Dialog->Info->AppendText("获取临时文件夹失败!\n");
                ret=0;
                return;
            }
            strcat(hex_file_path,buff);
            memset(buff,0,sizeof(buff));
            srand(time(NULL));
            sprintf(buff,"\\%08X.hex",rand());
            strcat(hex_file_path,buff);
            {//将文件名中的\替换成/
               for(size_t i=0;i<strlen(hex_file_path);i++)
               {
                   if(hex_file_path[i]=='\\')
                        hex_file_path[i]='/';
               }
            }
            FILE *fp=fopen(hex_file_path,"wb");
            if(fp==NULL)
            {
                ret=0;
                Dialog->Info->AppendText("文件路径不可写!\n");
                return;
            }
            file_size=fwrite(Dialog->hex_data,1,strlen((char *)Dialog->hex_data),fp);
            fclose(fp);
        }

        std::string data="";
        {//清空缓冲区数据
          char buff[8192];
          memset(buff,0,sizeof(buff));
          recv(openocd_socket,buff,sizeof(buff),0);
        }
        {//检查硬件是否正确连接
            Dialog->Info->AppendText("检查硬件是否正确连接!\n");
            send(openocd_socket,"transport init\n",sizeof("transport init\n"),0);//单片机停机
            while(1)
            {
                char buff[4096];
                memset(buff,0,sizeof(buff));
                if(recv(openocd_socket,buff,sizeof(buff),0)>0)
                {
                    data+=buff;
                    std::string temp=buff;
                   if(temp.find(">")!=std::string::npos)
                        break;
                }
                else
                {//出错退出
                    close(openocd_socket);
                    ret=0;
                    return;
                }
            }
            //Dialog->Info->AppendText(data);
            //Dialog->Info->AppendText("\n");
            if(data.find("SWD")==std::string::npos)
            {//连接有问题
               Dialog->Info->AppendText("硬件连接异常!\n");
               ret=0;
               return;
            }
            else
            {
                Dialog->Info->AppendText("硬件连接正常!\n");
            }


        }

        {//烧录hex
           Dialog->Info->AppendText("写入并校验hex!\n");
           char cmd[8192];
           memset(cmd,0,sizeof(cmd));
           sprintf(cmd,"program %s verify reset\n",hex_file_path);
            send(openocd_socket,cmd,strlen(cmd),0);//单片机停机
            while(1)
            {
                char buff[4096];
                memset(buff,0,sizeof(buff));
                if(recv(openocd_socket,buff,sizeof(buff),0)>0)
                {
                    data+=buff;
                    std::string temp=buff;
                   if(temp.find(">")!=std::string::npos)
                        break;
                }
                else
                {//出错退出
                    close(openocd_socket);
                    ret=0;
                    return;
                }
            }
            //Dialog->Info->AppendText(data);
            //Dialog->Info->AppendText("\n");
            if(data.find("Verified OK")==std::string::npos)
            {//连接有问题
               Dialog->Info->AppendText("写入失败!\n");
               ret=0;
               return;
            }
            else
            {
                Dialog->Info->AppendText("写入成功!\n");
                ret=file_size;
            }
        }

        {//检查硬件是否断开

            while(1)
                {//检查硬件是否正确连接
                data="";
                Dialog->Info->AppendText("等待单片机断开!\n");
                send(openocd_socket,"transport init\n",sizeof("transport init\n"),0);//单片机停机
                while(1)
                {
                    char buff[4096];
                    memset(buff,0,sizeof(buff));
                    if(recv(openocd_socket,buff,sizeof(buff),0)>0)
                    {
                        data+=buff;
                        std::string temp=buff;
                       if(temp.find(">")!=std::string::npos)
                            break;
                    }
                    else
                    {//出错退出
                        Dialog->Info->AppendText("读取出错!\n");
                        close(openocd_socket);
                        ret=0;
                        return;
                    }
                }
                //Dialog->Info->AppendText(data);
                //Dialog->Info->AppendText("\n");
                if(data.find("SWD")==std::string::npos)
                {//连接有问题

                   break;
                }
                else
                {
                    Dialog->Info->AppendText("请断开单片机与调试器的连接!\n");
                    Sleep(1000);
                }


            }
        }
        send(openocd_socket,"exit\n",sizeof("exit\n"),0);//退出telnet
        close(openocd_socket);
        Sleep(200);//等待200ms
        remove(hex_file_path);//删除临时文件

}

int  cpp_plug_process_program_cpp(const uint8_t *hex)
{
    //加载指针
    if(getenv("Dialog_Ptr")==NULL)
    {
        MessageBoxA(NULL,"未知错误（窗口指针不存在）!\n","警告",MB_OK);
        return 0;
    }
    #ifdef WIN32
      //Winsows下启用socket
      WSADATA wsadata;
      if(WSAStartup(MAKEWORD(1,1),&wsadata)==SOCKET_ERROR)
      {
        Dialog->Info->AppendText("socket初始化失败!\n");
        return 0;
      }
    #endif
    //MessageBoxA(NULL,getenv("Dialog_Ptr"),"提示",MB_OK);
    {
     uint64_t  ptr=0;
     sscanf(getenv("Dialog_Ptr"),"%016X",&ptr);
     Dialog =(STM32_Data_ProgramerDlg *)ptr;
    }
    Dialog->Enable(false);
    //std::thread t(program_thread);
    //t.join();
    program_thread();
    Dialog->Enable(true);
    #ifdef WIN32
         WSACleanup();
    #endif
    return ret;
}



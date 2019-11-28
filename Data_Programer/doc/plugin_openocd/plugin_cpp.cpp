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
        {//У��ǰ������
            HANDLE h=0;
            if(!(h=OpenMutexA(SYNCHRONIZE,FALSE,"openocd_plugin_backend_win32_running")))
            {
                Dialog->Info->AppendText("openocdδ����,������������openocd!\n");
                {
                    if(WinExec("openocd_plugin_backend_win32.exe",SW_SHOWMINNOACTIVE)>32)
                    {
                        Dialog->Info->AppendText("�ȴ�10s\n");
                        Sleep(10000);
                        if(!(h=OpenMutexA(SYNCHRONIZE,FALSE,"openocd_plugin_backend_win32_running")))
                        {
                            Dialog->Info->AppendText("openocd����ʧ��!\n");
                            ret=0;
                            return;
                        }
                        else
                        {
                            Dialog->Info->AppendText("����openocd�ɹ�!\n");
                            CloseHandle(h);
                        }
                    }
                    else
                    {
                        Dialog->Info->AppendText("����openocdʧ��!\n");
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

        //���õ�ַ
        struct sockaddr_in serveraddr;
        memset(&serveraddr,0,sizeof(serveraddr));
        serveraddr.sin_family = AF_INET;
        serveraddr.sin_port=htons(55556);
        //����IP
        serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");

        //����openocd
        Dialog->Info->AppendText("׼������openocd����!\n");
        int openocd_socket=0;
        if((openocd_socket=socket(AF_INET,SOCK_STREAM,0))==-1)
        {
            Dialog->Info->AppendText("����socketʧ��!\n");
            ret=0;
            return;
        }
        if(connect(openocd_socket,(const sockaddr *)&serveraddr,sizeof(serveraddr))==-1)
        {
            Dialog->Info->AppendText("����openocd����ʧ��!\n");
            ret=0;
            close(openocd_socket);
            return;
        }


        //����hex�ļ�
        char hex_file_path[8192];
        memset(hex_file_path,0,sizeof(8192));
        {
            //Dialog->Info->AppendText((wxString)"����·��Ϊ:"+dlg.GetPath()+"\n");
            char buff[4096];
            memset(buff,0,sizeof(buff));
            if(!GetTempPathA(sizeof(buff),buff))
            {
                Dialog->Info->AppendText("��ȡ��ʱ�ļ���ʧ��!\n");
                ret=0;
                return;
            }
            strcat(hex_file_path,buff);
            memset(buff,0,sizeof(buff));
            srand(time(NULL));
            sprintf(buff,"\\%08X.hex",rand());
            strcat(hex_file_path,buff);
            {//���ļ����е�\�滻��/
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
                Dialog->Info->AppendText("�ļ�·������д!\n");
                return;
            }
            file_size=fwrite(Dialog->hex_data,1,strlen((char *)Dialog->hex_data),fp);
            fclose(fp);
        }

        std::string data="";
        {//��ջ���������
          char buff[8192];
          memset(buff,0,sizeof(buff));
          recv(openocd_socket,buff,sizeof(buff),0);
        }
        {//���Ӳ���Ƿ���ȷ����
            Dialog->Info->AppendText("���Ӳ���Ƿ���ȷ����!\n");
            send(openocd_socket,"transport init\n",sizeof("transport init\n"),0);//��Ƭ��ͣ��
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
                {//�����˳�
                    close(openocd_socket);
                    ret=0;
                    return;
                }
            }
            //Dialog->Info->AppendText(data);
            //Dialog->Info->AppendText("\n");
            if(data.find("SWD")==std::string::npos)
            {//����������
               Dialog->Info->AppendText("Ӳ�������쳣!\n");
               ret=0;
               return;
            }
            else
            {
                Dialog->Info->AppendText("Ӳ����������!\n");
            }


        }

        {//��¼hex
           Dialog->Info->AppendText("д�벢У��hex!\n");
           char cmd[8192];
           memset(cmd,0,sizeof(cmd));
           sprintf(cmd,"program %s verify reset\n",hex_file_path);
            send(openocd_socket,cmd,strlen(cmd),0);//��Ƭ��ͣ��
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
                {//�����˳�
                    close(openocd_socket);
                    ret=0;
                    return;
                }
            }
            //Dialog->Info->AppendText(data);
            //Dialog->Info->AppendText("\n");
            if(data.find("Verified OK")==std::string::npos)
            {//����������
               Dialog->Info->AppendText("д��ʧ��!\n");
               ret=0;
               return;
            }
            else
            {
                Dialog->Info->AppendText("д��ɹ�!\n");
                ret=file_size;
            }
        }

        {//���Ӳ���Ƿ�Ͽ�

            while(1)
                {//���Ӳ���Ƿ���ȷ����
                data="";
                Dialog->Info->AppendText("�ȴ���Ƭ���Ͽ�!\n");
                send(openocd_socket,"transport init\n",sizeof("transport init\n"),0);//��Ƭ��ͣ��
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
                    {//�����˳�
                        Dialog->Info->AppendText("��ȡ����!\n");
                        close(openocd_socket);
                        ret=0;
                        return;
                    }
                }
                //Dialog->Info->AppendText(data);
                //Dialog->Info->AppendText("\n");
                if(data.find("SWD")==std::string::npos)
                {//����������

                   break;
                }
                else
                {
                    Dialog->Info->AppendText("��Ͽ���Ƭ���������������!\n");
                    Sleep(1000);
                }


            }
        }
        send(openocd_socket,"exit\n",sizeof("exit\n"),0);//�˳�telnet
        close(openocd_socket);
        Sleep(200);//�ȴ�200ms
        remove(hex_file_path);//ɾ����ʱ�ļ�

}

int  cpp_plug_process_program_cpp(const uint8_t *hex)
{
    //����ָ��
    if(getenv("Dialog_Ptr")==NULL)
    {
        MessageBoxA(NULL,"δ֪���󣨴���ָ�벻���ڣ�!\n","����",MB_OK);
        return 0;
    }
    #ifdef WIN32
      //Winsows������socket
      WSADATA wsadata;
      if(WSAStartup(MAKEWORD(1,1),&wsadata)==SOCKET_ERROR)
      {
        Dialog->Info->AppendText("socket��ʼ��ʧ��!\n");
        return 0;
      }
    #endif
    //MessageBoxA(NULL,getenv("Dialog_Ptr"),"��ʾ",MB_OK);
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



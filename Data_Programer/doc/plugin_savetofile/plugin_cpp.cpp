#include "wx/wx.h"
#include "wx/filedlg.h"
#include "wx/msgdlg.h"
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

        //MessageBoxA(NULL,"OK","Test",MB_OK);
        wxFileDialog dlg(Dialog,"选择hex保存路径","","out.hex","*.hex",wxFD_SAVE);
        if(wxID_OK==dlg.ShowModal())
        {
            Dialog->Info->AppendText((wxString)"保存路径为:"+dlg.GetPath()+"\n");
            FILE *fp=fopen(((std::string)dlg.GetPath().c_str()).c_str(),"wb");
            if(fp==NULL)
            {
                ret=0;
                Dialog->Info->AppendText("文件路径不可写!\n");
                return;
            }
            ret=fwrite(Dialog->hex_data,1,strlen((char *)Dialog->hex_data),fp);
            fclose(fp);
        }
        else
        {
            ret=0;
            Dialog->Info->AppendText("操作取消!\n");
            return;
        }


}

int  cpp_plug_process_program_cpp(const uint8_t *hex)
{
    //加载指针
    if(getenv("Dialog_Ptr")==NULL)
    {
        MessageBoxA(NULL,"未知错误（窗口指针不存在）!\n","警告",MB_OK);
        return 0;
    }
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
    return ret;
}



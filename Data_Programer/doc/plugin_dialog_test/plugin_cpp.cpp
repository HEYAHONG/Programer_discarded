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
#include "test.h"



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

}

int  cpp_plug_process_program_cpp(const uint8_t *hex)
{
    //����ָ��
    if(getenv("Dialog_Ptr")==NULL)
    {
        MessageBoxA(NULL,"δ֪���󣨴���ָ�벻���ڣ�!\n","����",MB_OK);
        return 0;
    }
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
    return ret;
}



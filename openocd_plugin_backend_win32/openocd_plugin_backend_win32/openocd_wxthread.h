#ifndef OPENOCD_WXTHREAD_H
#define OPENOCD_WXTHREAD_H
#include "wx/thread.h"
#include "wx/wx.h"


class Openocd_wxThread:public wxThread
{
    public:
        Openocd_wxThread();
        virtual ~Openocd_wxThread();
        HANDLE hStdin_w;
        HANDLE hStdin_r;
        HANDLE hStdout_w;
        HANDLE hStdout_r;
        HANDLE hStderr_w;
        HANDLE hStderr_r;
        PROCESS_INFORMATION pi;
        STARTUPINFOA        si;
        char openocd_title[128];
        int status;//0为未初始化，1为成功，-1为失败。
        int GetStatus();
        void ConfirmExit();
        size_t ReadStdout(unsigned char buff[],size_t length);
        size_t ReadStderr(unsigned char buff[],size_t length);
        size_t WriteStdin(unsigned char buff[],size_t length);

    protected:
        ExitCode Entry();

    private:
};

#endif // OPENOCD_WXTHREAD_H

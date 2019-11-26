#ifndef JLINK_WXTHREAD_H
#define JLINK_WXTHREAD_H
#include "wx/thread.h"
#include "wx/wx.h"


class Jlink_wxThread:public wxThread
{
    public:
        Jlink_wxThread();
        virtual ~Jlink_wxThread();
        HANDLE hStdin_w;
        HANDLE hStdin_r;
        HANDLE hStdout_w;
        HANDLE hStdout_r;
        HANDLE hStderr_w;
        HANDLE hStderr_r;
        PROCESS_INFORMATION pi;
        STARTUPINFOA        si;
        char jlink_title[128];
        int status;//0为未初始化，1为成功，-1为失败。
        int GetStatus();
        void ConfirmExit();
        wxString log;
        size_t ReadStdout(unsigned char buff[],size_t length);
        size_t ReadStderr(unsigned char buff[],size_t length);
        size_t WriteStdin(unsigned char buff[],size_t length);

    protected:
        ExitCode Entry();

    private:
};

#endif // JLINK_WXTHREAD_H

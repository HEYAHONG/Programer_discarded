///-----------------------------------------------------------------
///
/// @file      FilePassWord.cpp
/// @author    何亚红
/// Created:   2019-11-18 15:26:08
/// @section   DESCRIPTION
///            FilePassWord class implementation
///
///------------------------------------------------------------------

#include "FilePassWord.h"

//Do not add custom headers
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// FilePassWord
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(FilePassWord,wxDialog)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(FilePassWord::OnClose)
	EVT_BUTTON(ID_WXBUTTON2,FilePassWord::WxButton2Click0)
	EVT_BUTTON(ID_WXBUTTON1,FilePassWord::WxButton1Click)
	
	EVT_TEXT(ID_WXEDIT1,FilePassWord::WxEdit1Updated)
END_EVENT_TABLE()
////Event Table End

FilePassWord::FilePassWord(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style)
{
	CreateGUIControls();
}

FilePassWord::~FilePassWord()
{
} 

void FilePassWord::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End.
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	WxButton2 = new wxButton(this, ID_WXBUTTON2, _("取消"), wxPoint(251, 31), wxSize(72, 26), 0, wxDefaultValidator, _("WxButton2"));

	WxEdit2 = new wxTextCtrl(this, ID_WXEDIT2, _("在上方输入密码,点击确定。"), wxPoint(3, 34), wxSize(244, 26), wxTE_READONLY | wxTE_LEFT, wxDefaultValidator, _("WxEdit2"));

	WxButton1 = new wxButton(this, ID_WXBUTTON1, _("确定"), wxPoint(251, 1), wxSize(72, 26), 0, wxDefaultValidator, _("WxButton1"));

	WxEdit1 = new wxTextCtrl(this, ID_WXEDIT1, _("cdwzdl.cn"), wxPoint(2, 2), wxSize(244, 25), 0, wxDefaultValidator, _("WxEdit1"));

	SetTitle(_("FilePassWord"));
	SetIcon(wxNullIcon);
	SetSize(8,8,343,101);
	Center();
	
	////GUI Items Creation End
}

void FilePassWord::OnClose(wxCloseEvent& /*event*/)
{
	Destroy();
}

/*
 * WxEdit1Updated
 */
void FilePassWord::WxEdit1Updated(wxCommandEvent& event)
{
	// insert your code here
	if(WxEdit1->GetValue().Len()>31)
	   {
        wxMessageDialog dlg(this,"密码输入过长!\n","警告");
        dlg.ShowModal();
        WxEdit1->Clear();
        WxEdit1->AppendText("cdwzdl.cn");    
       }
}

/*
 * WxButton1Click
 */
void FilePassWord::WxButton1Click(wxCommandEvent& event)
{
	// insert your code here
	Dat_header fheader;
	memset(&fheader,0,sizeof(fheader)); 
	{//验证密码是否正确
       char * DataDir=getenv("DataDir"); 
       char * fname=getenv("data");
       size_t fsize=0;
       if(fname==NULL || DataDir ==NULL)
                {
                    wxMessageDialog dlg(this,"配置文件错误!\n","警告");
                    dlg.ShowModal();
                    EndModal(wxID_CANCEL);
                    return; 
                }
        FILE *fp=fopen((wxString)DataDir+fname,"rb");
        if(fp==NULL)
                {
                    wxMessageDialog dlg(this,"数据文件错误!\n","警告");
                    dlg.ShowModal();
                    EndModal(wxID_CANCEL);
                    return; 
                }
        fseek(fp,0L,SEEK_END);
        fsize=ftell(fp);
        fseek(fp,0,SEEK_SET);
        if(fsize<64)
                {
                    wxMessageDialog dlg(this,"数据文件太小!\n","警告");
                    dlg.ShowModal();
                    fclose(fp); 
                    EndModal(wxID_CANCEL);
                    return; 
                }
        {
            uint8_t aes_in[32],aes_out[32],aes_key[32];
            uint8_t *w=aes_init(32);
            memset(aes_key,0,sizeof(aes_key));
            memcpy(aes_key,((std::string)WxEdit1->GetValue().c_str()).c_str(),WxEdit1->GetValue().Len()); 
            aes_key_expansion(aes_key,w);
            if(fread(aes_in,1,32,fp)==32)
                {
                   aes_inv_cipher(aes_in,aes_out,w);
                   memcpy(&fheader,aes_out,32); 
                   if(fheader.data.flag != 0x12345678 || fheader.data.dat_size != fsize || fheader.data.hex_data_size!=(fsize-32))
                   {
                    wxMessageDialog dlg(this,"密码错误!\n","警告");
                    dlg.ShowModal();
                    free(w); 
                    fclose(fp);
                    return;
                   }
                   else
                   {//将密码(data_password)设定为环境变量
                     char buff[256];
                     sprintf(buff,"data_password=%s",aes_key);
                     putenv(buff);                                                  
                   }
        
                }
            else
                {
                    wxMessageDialog dlg(this,"数据文件读取错误!\n","警告");
                    dlg.ShowModal();
                    free(w); 
                    fclose(fp); 
                    EndModal(wxID_CANCEL);
                    return; 
                }
            free(w);
               
        }
        fclose(fp); 
    }
	EndModal(wxID_OK);
}
void FilePassWord::WxButton2Click(wxCommandEvent& event)
{
    EndModal(wxID_CANCEL); 
    
} 


/*
 * WxButton2Click0
 */
void FilePassWord::WxButton2Click0(wxCommandEvent& event)
{
	// insert your code here
	WxButton2Click(event);
}

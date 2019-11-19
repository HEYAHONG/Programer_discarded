///-----------------------------------------------------------------
///
/// @file      FileCrypto.cpp
/// @author    何亚红
/// Created:   2019-11-15 11:44:28
/// @section   DESCRIPTION
///            FileCrypto class implementation
///
///------------------------------------------------------------------

#include "FileCrypto.h"

//Do not add custom headers
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// FileCrypto
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(FileCrypto,wxDialog)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(FileCrypto::OnClose)
	EVT_BUTTON(ID_WXBUTTON1,FileCrypto::WxButton1Click)
	
	EVT_TEXT(ID_WXEDIT1,FileCrypto::WxEdit1Updated)
END_EVENT_TABLE()
////Event Table End

FileCrypto::FileCrypto(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style)
{
	CreateGUIControls();
	remove("data/data.Dat");//删除原来的数据 
	if(access("data",6))
	{
        {
            wxMessageDialog msg(this,"安装目录不可写","警告");
            msg.ShowModal(); 
        }
        EndModal(wxID_CANCEL);
    }
    hex=fopen("data/data.hex","rb");
    if(hex == NULL)
        {
           wxMessageDialog msg(this,"安装目录不可写","警告");
            msg.ShowModal();   
        }
    else
        {
            fseek(hex,0L,SEEK_END);
            hex_size=ftell(hex);
            fseek(hex,0L,SEEK_SET);
            if(hex_size%32)
            {
                hex_data_size=hex_size/32*32+32;
            }
            else
            {
                hex_data_size=hex_size;
            }
                dat_size=hex_data_size+sizeof(Dat_header);
        } 
    dat=fopen("data/data.Dat","wb");
     if(dat == NULL)
        {
           wxMessageDialog msg(this,"安装目录不可写","警告");
            msg.ShowModal();   
        } 
    {//显示信息
        char buff[8192];
        sprintf(buff,"请输入密码后点击确定开始！\nhex文件大小:%d\nhex加密后大小:%d\nDat文件大小(预计):%d",
                        hex_size,
                        hex_data_size,
                        dat_size);
        WxEdit2->AppendText(buff); 
        
    }
	
}

FileCrypto::~FileCrypto()
{
    if(hex!=NULL)
        fclose(hex);
    if(dat!=NULL)
        fclose(dat);
    
} 

void FileCrypto::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End.
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	WxEdit2 = new wxTextCtrl(this, ID_WXEDIT2, _(""), wxPoint(3, 38), wxSize(328, 90), wxTE_READONLY | wxTE_LEFT | wxTE_MULTILINE, wxDefaultValidator, _("WxEdit2"));

	WxButton1 = new wxButton(this, ID_WXBUTTON1, _("确定"), wxPoint(252, 8), wxSize(75, 22), 0, wxDefaultValidator, _("WxButton1"));

	WxEdit1 = new wxTextCtrl(this, ID_WXEDIT1, _("cdwzdl.cn"), wxPoint(4, 7), wxSize(240, 24), 0, wxTextValidator(wxFILTER_ASCII, NULL), _("WxEdit1"));

	SetTitle(_("FileCrypto"));
	SetIcon(wxNullIcon);
	SetSize(8,8,350,171);
	Center();
	
	////GUI Items Creation End
}

void FileCrypto::OnClose(wxCloseEvent& /*event*/)
{
    
	Destroy();
}

/*
 * WxButton1Click
 */
void FileCrypto::WxButton1Click(wxCommandEvent& event)
{
	// insert your code here
	uint8_t aes_in_buff[32],aes_out_buff[32];
	uint8_t aes_key[32];
	uint8_t *aes_w=aes_init(sizeof(aes_key));
	{
        wxString key=WxEdit1->GetValue();
        memset(aes_key,0,sizeof(aes_key)); 
        memcpy(aes_key,((std::string)key.c_str()).c_str(),key.Len());
        aes_key_expansion(aes_key, aes_w);
    }
	{//写入文件头
        Dat_header header;
        header.data.hex_size=hex_size;
        header.data.hex_data_size=hex_data_size;
        header.data.dat_size=dat_size;
        header.data.flag=0x12345678;//标志为0x12345678 
        memcpy(aes_in_buff,&header,32);
        
        //加密并写入文件 
        aes_cipher(aes_in_buff,aes_out_buff,aes_w);
        fwrite(aes_out_buff,32,1,dat); 
                
    }
	
	{//读取hex文件并加密
	    memset(aes_in_buff,0,32);   
        while(!feof(hex))
        {
            fread(aes_in_buff,1,32,hex);//读取hex文件 
            
            //加密并写入文件 
            aes_key_expansion(aes_key, aes_w);
            aes_cipher(aes_in_buff,aes_out_buff,aes_w);
            fwrite(aes_out_buff,32,1,dat); 
            memset(aes_in_buff,0,32);
        } 
        
    }
	WxButton1->Disable();
	free(aes_w);
	EndModal(wxID_OK); 
}

/*
 * WxEdit1Updated
 */
void FileCrypto::WxEdit1Updated(wxCommandEvent& event)
{
	// insert your code here
	if(WxEdit1->GetValue().Len() >= 32)
	{
        {
            wxMessageDialog msg(this,"密码过长!","警告");
            msg.ShowModal();
            WxEdit1->Clear();
            WxEdit1->AppendText("cdwzdl.cn");
        } 
    }
}

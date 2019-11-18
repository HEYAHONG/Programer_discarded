///-----------------------------------------------------------------
///
/// @file      Address_Select.cpp
/// @author    何亚红
/// Created:   2019-11-13 15:36:56
/// @section   DESCRIPTION
///            Address_Select class implementation
///
///------------------------------------------------------------------

#include "Address_Select.h"
#include <vector>
#include "stdio.h"

//Do not add custom headers
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// Address_Select
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(Address_Select,wxDialog)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(Address_Select::OnClose)
	EVT_BUTTON(ID_WXBUTTON1,Address_Select::WxButton1Click)
	EVT_COMBOBOX(ID_WXCOMBOBOX1,Address_Select::WxComboBox1Selected)
	EVT_TEXT(ID_WXCOMBOBOX1,Address_Select::WxComboBox1Updated)
END_EVENT_TABLE()
////Event Table End

Address_Select::Address_Select(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style)
{
	CreateGUIControls();
	symbol_table.clear();
    symbol_start_table.clear();
    symbol_length_table.clear();
    {//添加自定义选项 
        symbol_table.push_back("自定义");
        symbol_start_table.push_back(0);
        symbol_length_table.push_back(0);            
    }
   // {//分析symbol.txt
//    FILE *fp=fopen("symbol.txt","r");
//    if(fp == NULL)
//        {
//            EndModal(wxID_CANCEL);
//        }
//    else
//        {
//            char buff[8192];
//            bool is_table_start=false;
//            while(fgets(buff,sizeof(buff),fp)!= NULL)
//            {
//                if(strstr(buff,"SYMBOL TABLE:")!=NULL)
//                {
//                    is_table_start=true;
//                    continue;
//                }
//                if(is_table_start)
//                {//开始解析
//                    if((strstr(buff," g ")!=NULL)&&(strstr(buff," ro	")!=NULL) && (strstr(buff," F ")==NULL))//寻找全局只读变量(仅非函数符号) 
//                    {
//                       if((strstr(buff,"$")== NULL) && strstr(buff,"?") == NULL)//除去含有$号与?号的符号 
//                       {
//                            uint32_t start=0,length=0;
//                            wxString name="";
//                            
//                            sscanf(buff,"%X ",&start);
//                            
//                            for(size_t i=0;i<strlen(buff);i++)
//                            {
//                                if(buff[i]=='\t')
//                                {
//                                    char temp[4096];
//                                    memset(temp,0,sizeof(temp));
//                                    memcpy(temp,&buff[i+1],8);
//                                    temp[8]='\0';
//                                    sscanf(temp,"%X",&length);
//                                    memset(temp,0,sizeof(temp));
//                                    strcpy(temp,&buff[i+10]);
//                                    name=temp;
//                                }
//                            
//                            }
//                            if(length >0)//长度需大于0 
//                                { 
//                                    //char temp[4096]; 
////                                    sprintf(temp,"符号名:%s,起始地址=%08X,长度%u(字节)",((std::string)name.c_str()).c_str(),start,length);
////                                    wxMessageDialog wxtemp(NULL,temp,"说明");
////                                    wxtemp.ShowModal();
//                                        symbol_table.push_back(name);
//                                        symbol_start_table.push_back(start);
//                                        symbol_length_table.push_back(length); 
//                                } 
//                        } 
//                    }
//                    
//                }
//            }
//            
//            
//        }
//    fclose(fp);
//         
//    }
    {//添加选项到选择框
        size_t i=0;
        for(i=0;i<symbol_table.size();i++)
        {
          WxComboBox1->Insert(symbol_table[i],i); 
        } 
         
    }
}
void Address_Select::Update_Data()
{
    WxComboBox1->Clear();
     {//添加选项到选择框
        size_t i=0;
        for(i=0;i<symbol_table.size();i++)
        {
          WxComboBox1->Insert(symbol_table[i],i); 
        } 
         
    }
}

Address_Select::~Address_Select()
{
    
    
    
} 

void Address_Select::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End.
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	WxButton1 = new wxButton(this, ID_WXBUTTON1, _("确定"), wxPoint(280, 6), wxSize(59, 24), 0, wxDefaultValidator, _("WxButton1"));
	WxButton1->Enable(false);

	wxArrayString arrayStringFor_WxComboBox1;
	WxComboBox1 = new wxComboBox(this, ID_WXCOMBOBOX1, _(""), wxPoint(4, 5), wxSize(272, 25), arrayStringFor_WxComboBox1, wxTE_READONLY, wxDefaultValidator, _("WxComboBox1"));

	WxEdit1 = new wxTextCtrl(this, ID_WXEDIT1, _("请在上方选择一个变量，确定后点击确定。"), wxPoint(3, 40), wxSize(338, 52), wxTE_CENTRE | wxTE_BESTWRAP | wxTE_MULTILINE, wxDefaultValidator, _("WxEdit1"));
	WxEdit1->Enable(false);

	SetTitle(_("Select variable:"));
	SetIcon(wxNullIcon);
	SetSize(8,8,360,132);
	Center();
	
	////GUI Items Creation End
	
	
}

void Address_Select::OnClose(wxCloseEvent& /*event*/)
{
	Destroy();
}

/*
 * WxButton1Click
 */
void Address_Select::WxButton1Click(wxCommandEvent& event)
{
	// insert your code here
	
	EndModal(wxID_OK); 
}

/*
 * WxComboBox1Updated
 */
void Address_Select::WxComboBox1Updated(wxCommandEvent& event )
{
	// insert your code here
	
}

/*
 * WxComboBox1Selected
 */
void Address_Select::WxComboBox1Selected(wxCommandEvent& event )
{
	// insert your code here
	WxButton1->Enable(true); 
	{//显示相关信息
       for(size_t i=0;i<symbol_table.size();i++)
       {
            if(symbol_table[i]==(WxComboBox1->GetValue()))
            {
                char buff[4096];
                wxChar C_n='\n',C_0='\0'; 
                memset(buff,0,sizeof(buff));
                symbol_ret=symbol_table[i];
                {   //除去符号名中的回车 
                    size_t length=symbol_ret.Length();
                    char buff[8192];
                    strcpy(buff,((std::string)symbol_ret.c_str()).c_str());
                    if(buff[length-1] == '\n' || buff[length-1] == '\r')
                        {
                            buff[length-1]='\0';
                        } 
                    symbol_ret=buff;
                }
                symbol_start_ret=symbol_start_table[i];
                symbol_length_ret=symbol_length_table[i];
                sprintf(buff,"符号名:%s,起始地址=%08X,长度%u字节",((std::string)symbol_ret.c_str()).c_str(),
                                                                    symbol_start_ret,symbol_length_ret);
                WxEdit1->Clear();
                WxEdit1->AppendText(buff);
                break;
            }
        }
         
    }
}

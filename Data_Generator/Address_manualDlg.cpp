///-----------------------------------------------------------------
///
/// @file      Address_manualDlg.cpp
/// @author    ���Ǻ�
/// Created:   2019-11-14 12:47:23
/// @section   DESCRIPTION
///            Address_manual class implementation
///
///------------------------------------------------------------------

#include "Address_manualDlg.h"

//Do not add custom headers
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// Address_manual
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(Address_manual,wxDialog)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(Address_manual::OnClose)
	
	EVT_TEXT(ID_WXEDIT3,Address_manual::WxEdit3Updated)
	
	EVT_TEXT(ID_WXEDIT2,Address_manual::WxEdit2Updated)
	
	EVT_TEXT(ID_WXEDIT1,Address_manual::WxEdit1Updated)
	EVT_BUTTON(ID_WXBUTTON1,Address_manual::WxButton1Click)
END_EVENT_TABLE()
////Event Table End

Address_manual::Address_manual(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style)
{
	CreateGUIControls();
}

Address_manual::~Address_manual()
{
} 

void Address_manual::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End.
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	WxEdit3 = new wxTextCtrl(this, ID_WXEDIT3, _("0"), wxPoint(61, 50), wxSize(164, 20), 0, wxTextValidator(wxFILTER_NUMERIC, NULL), _("WxEdit3"));

	WxEdit2 = new wxTextCtrl(this, ID_WXEDIT2, _("0"), wxPoint(60, 26), wxSize(164, 20), 0, wxTextValidator(wxFILTER_ASCII, NULL), _("WxEdit2"));

	WxEdit1 = new wxTextCtrl(this, ID_WXEDIT1, _("symbol"), wxPoint(60, 5), wxSize(164, 20), 0, wxTextValidator(wxFILTER_ASCII, NULL), _("WxEdit1"));

	WxStaticText3 = new wxStaticText(this, ID_WXSTATICTEXT3, _("���ȣ�"), wxPoint(9, 53), wxDefaultSize, 0, _("WxStaticText3"));

	WxStaticText2 = new wxStaticText(this, ID_WXSTATICTEXT2, _("��ַ��"), wxPoint(10, 31), wxDefaultSize, 0, _("WxStaticText2"));

	WxStaticText1 = new wxStaticText(this, ID_WXSTATICTEXT1, _("������"), wxPoint(9, 6), wxDefaultSize, 0, _("WxStaticText1"));

	WxButton1 = new wxButton(this, ID_WXBUTTON1, _("ȷ��"), wxPoint(228, 1), wxSize(73, 73), 0, wxDefaultValidator, _("WxButton1"));
	WxButton1->Enable(false);
	WxButton1->SetFont(wxFont(22, wxSWISS, wxNORMAL, wxNORMAL, false));

	SetTitle(_("Set Address"));
	SetIcon(wxNullIcon);
	SetSize(8,8,320,115);
	Center();
	
	////GUI Items Creation End
}

void Address_manual::OnClose(wxCloseEvent& /*event*/)
{
	Destroy();
}

/*
 * WxButton1Click
 */
void Address_manual::WxButton1Click(wxCommandEvent& event)
{
	// insert your code here
	symbol_ret=WxEdit1->GetValue();
    unsigned long start=0,length=0;
    if(WxEdit2->GetValue().ToULong(&start,16) && WxEdit3->GetValue().ToULong(&length))
        {
            symbol_start_ret=start;
            symbol_length_ret=length; 
        	EndModal(wxID_OK);//�˳����� 
        }
    else
        {
            wxMessageDialog temp(this,"��������,����������!\n","����");
            temp.ShowModal();
            return;
        }
}

/*
 * WxEdit1Updated
 */
void Address_manual::WxEdit1Updated(wxCommandEvent& event)
{
	// insert your code here
	
}

/*
 * WxEdit3Updated
 */
void Address_manual::WxEdit3Updated(wxCommandEvent& event)
{
	// insert your code here
	static bool Is_ReEnter=false;
	if(Is_ReEnter==true) 
        return;
	unsigned long i;
	if(WxEdit3->GetValue().ToULong(&i))
	{
        if(i>0)
            {
                WxButton1->Enable();
            }
        else
            {
                WxButton1->Disable();
            }
    }
    else
    {
        wxMessageDialog temp(this,"���ȣ�10�������ݣ����벻��ȷ!\n");
        temp.ShowModal();
        Is_ReEnter=true;
        WxEdit3->Clear();
        Is_ReEnter=false; 
        WxEdit3->AppendText("1");
        
    }
}

/*
 * WxEdit2Updated
 */
void Address_manual::WxEdit2Updated(wxCommandEvent& event)
{
	// insert your code here
	static bool Is_ReEnter=false;
	if(Is_ReEnter==true) 
        return;
	unsigned long i=0;
	if(!WxEdit2->GetValue().ToULong(&i,16))
	{
        wxMessageDialog temp(this,"��ַ(16��������)���벻��ȷ!\n");
        temp.ShowModal();
        Is_ReEnter=true;
        WxEdit2->Clear();
        Is_ReEnter=false; 
        WxEdit2->AppendText("00000000"); 
        
    }
}

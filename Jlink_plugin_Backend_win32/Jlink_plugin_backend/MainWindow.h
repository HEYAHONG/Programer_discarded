#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <wx/wx.h>
#include <wx/webview.h>
#include "jlink_wxthread.h"
//(*Headers(MainWindow)
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/timer.h>
//*)

class MainWindow: public wxDialog
{
	public:

		MainWindow(wxWindow* parent,wxWindowID id=wxID_ANY);
		virtual ~MainWindow();

		//(*Declarations(MainWindow)
		wxButton* Button1;
		wxRichTextCtrl* Info;
		wxTimer InfoTimer;
		wxTimer Timer1;
		//*)

		Jlink_wxThread *jlink_thread;

	protected:

		//(*Identifiers(MainWindow)
		static const long ID_RICHTEXTCTRL1;
		static const long ID_BUTTON1;
		static const long ID_TIMER1;
		static const long ID_TIMER2;
		//*)

	private:

		//(*Handlers(MainWindow)
		void OnTimer1Trigger(wxTimerEvent& event);
		void OnPanel1Paint(wxPaintEvent& event);
		void OnClose(wxCloseEvent& event);
		void OnInfoTimerTrigger(wxTimerEvent& event);
		void OnButton1Click(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif

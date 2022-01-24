///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.0-4761b0c)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "NetCapture.h"

///////////////////////////////////////////////////////////////////////////

MainWnd::MainWnd( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	RecvBook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panel1 = new wxPanel( RecvBook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );

	m_button1 = new wxButton( m_panel1, wxID_ANY, wxT("刷新网卡"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_button1, 0, wxALL, 5 );

	wxString m_choice1Choices[] = { wxT("                                               ") };
	int m_choice1NChoices = sizeof( m_choice1Choices ) / sizeof( wxString );
	m_choice1 = new wxChoice( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice1NChoices, m_choice1Choices, 0 );
	m_choice1->SetSelection( 0 );
	bSizer3->Add( m_choice1, 0, wxALL, 5 );

	m_button2 = new wxButton( m_panel1, wxID_ANY, wxT("开始"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_button2, 0, wxALL, 5 );

	m_button3 = new wxButton( m_panel1, wxID_ANY, wxT("清空"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_button3, 0, wxALL, 5 );

	m_button4 = new wxButton( m_panel1, wxID_ANY, wxT("加载配置"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_button4, 0, wxALL, 5 );

	m_button5 = new wxButton( m_panel1, wxID_ANY, wxT("读取报文"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_button5, 0, wxALL, 5 );

	m_button6 = new wxButton( m_panel1, wxID_ANY, wxT("保存报文"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_button6, 0, wxALL, 5 );


	bSizer2->Add( bSizer3, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );

	m_checkBox1 = new wxCheckBox( m_panel1, wxID_ANY, wxT("过滤条件1"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_checkBox1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	wxArrayString m_choice2Choices;
	m_choice2 = new wxChoice( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice2Choices, 0 );
	m_choice2->SetSelection( 0 );
	bSizer4->Add( m_choice2, 0, wxALL, 5 );

	wxString m_choice3Choices[] = { wxT("无条件"), wxT("=="), wxT("!="), wxT(">"), wxT("<") };
	int m_choice3NChoices = sizeof( m_choice3Choices ) / sizeof( wxString );
	m_choice3 = new wxChoice( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice3NChoices, m_choice3Choices, 0 );
	m_choice3->SetSelection( 0 );
	bSizer4->Add( m_choice3, 0, wxALL, 5 );

	m_textCtrl1 = new wxTextCtrl( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_textCtrl1, 0, wxALL, 5 );

	m_checkBox11 = new wxCheckBox( m_panel1, wxID_ANY, wxT("过滤条件2"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_checkBox11, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	wxArrayString m_choice4Choices;
	m_choice4 = new wxChoice( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice4Choices, 0 );
	m_choice4->SetSelection( 0 );
	bSizer4->Add( m_choice4, 0, wxALL, 5 );

	wxString m_choice5Choices[] = { wxT("无条件"), wxT("=="), wxT("!="), wxT(">"), wxT("<") };
	int m_choice5NChoices = sizeof( m_choice5Choices ) / sizeof( wxString );
	m_choice5 = new wxChoice( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice5NChoices, m_choice5Choices, 0 );
	m_choice5->SetSelection( 0 );
	bSizer4->Add( m_choice5, 0, wxALL, 5 );

	m_textCtrl4 = new wxTextCtrl( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_textCtrl4, 0, wxALL, 5 );


	bSizer2->Add( bSizer4, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );

	m_splitter1 = new wxSplitterWindow( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_splitter1->Connect( wxEVT_IDLE, wxIdleEventHandler( MainWnd::m_splitter1OnIdle ), NULL, this );

	m_panel2 = new wxPanel( m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );

	m_grid1 = new wxGrid( m_panel2, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// Grid
	m_grid1->CreateGrid( 0, 7 );
	m_grid1->EnableEditing( false );
	m_grid1->EnableGridLines( true );
	m_grid1->EnableDragGridSize( false );
	m_grid1->SetMargins( 0, 0 );

	// Columns
	m_grid1->SetColSize( 0, 220 );
	m_grid1->SetColSize( 1, 140 );
	m_grid1->SetColSize( 2, 140 );
	m_grid1->SetColSize( 3, 50 );
	m_grid1->SetColSize( 4, 50 );
	m_grid1->SetColSize( 5, 100 );
	m_grid1->SetColSize( 6, 2000 );
	m_grid1->EnableDragColMove( false );
	m_grid1->EnableDragColSize( false );
	m_grid1->SetColLabelValue( 0, wxT("时间") );
	m_grid1->SetColLabelValue( 1, wxT("源地址") );
	m_grid1->SetColLabelValue( 2, wxT("目的地址") );
	m_grid1->SetColLabelValue( 3, wxT("类型") );
	m_grid1->SetColLabelValue( 4, wxT("长度") );
	m_grid1->SetColLabelValue( 5, wxT("备注") );
	m_grid1->SetColLabelValue( 6, wxT("内容") );
	m_grid1->SetColLabelAlignment( wxALIGN_LEFT, wxALIGN_CENTER );

	// Rows
	m_grid1->EnableDragRowSize( false );
	m_grid1->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Label Appearance

	// Cell Defaults
	m_grid1->SetDefaultCellFont( wxFont( 9, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Courier New") ) );
	m_grid1->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	bSizer9->Add( m_grid1, 1, wxALL|wxEXPAND, 5 );


	m_panel2->SetSizer( bSizer9 );
	m_panel2->Layout();
	bSizer9->Fit( m_panel2 );
	m_panel3 = new wxPanel( m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );

	m_splitter2 = new wxSplitterWindow( m_panel3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_splitter2->Connect( wxEVT_IDLE, wxIdleEventHandler( MainWnd::m_splitter2OnIdle ), NULL, this );

	m_panel4 = new wxPanel( m_splitter2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );

	m_textCtrl5 = new wxTextCtrl( m_panel4, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY|wxTE_RICH2 );
	m_textCtrl5->SetFont( wxFont( 9, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Courier New") ) );

	bSizer11->Add( m_textCtrl5, 1, wxALL|wxEXPAND, 5 );


	m_panel4->SetSizer( bSizer11 );
	m_panel4->Layout();
	bSizer11->Fit( m_panel4 );
	m_panel5 = new wxPanel( m_splitter2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxVERTICAL );

	m_treeCtrl1 = new wxTreeCtrl( m_panel5, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE|wxTR_HIDE_ROOT );
	bSizer12->Add( m_treeCtrl1, 1, wxALL|wxEXPAND, 5 );


	m_panel5->SetSizer( bSizer12 );
	m_panel5->Layout();
	bSizer12->Fit( m_panel5 );
	m_splitter2->SplitVertically( m_panel4, m_panel5, 0 );
	bSizer7->Add( m_splitter2, 1, wxEXPAND, 5 );


	m_panel3->SetSizer( bSizer7 );
	m_panel3->Layout();
	bSizer7->Fit( m_panel3 );
	m_splitter1->SplitHorizontally( m_panel2, m_panel3, 0 );
	bSizer5->Add( m_splitter1, 1, wxEXPAND, 5 );


	bSizer2->Add( bSizer5, 1, wxEXPAND, 5 );


	m_panel1->SetSizer( bSizer2 );
	m_panel1->Layout();
	bSizer2->Fit( m_panel1 );
	RecvBook->AddPage( m_panel1, wxT("GnrRecv"), false );

	bSizer1->Add( RecvBook, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();
	m_timer1.SetOwner( this, wxID_ANY );
	m_timer1.Start( 10 );

	m_statusBar1 = this->CreateStatusBar( 2, wxSTB_SIZEGRIP, wxID_ANY );

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_IDLE, wxIdleEventHandler( MainWnd::UpdateOnIdle ) );
	m_button1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWnd::ReFreshGnrNetCard ), NULL, this );
	m_button2->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWnd::StartGnrCapture ), NULL, this );
	m_button3->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWnd::ClearGnrFrame ), NULL, this );
	m_button4->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWnd::LoadGnrCfg ), NULL, this );
	m_button6->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWnd::SaveGnrPcap ), NULL, this );
	m_checkBox1->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainWnd::UpdateGnrFilter1 ), NULL, this );
	m_checkBox11->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainWnd::UpdateGnrFilter2 ), NULL, this );
	m_grid1->Connect( wxEVT_GRID_SELECT_CELL, wxGridEventHandler( MainWnd::ShowGnrSelFrame ), NULL, this );
	this->Connect( wxID_ANY, wxEVT_TIMER, wxTimerEventHandler( MainWnd::UpDateUi10Ms ) );
}

MainWnd::~MainWnd()
{
	// Disconnect Events
	this->Disconnect( wxEVT_IDLE, wxIdleEventHandler( MainWnd::UpdateOnIdle ) );
	m_button1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWnd::ReFreshGnrNetCard ), NULL, this );
	m_button2->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWnd::StartGnrCapture ), NULL, this );
	m_button3->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWnd::ClearGnrFrame ), NULL, this );
	m_button4->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWnd::LoadGnrCfg ), NULL, this );
	m_button6->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWnd::SaveGnrPcap ), NULL, this );
	m_checkBox1->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainWnd::UpdateGnrFilter1 ), NULL, this );
	m_checkBox11->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainWnd::UpdateGnrFilter2 ), NULL, this );
	m_grid1->Disconnect( wxEVT_GRID_SELECT_CELL, wxGridEventHandler( MainWnd::ShowGnrSelFrame ), NULL, this );
	this->Disconnect( wxID_ANY, wxEVT_TIMER, wxTimerEventHandler( MainWnd::UpDateUi10Ms ) );

}

///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "MainWnd.h"

///////////////////////////////////////////////////////////////////////////

MainWnd::MainWnd( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	m_menubar1 = new wxMenuBar( 0 );
	m_menu2 = new wxMenu();
	wxMenuItem* m_menuItem1;
	m_menuItem1 = new wxMenuItem( m_menu2, wxID_ANY, wxString( wxT("关于") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu2->Append( m_menuItem1 );

	m_menubar1->Append( m_menu2, wxT("帮助") );

	this->SetMenuBar( m_menubar1 );

	m_toolBar1 = this->CreateToolBar( wxTB_HORIZONTAL, wxID_ANY );
	ServerIp = new wxTextCtrl( m_toolBar1, wxID_ANY, wxT("100.100.100.100"), wxDefaultPosition, wxDefaultSize, 0 );
	m_toolBar1->AddControl( ServerIp );
	m_button1 = new wxButton( m_toolBar1, wxID_ANY, wxT("连接"), wxDefaultPosition, wxDefaultSize, 0 );
	m_toolBar1->AddControl( m_button1 );
	m_toolBar1->Realize();

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );


	this->SetSizer( bSizer1 );
	this->Layout();
	WndUpdate.SetOwner( this, wxID_ANY );
	StatusTimer.SetOwner( this, wxID_ANY );
	StatusTimer.Start( 100 );

	m_statusBar1 = this->CreateStatusBar( 5, wxSTB_SIZEGRIP, wxID_ANY );

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_IDLE, wxIdleEventHandler( MainWnd::OnWndIdle ) );
	m_menu2->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWnd::ShowAbout ), this, m_menuItem1->GetId());
	m_button1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWnd::LinkServer ), NULL, this );
	this->Connect( wxID_ANY, wxEVT_TIMER, wxTimerEventHandler( MainWnd::StatusUpdate ) );
}

MainWnd::~MainWnd()
{
	// Disconnect Events
	this->Disconnect( wxEVT_IDLE, wxIdleEventHandler( MainWnd::OnWndIdle ) );
	m_button1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWnd::LinkServer ), NULL, this );
	this->Disconnect( wxID_ANY, wxEVT_TIMER, wxTimerEventHandler( MainWnd::StatusUpdate ) );

}

TextPage::TextPage( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );

	m_toolBar2 = new wxToolBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL );
	wxString UpdateModeChoices[] = { wxT("手动刷新"), wxT("周期刷新") };
	int UpdateModeNChoices = sizeof( UpdateModeChoices ) / sizeof( wxString );
	UpdateMode = new wxChoice( m_toolBar2, wxID_ANY, wxDefaultPosition, wxDefaultSize, UpdateModeNChoices, UpdateModeChoices, 0 );
	UpdateMode->SetSelection( 0 );
	m_toolBar2->AddControl( UpdateMode );
	PeriodMs = new wxStaticText( m_toolBar2, wxID_ANY, wxT("刷新周期(Ms):"), wxDefaultPosition, wxDefaultSize, 0 );
	PeriodMs->Wrap( -1 );
	m_toolBar2->AddControl( PeriodMs );
	Period = new wxSpinCtrl( m_toolBar2, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, 100, 100000000, 1000 );
	m_toolBar2->AddControl( Period );
	UpdatePara = new wxStaticText( m_toolBar2, wxID_ANY, wxT("参数:"), wxDefaultPosition, wxDefaultSize, 0 );
	UpdatePara->Wrap( -1 );
	m_toolBar2->AddControl( UpdatePara );
	m_spinCtrl3 = new wxSpinCtrl( m_toolBar2, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -2147483648, 2147483647, 0 );
	m_toolBar2->AddControl( m_spinCtrl3 );
	ManualUpdate = new wxButton( m_toolBar2, wxID_ANY, wxT("刷新"), wxDefaultPosition, wxDefaultSize, 0 );
	m_toolBar2->AddControl( ManualUpdate );
	ManualSet = new wxButton( m_toolBar2, wxID_ANY, wxT("设置"), wxDefaultPosition, wxDefaultSize, 0 );
	m_toolBar2->AddControl( ManualSet );
	m_toolBar2->Realize();

	bSizer3->Add( m_toolBar2, 0, wxEXPAND, 5 );

	m_richText1 = new wxRichTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0|wxVSCROLL|wxHSCROLL|wxNO_BORDER|wxWANTS_CHARS );
	bSizer3->Add( m_richText1, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( bSizer3 );
	this->Layout();
}

TextPage::~TextPage()
{
}

CascadePage::CascadePage( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );

	m_notebook2 = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	bSizer4->Add( m_notebook2, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( bSizer4 );
	this->Layout();
}

CascadePage::~CascadePage()
{
}

GridPage::GridPage( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );

	m_toolBar2 = new wxToolBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL );
	wxString UpdateModeChoices[] = { wxT("手动刷新"), wxT("周期刷新") };
	int UpdateModeNChoices = sizeof( UpdateModeChoices ) / sizeof( wxString );
	UpdateMode = new wxChoice( m_toolBar2, wxID_ANY, wxDefaultPosition, wxDefaultSize, UpdateModeNChoices, UpdateModeChoices, 0 );
	UpdateMode->SetSelection( 0 );
	m_toolBar2->AddControl( UpdateMode );
	PeriodMs = new wxStaticText( m_toolBar2, wxID_ANY, wxT("刷新周期(Ms):"), wxDefaultPosition, wxDefaultSize, 0 );
	PeriodMs->Wrap( -1 );
	m_toolBar2->AddControl( PeriodMs );
	Period = new wxSpinCtrl( m_toolBar2, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, 100, 100000000, 1000 );
	m_toolBar2->AddControl( Period );
	UpdatePara = new wxStaticText( m_toolBar2, wxID_ANY, wxT("参数:"), wxDefaultPosition, wxDefaultSize, 0 );
	UpdatePara->Wrap( -1 );
	m_toolBar2->AddControl( UpdatePara );
	m_spinCtrl3 = new wxSpinCtrl( m_toolBar2, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -2147483648, 2147483647, 0 );
	m_toolBar2->AddControl( m_spinCtrl3 );
	ManualUpdate = new wxButton( m_toolBar2, wxID_ANY, wxT("刷新"), wxDefaultPosition, wxDefaultSize, 0 );
	m_toolBar2->AddControl( ManualUpdate );
	ManualSet = new wxButton( m_toolBar2, wxID_ANY, wxT("设置"), wxDefaultPosition, wxDefaultSize, 0 );
	m_toolBar2->AddControl( ManualSet );
	m_toolBar2->Realize();

	bSizer5->Add( m_toolBar2, 0, wxEXPAND, 5 );

	m_grid1 = new wxGrid( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// Grid
	m_grid1->CreateGrid( 5, 5 );
	m_grid1->EnableEditing( true );
	m_grid1->EnableGridLines( true );
	m_grid1->EnableDragGridSize( false );
	m_grid1->SetMargins( 0, 0 );

	// Columns
	m_grid1->EnableDragColMove( false );
	m_grid1->EnableDragColSize( true );
	m_grid1->SetColLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Rows
	m_grid1->EnableDragRowSize( true );
	m_grid1->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Label Appearance

	// Cell Defaults
	m_grid1->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	bSizer5->Add( m_grid1, 1, wxALL|wxEXPAND, 5 );


	this->SetSizer( bSizer5 );
	this->Layout();
}

GridPage::~GridPage()
{
}

SetPage::SetPage( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );

	m_toolBar2 = new wxToolBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL );
	wxString UpdateModeChoices[] = { wxT("手动刷新"), wxT("周期刷新") };
	int UpdateModeNChoices = sizeof( UpdateModeChoices ) / sizeof( wxString );
	UpdateMode = new wxChoice( m_toolBar2, wxID_ANY, wxDefaultPosition, wxDefaultSize, UpdateModeNChoices, UpdateModeChoices, 0 );
	UpdateMode->SetSelection( 0 );
	m_toolBar2->AddControl( UpdateMode );
	PeriodMs = new wxStaticText( m_toolBar2, wxID_ANY, wxT("刷新周期(Ms):"), wxDefaultPosition, wxDefaultSize, 0 );
	PeriodMs->Wrap( -1 );
	m_toolBar2->AddControl( PeriodMs );
	Period = new wxSpinCtrl( m_toolBar2, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, 100, 100000000, 1000 );
	m_toolBar2->AddControl( Period );
	UpdatePara = new wxStaticText( m_toolBar2, wxID_ANY, wxT("参数:"), wxDefaultPosition, wxDefaultSize, 0 );
	UpdatePara->Wrap( -1 );
	m_toolBar2->AddControl( UpdatePara );
	m_spinCtrl3 = new wxSpinCtrl( m_toolBar2, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -2147483648, 2147483647, 0 );
	m_toolBar2->AddControl( m_spinCtrl3 );
	ManualUpdate = new wxButton( m_toolBar2, wxID_ANY, wxT("刷新"), wxDefaultPosition, wxDefaultSize, 0 );
	m_toolBar2->AddControl( ManualUpdate );
	ManualSet = new wxButton( m_toolBar2, wxID_ANY, wxT("设置"), wxDefaultPosition, wxDefaultSize, 0 );
	m_toolBar2->AddControl( ManualSet );
	m_toolBar2->Realize();

	bSizer5->Add( m_toolBar2, 0, wxEXPAND, 5 );


	this->SetSizer( bSizer5 );
	this->Layout();
}

SetPage::~SetPage()
{
}

LogWnd::LogWnd( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	LogBox = new wxBoxSizer( wxVERTICAL );

	wxStaticBoxSizer* bSize10222;
	bSize10222 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("唯一性代码") ), wxVERTICAL );

	idtext = new wxTextCtrl( bSize10222->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSize10222->Add( idtext, 1, wxALL|wxEXPAND, 5 );


	LogBox->Add( bSize10222, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );

	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("帐号") ), wxVERTICAL );

	nametext = new wxTextCtrl( sbSizer2->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer2->Add( nametext, 1, wxALL|wxEXPAND, 5 );


	bSizer8->Add( sbSizer2, 0, wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("密码") ), wxVERTICAL );

	pwtext = new wxTextCtrl( sbSizer3->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD );
	sbSizer3->Add( pwtext, 1, wxALL|wxEXPAND, 5 );


	bSizer8->Add( sbSizer3, 0, wxEXPAND, 5 );


	LogBox->Add( bSizer8, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxHORIZONTAL );

	m_button9 = new wxButton( this, wxID_ANY, wxT("确定"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( m_button9, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_button10 = new wxButton( this, wxID_ANY, wxT("取消"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( m_button10, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	LogBox->Add( bSizer7, 1, wxALIGN_CENTER_HORIZONTAL, 5 );


	this->SetSizer( LogBox );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_button9->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LogWnd::Enter ), NULL, this );
	m_button10->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LogWnd::Cancel ), NULL, this );
}

LogWnd::~LogWnd()
{
	// Disconnect Events
	m_button9->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LogWnd::Enter ), NULL, this );
	m_button10->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LogWnd::Cancel ), NULL, this );

}

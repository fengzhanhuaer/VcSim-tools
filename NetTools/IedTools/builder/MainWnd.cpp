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

	RootBox = new wxBoxSizer( wxVERTICAL );


	this->SetSizer( RootBox );
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

TextWnd::TextWnd( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );

	wxStaticBoxSizer* panelCtrl;
	panelCtrl = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("label") ), wxHORIZONTAL );

	wxStaticBoxSizer* sbdPara1;
	sbdPara1 = new wxStaticBoxSizer( new wxStaticBox( panelCtrl->GetStaticBox(), wxID_ANY, wxT("label") ), wxVERTICAL );

	dPara1 = new wxSpinCtrlDouble( sbdPara1->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100, 0, 1 );
	dPara1->SetDigits( 0 );
	dPara1->Enable( false );

	sbdPara1->Add( dPara1, 1, wxALL|wxEXPAND, 5 );


	panelCtrl->Add( sbdPara1, 1, wxEXPAND, 5 );

	wxStaticBoxSizer* sbdPara2;
	sbdPara2 = new wxStaticBoxSizer( new wxStaticBox( panelCtrl->GetStaticBox(), wxID_ANY, wxT("label") ), wxVERTICAL );

	dPara2 = new wxSpinCtrlDouble( sbdPara2->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100, 0, 1 );
	dPara2->SetDigits( 0 );
	sbdPara2->Add( dPara2, 0, wxALL, 5 );


	panelCtrl->Add( sbdPara2, 1, wxEXPAND, 5 );

	wxStaticBoxSizer* sbdPara3;
	sbdPara3 = new wxStaticBoxSizer( new wxStaticBox( panelCtrl->GetStaticBox(), wxID_ANY, wxT("label") ), wxVERTICAL );

	dPara3 = new wxSpinCtrlDouble( sbdPara3->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100, 0, 1 );
	dPara3->SetDigits( 0 );
	dPara3->Enable( false );

	sbdPara3->Add( dPara3, 1, wxALL|wxEXPAND, 5 );


	panelCtrl->Add( sbdPara3, 1, wxEXPAND, 5 );

	Check1 = new wxCheckBox( panelCtrl->GetStaticBox(), wxID_ANY, wxT("Check Me!"), wxDefaultPosition, wxDefaultSize, 0 );
	Check1->Enable( false );

	panelCtrl->Add( Check1, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	Check2 = new wxCheckBox( panelCtrl->GetStaticBox(), wxID_ANY, wxT("Check Me!"), wxDefaultPosition, wxDefaultSize, 0 );
	Check2->Enable( false );

	panelCtrl->Add( Check2, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	Check3 = new wxCheckBox( panelCtrl->GetStaticBox(), wxID_ANY, wxT("Check Me!"), wxDefaultPosition, wxDefaultSize, 0 );
	Check3->Enable( false );

	panelCtrl->Add( Check3, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	Button1 = new wxButton( panelCtrl->GetStaticBox(), wxID_ANY, wxT("MyButton"), wxDefaultPosition, wxDefaultSize, 0 );
	Button1->Enable( false );

	panelCtrl->Add( Button1, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	Button2 = new wxButton( panelCtrl->GetStaticBox(), wxID_ANY, wxT("MyButton"), wxDefaultPosition, wxDefaultSize, 0 );
	Button2->Enable( false );

	panelCtrl->Add( Button2, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	Button3 = new wxButton( panelCtrl->GetStaticBox(), wxID_ANY, wxT("MyButton"), wxDefaultPosition, wxDefaultSize, 0 );
	Button3->Enable( false );

	panelCtrl->Add( Button3, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	wxString updateModeChoices[] = { wxT("手动刷新"), wxT("自动刷新") };
	int updateModeNChoices = sizeof( updateModeChoices ) / sizeof( wxString );
	updateMode = new wxChoice( panelCtrl->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, updateModeNChoices, updateModeChoices, 0 );
	updateMode->SetSelection( 0 );
	panelCtrl->Add( updateMode, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	UpdateButton = new wxButton( panelCtrl->GetStaticBox(), wxID_ANY, wxT("刷新"), wxDefaultPosition, wxDefaultSize, 0 );
	panelCtrl->Add( UpdateButton, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer->Add( panelCtrl, 0, wxEXPAND, 5 );

	text = new wxRichTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxVSCROLL|wxHSCROLL|wxNO_BORDER|wxWANTS_CHARS );
	bSizer->Add( text, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( bSizer );
	this->Layout();
}

TextWnd::~TextWnd()
{
}

GridWnd::GridWnd( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );

	m_grid = new wxGrid( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// Grid
	m_grid->CreateGrid( 5, 5 );
	m_grid->EnableEditing( true );
	m_grid->EnableGridLines( true );
	m_grid->EnableDragGridSize( false );
	m_grid->SetMargins( 0, 0 );

	// Columns
	m_grid->EnableDragColMove( false );
	m_grid->EnableDragColSize( true );
	m_grid->SetColLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Rows
	m_grid->EnableDragRowSize( true );
	m_grid->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Label Appearance

	// Cell Defaults
	m_grid->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	bSizer->Add( m_grid, 1, wxALL|wxEXPAND, 5 );


	this->SetSizer( bSizer );
	this->Layout();
}

GridWnd::~GridWnd()
{
}

MyPanel10::MyPanel10( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );

	m_dataViewListCtrl000 = new wxDataViewListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer->Add( m_dataViewListCtrl000, 1, wxALL|wxEXPAND, 5 );


	this->SetSizer( bSizer );
	this->Layout();
}

MyPanel10::~MyPanel10()
{
}

CascadeWnd::CascadeWnd( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer( wxVERTICAL );

	ListPage = new wxListbook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLB_DEFAULT );
	m_panel000 = new wxPanel( ListPage, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* pb000;
	pb000 = new wxBoxSizer( wxVERTICAL );


	m_panel000->SetSizer( pb000 );
	m_panel000->Layout();
	pb000->Fit( m_panel000 );
	ListPage->AddPage( m_panel000, wxT("a page"), false );
	#ifdef __WXGTK__ // Small icon style not supported in GTK
	wxListView* ListPageListView = ListPage->GetListView();
	long ListPageFlags = ListPageListView->GetWindowStyleFlag();
	if( ListPageFlags & wxLC_SMALL_ICON )
	{
		ListPageFlags = ( ListPageFlags & ~wxLC_SMALL_ICON ) | wxLC_ICON;
	}
	ListPageListView->SetWindowStyleFlag( ListPageFlags );
	#endif

	bSizer21->Add( ListPage, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( bSizer21 );
	this->Layout();
}

CascadeWnd::~CascadeWnd()
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

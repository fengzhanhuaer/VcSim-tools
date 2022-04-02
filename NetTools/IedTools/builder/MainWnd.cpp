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
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );

	panelCtrl1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("label") ), wxHORIZONTAL );

	sbdPara11 = new wxStaticBoxSizer( new wxStaticBox( panelCtrl1->GetStaticBox(), wxID_ANY, wxT("label") ), wxVERTICAL );

	dPara11 = new wxSpinCtrlDouble( sbdPara11->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100, 0, 1 );
	dPara11->SetDigits( 0 );
	sbdPara11->Add( dPara11, 1, wxALL|wxEXPAND, 5 );


	panelCtrl1->Add( sbdPara11, 1, wxEXPAND, 5 );

	sbdPara21 = new wxStaticBoxSizer( new wxStaticBox( panelCtrl1->GetStaticBox(), wxID_ANY, wxT("label") ), wxVERTICAL );

	dPara21 = new wxSpinCtrlDouble( sbdPara21->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100, 0, 1 );
	dPara21->SetDigits( 0 );
	dPara21->Enable( false );

	sbdPara21->Add( dPara21, 1, wxALL|wxEXPAND, 5 );


	panelCtrl1->Add( sbdPara21, 1, wxEXPAND, 5 );

	sbdPara31 = new wxStaticBoxSizer( new wxStaticBox( panelCtrl1->GetStaticBox(), wxID_ANY, wxT("label") ), wxVERTICAL );

	dPara31 = new wxSpinCtrlDouble( sbdPara31->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100, 0, 1 );
	dPara31->SetDigits( 0 );
	dPara31->Enable( false );

	sbdPara31->Add( dPara31, 1, wxALL|wxEXPAND, 5 );


	panelCtrl1->Add( sbdPara31, 1, wxEXPAND, 5 );

	Check11 = new wxCheckBox( panelCtrl1->GetStaticBox(), wxID_ANY, wxT("Check Me!"), wxDefaultPosition, wxDefaultSize, 0 );
	Check11->Hide();

	panelCtrl1->Add( Check11, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	Check21 = new wxCheckBox( panelCtrl1->GetStaticBox(), wxID_ANY, wxT("Check Me!"), wxDefaultPosition, wxDefaultSize, 0 );
	Check21->Hide();

	panelCtrl1->Add( Check21, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	Check31 = new wxCheckBox( panelCtrl1->GetStaticBox(), wxID_ANY, wxT("Check Me!"), wxDefaultPosition, wxDefaultSize, 0 );
	Check31->Hide();

	panelCtrl1->Add( Check31, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	Button11 = new wxButton( panelCtrl1->GetStaticBox(), wxID_ANY, wxT("MyButton"), wxDefaultPosition, wxDefaultSize, 0 );
	Button11->Hide();

	panelCtrl1->Add( Button11, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	Button21 = new wxButton( panelCtrl1->GetStaticBox(), wxID_ANY, wxT("MyButton"), wxDefaultPosition, wxDefaultSize, 0 );
	Button21->Hide();

	panelCtrl1->Add( Button21, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	Button31 = new wxButton( panelCtrl1->GetStaticBox(), wxID_ANY, wxT("MyButton"), wxDefaultPosition, wxDefaultSize, 0 );
	Button31->Hide();

	panelCtrl1->Add( Button31, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	wxString updateMode1Choices[] = { wxT("手动刷新"), wxT("自动刷新") };
	int updateMode1NChoices = sizeof( updateMode1Choices ) / sizeof( wxString );
	updateMode1 = new wxChoice( panelCtrl1->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, updateMode1NChoices, updateMode1Choices, 0 );
	updateMode1->SetSelection( 0 );
	panelCtrl1->Add( updateMode1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	UpdateButton1 = new wxButton( panelCtrl1->GetStaticBox(), wxID_ANY, wxT("刷新"), wxDefaultPosition, wxDefaultSize, 0 );
	panelCtrl1->Add( UpdateButton1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer->Add( panelCtrl1, 0, wxEXPAND, 5 );


	bSizer1->Add( bSizer, 1, wxEXPAND, 5 );

	text = new wxRichTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxVSCROLL|wxHSCROLL|wxNO_BORDER|wxWANTS_CHARS );
	bSizer1->Add( text, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( bSizer1 );
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

DataView::DataView( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );

	m_dataViewListCtrl000 = new wxDataViewListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer->Add( m_dataViewListCtrl000, 1, wxALL|wxEXPAND, 5 );


	this->SetSizer( bSizer );
	this->Layout();
}

DataView::~DataView()
{
}

WhiteBoard::WhiteBoard( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
	bSizer = new wxBoxSizer( wxVERTICAL );


	this->SetSizer( bSizer );
	this->Layout();
}

WhiteBoard::~WhiteBoard()
{
}

CascadeWnd::CascadeWnd( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer( wxVERTICAL );

	ListPage = new wxListbook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLB_DEFAULT );
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

	// Connect Events
	ListPage->Connect( wxEVT_COMMAND_LISTBOOK_PAGE_CHANGED, wxListbookEventHandler( CascadeWnd::PageChanged ), NULL, this );
	ListPage->Connect( wxEVT_COMMAND_LISTBOOK_PAGE_CHANGING, wxListbookEventHandler( CascadeWnd::PageChanging ), NULL, this );
}

CascadeWnd::~CascadeWnd()
{
	// Disconnect Events
	ListPage->Disconnect( wxEVT_COMMAND_LISTBOOK_PAGE_CHANGED, wxListbookEventHandler( CascadeWnd::PageChanged ), NULL, this );
	ListPage->Disconnect( wxEVT_COMMAND_LISTBOOK_PAGE_CHANGING, wxListbookEventHandler( CascadeWnd::PageChanging ), NULL, this );

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

///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.0-4761b0c)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "MainWnd.h"

///////////////////////////////////////////////////////////////////////////

MainWnd::MainWnd( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	m_statusBar1 = this->CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );
	m_menubar1 = new wxMenuBar( 0 );
	m_menu1 = new wxMenu();
	m_menubar1->Append( m_menu1, wxT("文件") );

	this->SetMenuBar( m_menubar1 );

	m_toolBar1 = this->CreateToolBar( wxTB_HORIZONTAL, wxID_ANY );
	wxString NetCardChoices[] = { wxT("                        ") };
	int NetCardNChoices = sizeof( NetCardChoices ) / sizeof( wxString );
	NetCard = new wxChoice( m_toolBar1, wxID_ANY, wxDefaultPosition, wxDefaultSize, NetCardNChoices, NetCardChoices, 0 );
	NetCard->SetSelection( 0 );
	m_toolBar1->AddControl( NetCard );
	RefreshNetCard = new wxButton( m_toolBar1, wxID_ANY, wxT("刷新网口"), wxDefaultPosition, wxDefaultSize, 0 );
	m_toolBar1->AddControl( RefreshNetCard );
	m_button7 = new wxButton( m_toolBar1, wxID_ANY, wxT("打开网口"), wxDefaultPosition, wxDefaultSize, 0 );
	m_toolBar1->AddControl( m_button7 );
	m_toolBar1->Realize();

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	m_notebook1 = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	SendPage = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );

	sendBook = new wxNotebook( SendPage, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panel8 = new wxPanel( sendBook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer101;
	bSizer101 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText31 = new wxStaticText( m_panel8, wxID_ANY, wxT("发送间隔："), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText31->Wrap( -1 );
	bSizer11->Add( m_staticText31, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_spinCtrlDouble1 = new wxSpinCtrlDouble( m_panel8, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT|wxSP_ARROW_KEYS, 0.001, 1e+06, 1, 1 );
	m_spinCtrlDouble1->SetDigits( 3 );
	bSizer11->Add( m_spinCtrlDouble1, 0, wxALL, 5 );

	m_staticText5 = new wxStaticText( m_panel8, wxID_ANY, wxT("ms"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	bSizer11->Add( m_staticText5, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_staticText7 = new wxStaticText( m_panel8, wxID_ANY, wxT("发送次数"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	bSizer11->Add( m_staticText7, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_spinCtrl3 = new wxSpinCtrl( m_panel8, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT|wxSP_ARROW_KEYS, -1, 1000000000, 1 );
	m_spinCtrl3->SetToolTip( wxT("-1表示无数次") );

	bSizer11->Add( m_spinCtrl3, 0, wxALL, 5 );

	m_button11 = new wxButton( m_panel8, wxID_ANY, wxT("发送"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer11->Add( m_button11, 0, wxALL, 5 );


	bSizer101->Add( bSizer11, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxVERTICAL );

	m_textCtrl4 = new wxTextCtrl( m_panel8, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	m_textCtrl4->SetToolTip( wxT("请输入16进制报文") );

	bSizer12->Add( m_textCtrl4, 1, wxALL|wxEXPAND, 5 );


	bSizer101->Add( bSizer12, 1, wxEXPAND, 5 );


	m_panel8->SetSizer( bSizer101 );
	m_panel8->Layout();
	bSizer101->Fit( m_panel8 );
	sendBook->AddPage( m_panel8, wxT("以太网报文"), true );
	m_panel9 = new wxPanel( sendBook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	sendBook->AddPage( m_panel9, wxT("UDP报文"), false );
	m_panel10 = new wxPanel( sendBook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	sendBook->AddPage( m_panel10, wxT("TCP报文"), false );

	bSizer2->Add( sendBook, 1, wxEXPAND | wxALL, 5 );


	SendPage->SetSizer( bSizer2 );
	SendPage->Layout();
	bSizer2->Fit( SendPage );
	m_notebook1->AddPage( SendPage, wxT("Send"), true );
	RecvPage = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );

	recvBook = new wxNotebook( RecvPage, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	bSizer3->Add( recvBook, 1, wxEXPAND | wxALL, 5 );


	RecvPage->SetSizer( bSizer3 );
	RecvPage->Layout();
	bSizer3->Fit( RecvPage );
	m_notebook1->AddPage( RecvPage, wxT("Recv"), false );
	FmtChange = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );

	m_notebook4 = new wxNotebook( FmtChange, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panel6 = new wxPanel( m_notebook4, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxHORIZONTAL );

	m_panel7 = new wxPanel( m_panel6, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE|wxTAB_TRAVERSAL );
	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 0, 2, 0, 0 );

	m_staticText3 = new wxStaticText( m_panel7, wxID_ANY, wxT("SV转BIN格式"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	gSizer1->Add( m_staticText3, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_button8 = new wxButton( m_panel7, wxID_ANY, wxT("打开"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_button8, 0, wxALL, 5 );


	m_panel7->SetSizer( gSizer1 );
	m_panel7->Layout();
	gSizer1->Fit( m_panel7 );
	bSizer10->Add( m_panel7, 0, 0, 5 );


	m_panel6->SetSizer( bSizer10 );
	m_panel6->Layout();
	bSizer10->Fit( m_panel6 );
	m_notebook4->AddPage( m_panel6, wxT("SV通道提取"), false );

	bSizer8->Add( m_notebook4, 1, wxEXPAND | wxALL, 5 );


	FmtChange->SetSizer( bSizer8 );
	FmtChange->Layout();
	bSizer8->Fit( FmtChange );
	m_notebook1->AddPage( FmtChange, wxT("格式转换"), false );

	bSizer1->Add( m_notebook1, 1, wxALL|wxEXPAND, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainWnd::WndClose ) );
	RefreshNetCard->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWnd::refreshNetCard ), NULL, this );
	m_button7->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWnd::OpenNetCard ), NULL, this );
	m_button11->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWnd::SendEthnetFrame ), NULL, this );
	m_button8->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWnd::OpenSvPcap2Bin ), NULL, this );
}

MainWnd::~MainWnd()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainWnd::WndClose ) );
	RefreshNetCard->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWnd::refreshNetCard ), NULL, this );
	m_button7->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWnd::OpenNetCard ), NULL, this );
	m_button11->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWnd::SendEthnetFrame ), NULL, this );
	m_button8->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWnd::OpenSvPcap2Bin ), NULL, this );

}

recvPanel::recvPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer35;
	bSizer35 = new wxBoxSizer( wxHORIZONTAL );

	BtStart = new wxButton( this, wxID_ANY, wxT("开始"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer35->Add( BtStart, 0, wxALL, 5 );

	m_button3 = new wxButton( this, wxID_ANY, wxT("清空"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer35->Add( m_button3, 0, wxALL, 5 );

	dispRtFrame = new wxCheckBox( this, wxID_ANY, wxT("显示实时帧"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer35->Add( dispRtFrame, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	recvCntText = new wxStaticText( this, wxID_ANY, wxT("             0"), wxDefaultPosition, wxDefaultSize, 0 );
	recvCntText->Wrap( -1 );
	bSizer35->Add( recvCntText, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_button5 = new wxButton( this, wxID_ANY, wxT("加载配置"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer35->Add( m_button5, 0, wxALL, 5 );

	m_button6 = new wxButton( this, wxID_ANY, wxT("读取报文"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer35->Add( m_button6, 0, wxALL, 5 );

	m_button4 = new wxButton( this, wxID_ANY, wxT("保存报文"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer35->Add( m_button4, 0, wxALL, 5 );

	wxArrayString SelItem1Choices;
	SelItem1 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, SelItem1Choices, 0 );
	SelItem1->SetSelection( 0 );
	bSizer35->Add( SelItem1, 0, wxALL, 5 );

	wxString SelCdt1Choices[] = { wxT("无条件"), wxT("=="), wxT("!="), wxT(">"), wxT("<") };
	int SelCdt1NChoices = sizeof( SelCdt1Choices ) / sizeof( wxString );
	SelCdt1 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, SelCdt1NChoices, SelCdt1Choices, 0 );
	SelCdt1->SetSelection( 0 );
	bSizer35->Add( SelCdt1, 0, wxALL, 5 );

	SelText1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	SelText1->SetToolTip( wxT("按回车键启动筛选") );

	bSizer35->Add( SelText1, 0, wxALL, 5 );

	wxArrayString SelItem2Choices;
	SelItem2 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, SelItem2Choices, 0 );
	SelItem2->SetSelection( 0 );
	bSizer35->Add( SelItem2, 0, wxALL, 5 );

	wxString SelCdt2Choices[] = { wxT("无条件"), wxT("=="), wxT("!="), wxT(">"), wxT("<") };
	int SelCdt2NChoices = sizeof( SelCdt2Choices ) / sizeof( wxString );
	SelCdt2 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, SelCdt2NChoices, SelCdt2Choices, 0 );
	SelCdt2->SetSelection( 0 );
	bSizer35->Add( SelCdt2, 0, wxALL, 5 );

	SelText2 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	SelText2->SetToolTip( wxT("按回车键启动筛选") );

	bSizer35->Add( SelText2, 0, wxALL, 5 );


	bSizer6->Add( bSizer35, 0, wxEXPAND, 5 );

	m_splitter1 = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_splitter1->Connect( wxEVT_IDLE, wxIdleEventHandler( recvPanel::m_splitter1OnIdle ), NULL, this );

	m_panel6 = new wxPanel( m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );

	FrameList = new wxListCtrl( m_panel6, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL );
	bSizer8->Add( FrameList, 1, wxALL|wxEXPAND, 5 );


	m_panel6->SetSizer( bSizer8 );
	m_panel6->Layout();
	bSizer8->Fit( m_panel6 );
	m_panel7 = new wxPanel( m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxHORIZONTAL );

	RtFrameText = new wxTextCtrl( m_panel7, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY|wxTE_RICH2 );
	RtFrameText->SetFont( wxFont( 9, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Courier New") ) );

	bSizer9->Add( RtFrameText, 1, wxALL|wxEXPAND, 5 );

	RtFrameTree = new wxTreeCtrl( m_panel7, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE|wxTR_HAS_BUTTONS|wxTR_HIDE_ROOT|wxTR_SINGLE );
	bSizer9->Add( RtFrameTree, 1, wxALL|wxEXPAND, 5 );


	m_panel7->SetSizer( bSizer9 );
	m_panel7->Layout();
	bSizer9->Fit( m_panel7 );
	m_splitter1->SplitHorizontally( m_panel6, m_panel7, 0 );
	bSizer6->Add( m_splitter1, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer6 );
	this->Layout();
	m_timer1.SetOwner( this, wxID_ANY );

	// Connect Events
	BtStart->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( recvPanel::BtStartPcap ), NULL, this );
	m_button3->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( recvPanel::ClearFrame ), NULL, this );
	m_button5->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( recvPanel::LoadXml ), NULL, this );
	m_button6->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( recvPanel::LoadPcap ), NULL, this );
	m_button4->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( recvPanel::SaveFile ), NULL, this );
	SelItem1->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( recvPanel::SelectFilterItem1 ), NULL, this );
	SelCdt1->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( recvPanel::SelectFilterCdt1 ), NULL, this );
	SelText1->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( recvPanel::SetFilterCtx1 ), NULL, this );
	SelItem2->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( recvPanel::SelectFilterItem2 ), NULL, this );
	SelCdt2->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( recvPanel::SelectFilterCdt2 ), NULL, this );
	SelText2->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( recvPanel::SetFilterCtx2 ), NULL, this );
	FrameList->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( recvPanel::FrameSelected ), NULL, this );
	RtFrameTree->Connect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( recvPanel::SelNodeChange ), NULL, this );
	this->Connect( wxID_ANY, wxEVT_TIMER, wxTimerEventHandler( recvPanel::OnTimer ) );
}

recvPanel::~recvPanel()
{
	// Disconnect Events
	BtStart->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( recvPanel::BtStartPcap ), NULL, this );
	m_button3->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( recvPanel::ClearFrame ), NULL, this );
	m_button5->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( recvPanel::LoadXml ), NULL, this );
	m_button6->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( recvPanel::LoadPcap ), NULL, this );
	m_button4->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( recvPanel::SaveFile ), NULL, this );
	SelItem1->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( recvPanel::SelectFilterItem1 ), NULL, this );
	SelCdt1->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( recvPanel::SelectFilterCdt1 ), NULL, this );
	SelText1->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( recvPanel::SetFilterCtx1 ), NULL, this );
	SelItem2->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( recvPanel::SelectFilterItem2 ), NULL, this );
	SelCdt2->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( recvPanel::SelectFilterCdt2 ), NULL, this );
	SelText2->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( recvPanel::SetFilterCtx2 ), NULL, this );
	FrameList->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( recvPanel::FrameSelected ), NULL, this );
	RtFrameTree->Disconnect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( recvPanel::SelNodeChange ), NULL, this );
	this->Disconnect( wxID_ANY, wxEVT_TIMER, wxTimerEventHandler( recvPanel::OnTimer ) );

}

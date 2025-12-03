
#include <iostream>
#include <wx/wx.h>
// #include <wx/gbsizer.h>

class MyFrame : public wxFrame {
private:
    enum MenuID {
        // File
        FILE_OPEN,
        FILE_SAVE,
        FILE_EXIT,

        // Edit
        EDIT_CHANGE_SET,

        // Help
        HELP_ABOUT
    };

    wxDialog* add_matrix_dialog;
    wxDialog* about_dialog;
    wxDialog* encoding_set_dialog;

public:
    MyFrame(const wxPoint& pos, const wxSize& size, const wxString& title);
    ~MyFrame() {

        // we need to delete this window to properly exit 
        // the mainloop.
        delete add_matrix_dialog;
        delete about_dialog;
        delete encoding_set_dialog;
    }

    void CreateDialogs();

    // events
    void OnClose(wxCloseEvent& ev);
};

MyFrame::MyFrame(const wxPoint& pos, const wxSize& size, const wxString& title) 
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    CreateDialogs();

    wxMenu* file_menu = new wxMenu();
    file_menu->Append(FILE_OPEN, "Open");
    file_menu->Append(FILE_SAVE, "Save");
    file_menu->AppendSeparator();
    file_menu->Append(FILE_EXIT, "Exit");

    wxMenu* edit_menu = new wxMenu();
    edit_menu->Append(EDIT_CHANGE_SET, "Change Encoding Set");
    
    wxMenu* help_menu = new wxMenu();
    help_menu->Append(HELP_ABOUT, "About");

    wxMenuBar* menu_bar = new wxMenuBar();
    menu_bar->Append(file_menu, "File");
    menu_bar->Append(edit_menu, "Edit");
    menu_bar->Append(help_menu, "Help");

    SetMenuBar(menu_bar);
    CreateStatusBar(1);

    const int MARGIN = 10;

    wxSize encoding_matrix_label_size;

    wxPanel* top_panel = new wxPanel(this, wxID_ANY);
    {
        wxStaticText* encoding_matrix_label = new wxStaticText(top_panel, wxID_ANY, "Encoding Matrix");
        wxComboBox* encoding_combo_box = new wxComboBox(top_panel, wxID_ANY);
        wxButton* add_button = new wxButton(top_panel, wxID_ANY, "Add");
        wxButton* edit_button = new wxButton(top_panel, wxID_ANY, "Edit");

        wxFlexGridSizer* top_sizer = new wxFlexGridSizer(1, 4, MARGIN, MARGIN);
        top_sizer->AddGrowableCol(1);
        top_sizer->Add(encoding_matrix_label, 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxBOTTOM | wxTOP, MARGIN);
        top_sizer->Add(encoding_combo_box, 1, wxEXPAND | wxBOTTOM | wxTOP, MARGIN);
        top_sizer->Add(add_button, 0, wxBOTTOM | wxTOP, MARGIN);
        top_sizer->Add(edit_button, 0, wxRIGHT | wxBOTTOM | wxTOP, MARGIN);

        encoding_matrix_label_size = encoding_matrix_label->GetSize();

        top_panel->SetSizerAndFit(top_sizer);
    }

    wxPanel* body_panel = new wxPanel(this, wxID_ANY);
    {
        wxStaticText* message_label = new wxStaticText(
            body_panel,
            wxID_ANY,
            "Message",
            wxDefaultPosition,
            encoding_matrix_label_size
        );

        wxTextCtrl* message_entry = new wxTextCtrl(body_panel, wxID_ANY);
        wxButton* encode_button = new wxButton(body_panel, wxID_ANY, "Encode");
        wxButton* decode_button = new wxButton(body_panel, wxID_ANY, "Decode");

        wxTextCtrl* emessage = new wxTextCtrl(
            body_panel,
            wxID_ANY,
            wxEmptyString,
            wxDefaultPosition,
            wxSize(500, 400),
            wxTE_MULTILINE
        );
        
        wxFlexGridSizer* body_sizer = new wxFlexGridSizer(2, 3, 0, 0);
        // wxGridBagSizer* body_sizer = new wxGridBagSizer(2, 3);

        body_sizer->AddGrowableCol(1);
        body_sizer->AddGrowableRow(1);
        
        body_sizer->Add(message_label, 0, wxALIGN_CENTRE | wxALL, MARGIN);
        body_sizer->Add(message_entry, 0, wxEXPAND | wxTOP | wxBOTTOM | wxRIGHT, MARGIN);
        body_sizer->Add(encode_button, 0, wxTOP | wxBOTTOM | wxRIGHT, MARGIN);

        body_sizer->Add(0, 0, 0); // empty
        body_sizer->Add(emessage, 0, wxEXPAND | wxRIGHT | wxBOTTOM, MARGIN);
        body_sizer->Add(decode_button, 0, wxBOTTOM | wxRIGHT, MARGIN);

        body_panel->SetSizer(body_sizer);
    }

    wxSizer* main_box = new wxBoxSizer(wxVERTICAL);
    main_box->Add(top_panel, 0, wxEXPAND);
    main_box->Add(0, 20, 0);
    main_box->Add(body_panel, 1, wxEXPAND);

    // this->SetMinSize(wxSize(FromDIP(500), FromDIP(700)));
    this->SetSizerAndFit(main_box);

    SetStatusText("Ready...", 0);
}

void MyFrame::CreateDialogs() {

    add_matrix_dialog = new wxDialog(NULL, wxID_ANY, "Add new encoding matrix");
    // TBD ...

    about_dialog = new wxDialog(NULL, wxID_ANY, "About Dialog");
    // TBD ...

    encoding_set_dialog = new wxDialog(NULL, wxID_ANY, "Encoding Set");
    // TBD ...
}

class MyApp : public wxApp {
public:
    bool OnInit();
};

bool MyApp::OnInit() {
    MyFrame* frame = new MyFrame(wxDefaultPosition, wxDefaultSize, "Cryptography Calculator");
    frame->Show(true);
    return true;
}

wxIMPLEMENT_APP(MyApp);
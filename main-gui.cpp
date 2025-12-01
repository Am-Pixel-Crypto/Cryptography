

#include <wx/wx.h>

class MyFrame : public wxFrame {
public:
    MyFrame(const wxPoint& pos, const wxSize& size, const wxString& title);
};

MyFrame::MyFrame(const wxPoint& pos, const wxSize& size, const wxString& title) 
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    const int MARGIN = 10;

    wxPanel* top_panel = new wxPanel(this, wxID_ANY);

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

    top_panel->SetSizerAndFit(top_sizer);

    wxSizer* main_box = new wxBoxSizer(wxVERTICAL);
    main_box->Add(top_panel, 0, wxEXPAND);

    this->SetSizerAndFit(main_box);
}

class MyApp : public wxApp {
public:
    bool OnInit();
};

bool MyApp::OnInit() {
    MyFrame* frame = new MyFrame(wxDefaultPosition, wxDefaultSize, "Hello, wxWidgets");
    frame->Show(true);
    return true;
}

wxIMPLEMENT_APP(MyApp);
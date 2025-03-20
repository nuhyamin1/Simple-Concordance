#include <wx/wx.h>
#include <wx/filedlg.h>
#include <wx/textctrl.h>
#include <wx/notebook.h>
#include <wx/stattext.h>
#include <wx/sizer.h>
#include <wx/spinctrl.h>
#include "concordance.h"

class ConcordanceFrame : public wxFrame
{
public:
    ConcordanceFrame() : wxFrame(nullptr, wxID_ANY, "Concordance Tool", wxDefaultPosition, wxSize(800, 600))
    {
        // Create a notebook with tabs for different functions
        wxNotebook* notebook = new wxNotebook(this, wxID_ANY);
        
        // Create panels for each tab
        wxPanel* loadPanel = new wxPanel(notebook);
        wxPanel* kwicPanel = new wxPanel(notebook);
        wxPanel* freqPanel = new wxPanel(notebook);
        wxPanel* ngramPanel = new wxPanel(notebook);
        
        // Add panels to notebook
        notebook->AddPage(loadPanel, "Load File");
        notebook->AddPage(kwicPanel, "KWIC");
        notebook->AddPage(freqPanel, "Frequency");
        notebook->AddPage(ngramPanel, "N-grams");
        
        // Set up Load File panel
        wxBoxSizer* loadSizer = new wxBoxSizer(wxVERTICAL);
        wxStaticText* loadLabel = new wxStaticText(loadPanel, wxID_ANY, "Select a text file to analyze:");
        m_filePathText = new wxTextCtrl(loadPanel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
        wxButton* browseButton = new wxButton(loadPanel, wxID_ANY, "Browse...");
        m_loadStatusText = new wxStaticText(loadPanel, wxID_ANY, "No file loaded");
        
        loadSizer->Add(loadLabel, 0, wxALL, 10);
        loadSizer->Add(m_filePathText, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
        loadSizer->Add(browseButton, 0, wxALL, 10);
        loadSizer->Add(m_loadStatusText, 0, wxALL, 10);
        loadPanel->SetSizer(loadSizer);
        
        // Set up KWIC panel
        wxBoxSizer* kwicSizer = new wxBoxSizer(wxVERTICAL);
        wxBoxSizer* kwicInputSizer = new wxBoxSizer(wxHORIZONTAL);
        
        wxStaticText* kwicWordLabel = new wxStaticText(kwicPanel, wxID_ANY, "Word to search:");
        m_kwicWordText = new wxTextCtrl(kwicPanel, wxID_ANY);
        wxStaticText* kwicContextLabel = new wxStaticText(kwicPanel, wxID_ANY, "Context size:");
        m_kwicContextSpin = new wxSpinCtrl(kwicPanel, wxID_ANY, "5", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 20, 5);
        wxButton* kwicSearchButton = new wxButton(kwicPanel, wxID_ANY, "Search");
        
        kwicInputSizer->Add(kwicWordLabel, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
        kwicInputSizer->Add(m_kwicWordText, 1, wxRIGHT, 10);
        kwicInputSizer->Add(kwicContextLabel, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
        kwicInputSizer->Add(m_kwicContextSpin, 0, wxRIGHT, 10);
        kwicInputSizer->Add(kwicSearchButton, 0);
        
        m_kwicResultsText = new wxTextCtrl(kwicPanel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY);
        
        kwicSizer->Add(kwicInputSizer, 0, wxEXPAND | wxALL, 10);
        kwicSizer->Add(m_kwicResultsText, 1, wxEXPAND | wxALL, 10);
        kwicPanel->SetSizer(kwicSizer);
        
        // Set up Frequency panel
        wxBoxSizer* freqSizer = new wxBoxSizer(wxVERTICAL);
        wxBoxSizer* freqInputSizer = new wxBoxSizer(wxHORIZONTAL);
        
        wxStaticText* freqLimitLabel = new wxStaticText(freqPanel, wxID_ANY, "Limit results (0 for all):");
        m_freqLimitSpin = new wxSpinCtrl(freqPanel, wxID_ANY, "10", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 1000, 10);
        wxButton* freqAnalyzeButton = new wxButton(freqPanel, wxID_ANY, "Analyze");
        
        freqInputSizer->Add(freqLimitLabel, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
        freqInputSizer->Add(m_freqLimitSpin, 0, wxRIGHT, 10);
        freqInputSizer->Add(freqAnalyzeButton, 0);
        
        m_freqResultsText = new wxTextCtrl(freqPanel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY);
        
        freqSizer->Add(freqInputSizer, 0, wxEXPAND | wxALL, 10);
        freqSizer->Add(m_freqResultsText, 1, wxEXPAND | wxALL, 10);
        freqPanel->SetSizer(freqSizer);
        
        // Set up N-gram panel
        wxBoxSizer* ngramSizer = new wxBoxSizer(wxVERTICAL);
        wxBoxSizer* ngramInputSizer = new wxBoxSizer(wxHORIZONTAL);
        
        wxStaticText* ngramSizeLabel = new wxStaticText(ngramPanel, wxID_ANY, "N-gram size:");
        m_ngramSizeSpin = new wxSpinCtrl(ngramPanel, wxID_ANY, "2", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 2, 5, 2);
        wxButton* ngramAnalyzeButton = new wxButton(ngramPanel, wxID_ANY, "Analyze");
        
        ngramInputSizer->Add(ngramSizeLabel, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
        ngramInputSizer->Add(m_ngramSizeSpin, 0, wxRIGHT, 10);
        ngramInputSizer->Add(ngramAnalyzeButton, 0);
        
        m_ngramResultsText = new wxTextCtrl(ngramPanel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY);
        
        ngramSizer->Add(ngramInputSizer, 0, wxEXPAND | wxALL, 10);
        ngramSizer->Add(m_ngramResultsText, 1, wxEXPAND | wxALL, 10);
        ngramPanel->SetSizer(ngramSizer);
        
        // Set up main sizer
        wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
        mainSizer->Add(notebook, 1, wxEXPAND | wxALL, 10);
        SetSizer(mainSizer);
        
        // Bind events
        browseButton->Bind(wxEVT_BUTTON, &ConcordanceFrame::OnBrowse, this);
        kwicSearchButton->Bind(wxEVT_BUTTON, &ConcordanceFrame::OnKwicSearch, this);
        freqAnalyzeButton->Bind(wxEVT_BUTTON, &ConcordanceFrame::OnFreqAnalyze, this);
        ngramAnalyzeButton->Bind(wxEVT_BUTTON, &ConcordanceFrame::OnNgramAnalyze, this);
        
        // Create status bar
        CreateStatusBar();
        SetStatusText("Ready");
    }
    
private:
    ConcordanceAnalyzer m_analyzer;
    wxTextCtrl* m_filePathText;
    wxStaticText* m_loadStatusText;
    wxTextCtrl* m_kwicWordText;
    wxSpinCtrl* m_kwicContextSpin;
    wxTextCtrl* m_kwicResultsText;
    wxSpinCtrl* m_freqLimitSpin;
    wxTextCtrl* m_freqResultsText;
    wxSpinCtrl* m_ngramSizeSpin;
    wxTextCtrl* m_ngramResultsText;
    
    void OnBrowse(wxCommandEvent& event)
    {
        wxFileDialog openFileDialog(this, "Open Text File", "", "", "Text files (*.txt)|*.txt|All files (*.*)|*.*", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
        
        if (openFileDialog.ShowModal() == wxID_CANCEL)
            return;
        
        wxString filePath = openFileDialog.GetPath();
        m_filePathText->SetValue(filePath);
        
        try {
            m_analyzer.loadFile(filePath.ToStdString());
            m_loadStatusText->SetLabel("File loaded successfully");
            SetStatusText("File loaded: " + filePath);
        }
        catch (const std::exception& e) {
            m_loadStatusText->SetLabel("Error loading file: " + wxString(e.what()));
            SetStatusText("Error loading file");
        }
    }
    
    void OnKwicSearch(wxCommandEvent& event)
    {
        wxString word = m_kwicWordText->GetValue();
        if (word.IsEmpty()) {
            wxMessageBox("Please enter a word to search for", "Input Error", wxICON_ERROR);
            return;
        }
        
        int context = m_kwicContextSpin->GetValue();
        
        try {
            auto results = m_analyzer.getKeywordInContext(word.ToStdString(), context);
            
            m_kwicResultsText->Clear();
            if (results.empty()) {
                m_kwicResultsText->AppendText("No occurrences found for '" + word + "'");
            }
            else {
                for (const auto& result : results) {
                    m_kwicResultsText->AppendText(wxString(result) + "\n\n");
                }
            }
            
            SetStatusText("KWIC search completed for '" + word + "'");
        }
        catch (const std::exception& e) {
            wxMessageBox(wxString(e.what()), "Error", wxICON_ERROR);
            SetStatusText("Error in KWIC search");
        }
    }
    
    void OnFreqAnalyze(wxCommandEvent& event)
    {
        int limit = m_freqLimitSpin->GetValue();
        
        try {
            auto results = m_analyzer.getWordFrequencies(limit);
            
            m_freqResultsText->Clear();
            m_freqResultsText->AppendText("WORD                FREQUENCY\n\n");
            
            for (const auto& [word, freq] : results) {
                wxString line = wxString(word);
                while (line.Length() < 20) line += " ";
                line += wxString::Format("%d", freq);
                m_freqResultsText->AppendText(line + "\n");
            }
            
            SetStatusText("Frequency analysis completed");
        }
        catch (const std::exception& e) {
            wxMessageBox(wxString(e.what()), "Error", wxICON_ERROR);
            SetStatusText("Error in frequency analysis");
        }
    }
    
    void OnNgramAnalyze(wxCommandEvent& event)
    {
        int n = m_ngramSizeSpin->GetValue();
        
        try {
            auto results = m_analyzer.getNGrams(n);
            
            m_ngramResultsText->Clear();
            m_ngramResultsText->AppendText(wxString::Format("%d-GRAM                         FREQUENCY\n\n", n));
            
            for (const auto& [ngram, freq] : results) {
                wxString line = wxString(ngram);
                while (line.Length() < 30) line += " ";
                line += wxString::Format("%d", freq);
                m_ngramResultsText->AppendText(line + "\n");
            }
            
            SetStatusText("N-gram analysis completed");
        }
        catch (const std::exception& e) {
            wxMessageBox(wxString(e.what()), "Error", wxICON_ERROR);
            SetStatusText("Error in n-gram analysis");
        }
    }
};

class ConcordanceApp : public wxApp
{
public:
    bool OnInit() override
    {
        ConcordanceFrame* frame = new ConcordanceFrame();
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(ConcordanceApp);
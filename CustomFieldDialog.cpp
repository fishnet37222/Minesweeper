// Copyright (c) 2026 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

#include "CustomFieldDialog.h"
#include <wx/gbsizer.h>

CustomFieldDialog::CustomFieldDialog(wxWindow* parent, const wxSize& customFieldSize, int customMineCount) : wxDialog(parent, wxID_ANY, "Custom Field"), m_customFieldSize(customFieldSize), m_customMineCount(customMineCount)
{
	wxDialog::SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_FRAMEBK));
	m_customFieldSize = customFieldSize;
	m_customMineCount = customMineCount;

	auto* szrMainOuter = new wxBoxSizer(wxHORIZONTAL);
	szrMainOuter->AddSpacer(10);
	auto* szrMainInner = new wxBoxSizer(wxVERTICAL);
	szrMainInner->AddSpacer(10);
	auto* szrMain = new wxGridBagSizer(5, 5);
	szrMain->Add(new wxStaticText(this, wxID_ANY, "Width:"), wxGBPosition(0, 0), wxDefaultSpan, wxALIGN_CENTER_VERTICAL);
	m_txtWidth = new wxTextCtrl(this, wxID_ANY, std::to_string(customFieldSize.x), wxDefaultPosition, wxDefaultSize, wxTE_RIGHT);
	szrMain->Add(m_txtWidth, wxGBPosition(0, 1), wxDefaultSpan, wxSizerFlags(1).CenterVertical().GetFlags());
	szrMain->Add(new wxStaticText(this, wxID_ANY, "Height:"), wxGBPosition(1, 0), wxDefaultSpan, wxALIGN_CENTER_VERTICAL);
	m_txtHeight = new wxTextCtrl(this, wxID_ANY, std::to_string(customFieldSize.y), wxDefaultPosition, wxDefaultSize, wxTE_RIGHT);
	szrMain->Add(m_txtHeight, wxGBPosition(1, 1), wxDefaultSpan, wxSizerFlags(1).CenterVertical().GetFlags());
	szrMain->Add(new wxStaticText(this, wxID_ANY, "Mines:"), wxGBPosition(2, 0), wxDefaultSpan, wxALIGN_CENTER_VERTICAL);
	m_txtMineCount = new wxTextCtrl(this, wxID_ANY, std::to_string(customMineCount), wxDefaultPosition, wxDefaultSize, wxTE_RIGHT);
	szrMain->Add(m_txtMineCount, wxGBPosition(2, 1), wxDefaultSpan, wxSizerFlags(1).CenterVertical().GetFlags());
	szrMainInner->Add(szrMain, wxSizerFlags(1).Expand());
	szrMainInner->AddSpacer(5);
	auto* szrButtons = new wxBoxSizer(wxHORIZONTAL);
	szrButtons->AddStretchSpacer(1);
	m_btnOK = new wxButton(this, wxID_OK, "OK");
	m_btnOK->Bind(wxEVT_BUTTON, &CustomFieldDialog::BtnOK_OnClick, this);
	szrButtons->Add(m_btnOK, wxSizerFlags(0).CenterVertical());
	szrButtons->AddSpacer(5);
	m_btnCancel = new wxButton(this, wxID_CANCEL, "Cancel");
	szrButtons->Add(m_btnCancel, wxSizerFlags(0).CenterVertical());
	szrMainInner->Add(szrButtons, wxSizerFlags(0).Expand());
	szrMainInner->AddSpacer(10);
	szrMainOuter->Add(szrMainInner, wxSizerFlags(1).Expand());
	szrMainOuter->AddSpacer(10);
	SetSizerAndFit(szrMainOuter);

	CenterOnParent();
}

void CustomFieldDialog::BtnOK_OnClick(wxCommandEvent& event)
{
	try
	{
		m_customFieldSize.x = std::stoi(m_txtWidth->GetValue().ToStdString());
		m_customFieldSize.y = std::stoi(m_txtHeight->GetValue().ToStdString());
		m_customMineCount = std::stoi(m_txtMineCount->GetValue().ToStdString());
	}
	catch (const std::exception&)
	{
		wxMessageBox("Please enter valid numbers.", "Invalid Input", wxICON_ERROR | wxOK);
		return;
	}

	event.Skip();
}

// Copyright (c) 2025 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

#include "pch.h"
#include "CustomFieldDialog.h"
#include <wx/gbsizer.h>

CustomFieldDialog::CustomFieldDialog(wxWindow* parent, const int fieldWidth, const int fieldHeight, const int mineCount) : wxDialog(parent, wxID_ANY, "Custom Minefield")
{
	wxDialog::SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_FRAMEBK));

	auto* szrMainOuter = new wxBoxSizer(wxHORIZONTAL);
	szrMainOuter->AddSpacer(12);
	auto* szrMainInner = new wxBoxSizer(wxVERTICAL);
	szrMainInner->AddSpacer(12);

	auto* szrFields = new wxGridBagSizer(5, 5);
	szrFields->Add(new wxStaticText(this, wxID_ANY, "Custom Field Width"), wxGBPosition(0, 0));
	m_txtFieldWidth = new wxTextCtrl(this, wxID_ANY, std::to_string(fieldWidth), wxDefaultPosition, wxDefaultSize, wxTE_RIGHT);
	szrFields->Add(m_txtFieldWidth, wxGBPosition(0, 1), wxDefaultSpan, wxSizerFlags().Expand().GetFlags());

	szrFields->Add(new wxStaticText(this, wxID_ANY, "Custom Field Height"), wxGBPosition(1, 0));
	m_txtFieldHeight = new wxTextCtrl(this, wxID_ANY, std::to_string(fieldHeight), wxDefaultPosition, wxDefaultSize, wxTE_RIGHT);
	szrFields->Add(m_txtFieldHeight, wxGBPosition(1, 1), wxDefaultSpan, wxSizerFlags().Expand().GetFlags());

	szrFields->Add(new wxStaticText(this, wxID_ANY, "Custom Mine Count"), wxGBPosition(2, 0));
	m_txtMineCount = new wxTextCtrl(this, wxID_ANY, std::to_string(mineCount), wxDefaultPosition, wxDefaultSize, wxTE_RIGHT);
	szrFields->Add(m_txtMineCount, wxGBPosition(2, 1), wxDefaultSpan, wxSizerFlags().Expand().GetFlags());
	szrFields->AddGrowableCol(1, 1);
	szrMainInner->Add(szrFields, wxSizerFlags(1).Expand());

	szrMainInner->AddSpacer(5);

	auto* szrButtons = new wxBoxSizer(wxHORIZONTAL);
	szrButtons->AddStretchSpacer(1);

	auto* szrButtonsRight = new wxGridSizer(1, 2, 5, 5);
	m_btnOk = new wxButton(this, wxID_OK);
	m_btnOk->Bind(wxEVT_BUTTON, &CustomFieldDialog::BtnOk_OnClick, this);
	szrButtonsRight->Add(m_btnOk, wxSizerFlags(0));
	m_btnCancel = new wxButton(this, wxID_CANCEL);
	szrButtonsRight->Add(m_btnCancel, wxSizerFlags(0));
	szrButtons->Add(szrButtonsRight, wxSizerFlags(0));

	szrMainInner->Add(szrButtons, wxSizerFlags(0).Expand());

	szrMainInner->AddSpacer(12);
	szrMainOuter->Add(szrMainInner, wxSizerFlags(1).Expand());
	szrMainOuter->AddSpacer(12);
	SetSizerAndFit(szrMainOuter);

	CenterOnParent();
}

void CustomFieldDialog::BtnOk_OnClick(wxCommandEvent& event)
{
	m_fieldWidth = std::stoi(m_txtFieldWidth->GetValue().ToStdString());
	m_fieldHeight = std::stoi(m_txtFieldHeight->GetValue().ToStdString());
	m_mineCount = std::stoi(m_txtMineCount->GetValue().ToStdString());

	event.Skip();
}

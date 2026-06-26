// Copyright (c) 2026 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

#include "pch.h"
#include "AboutDialog.h"
#include "LICENSE-2.0-text.h"
#include <wx/hyperlink.h>

AboutDialog::AboutDialog(wxWindow* parent)
{
	wxDialog::SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_FRAMEBK));
	Create(parent, wxID_ANY, "About Minesweeper", wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE);

	auto* szrMainOuter = new wxBoxSizer(wxHORIZONTAL);
	szrMainOuter->AddSpacer(10);
	auto* szrMainInner = new wxBoxSizer(wxVERTICAL);
	szrMainInner->Add(new wxStaticText(this, wxID_ANY, "Minesweeper Version 1.0.1"), wxSizerFlags(0).CenterHorizontal());
	szrMainInner->Add(new wxStaticText(this, wxID_ANY, "Copyright \u00a9 2026 David A. Frischknecht"), wxSizerFlags(0).CenterHorizontal());
	szrMainInner->Add(new wxHyperlinkCtrl(this, wxID_ANY, "Licensed under the Apache License, Version 2.0", "https://www.apache.org/licenses/LICENSE-2.0"), wxSizerFlags(0).CenterHorizontal());
	szrMainInner->Add(new wxHyperlinkCtrl(this, wxID_ANY, "Source Code on GitHub", "https://github.com/fishnet37222/Minesweeper"), wxSizerFlags(0).CenterHorizontal());
	szrMainInner->AddSpacer(5);
	m_txtLicense = new wxTextCtrl(this, wxID_ANY, license_txt, wxDefaultPosition, wxSize(650, 400), wxTE_MULTILINE | wxTE_READONLY);
	m_txtLicense->SetFont(wxFontInfo(10).Family(wxFONTFAMILY_TELETYPE));
	szrMainInner->Add(m_txtLicense, wxSizerFlags(1).Expand());
	szrMainInner->AddSpacer(5);
	auto* szrBottom = new wxBoxSizer(wxHORIZONTAL);
	szrBottom->AddStretchSpacer(1);
	m_btnClose = new wxButton(this, wxID_OK, "Close");
	szrBottom->Add(m_btnClose, wxSizerFlags(0).CenterVertical());
	szrMainInner->Add(szrBottom, wxSizerFlags(0).Expand());
	szrMainInner->AddSpacer(10);
	szrMainOuter->Add(szrMainInner, wxSizerFlags(1).Expand());
	szrMainOuter->AddSpacer(10);
	SetSizerAndFit(szrMainOuter);
	SetAffirmativeId(wxID_OK);
	AddMainButtonId(wxID_OK);
	SetEscapeId(wxID_OK);

	CenterOnParent();
}

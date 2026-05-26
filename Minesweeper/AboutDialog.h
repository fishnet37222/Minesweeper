// Copyright (c) 2026 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

#pragma once
#include <wx/hyperlink.h>
#include <wx/wx.h>

class AboutDialog final : public wxDialog
{
public:
	explicit AboutDialog(wxWindow* parent);

private:
	wxTextCtrl* m_txtLicense{};
	wxHyperlinkCtrl* m_lnkSourceCode{};
	wxButton* m_btnClose{};
};

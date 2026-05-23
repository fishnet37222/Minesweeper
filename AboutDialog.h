// Copyright (c) 2026 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

#pragma once
#include <wx/hyperlink.h>
#include <wx/webview.h>
#include <wx/wx.h>

class AboutDialog final : public wxDialog
{
public:
	explicit AboutDialog(wxWindow* parent);

private:
	wxWebView* m_wvLicense{};
	wxHyperlinkCtrl* m_lnkSourceCode{};

	void WvLicense_OnNavigating(wxWebViewEvent& event);
};

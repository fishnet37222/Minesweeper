// Copyright (c) 2023 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

#pragma once
#include <wx/wx.h>
#include <wx/webview.h>

class AboutDialog final : public wxDialog
{
public:
	explicit AboutDialog(wxWindow* parent);

private:
	wxWebView* webView{};

	void InitUi();
	void WebView_OnNavigating(wxWebViewEvent& event);
};

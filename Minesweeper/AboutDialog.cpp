// Copyright (c) 2023 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

#include "pch.h"
#include "AboutDialog.h"
#include "LICENSE-2.0-html.h"
#include <wx/hyperlink.h>

AboutDialog::AboutDialog(wxWindow* parent) : wxDialog(parent, wxID_ANY, L"About Minesweeper")
{
	this->InitUi();
}

void AboutDialog::InitUi()
{
	this->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_FRAMEBK));

	auto* szrMainOuter = new wxBoxSizer(wxHORIZONTAL);
	szrMainOuter->AddSpacer(12);
	auto* szrMainInner = new wxBoxSizer(wxVERTICAL);
	szrMainInner->AddSpacer(12);
	szrMainInner->Add(new wxStaticText(this, wxID_ANY, L"Minesweeper 1.0.0"), wxSizerFlags(0).CenterHorizontal());
	szrMainInner->AddSpacer(5);
	szrMainInner->Add(new wxStaticText(this, wxID_ANY, L"Copyright \u00A9 2023, David Frischknecht"), wxSizerFlags(0).CenterHorizontal());
	szrMainInner->AddSpacer(5);
	szrMainInner->Add(new wxStaticText(this, wxID_ANY, L"Licensed under the Apache License, Version 2.0"), wxSizerFlags(0).CenterHorizontal());
	szrMainInner->AddSpacer(5);
	szrMainInner->Add(new wxHyperlinkCtrl(this, wxID_ANY, L"This application uses the wxWidgets UI library.", "https://www.wxwidgets.org/"), wxSizerFlags(0).CenterHorizontal());
	szrMainInner->AddSpacer(5);
	szrMainInner->Add(new wxHyperlinkCtrl(this, wxID_ANY, L"This application uses WebView2 from Microsoft\u00AE.", "https://developer.microsoft.com/en-us/microsoft-edge/webview2/"), wxSizerFlags(0).CenterHorizontal());
	szrMainInner->AddSpacer(5);
	this->webView = wxWebView::New(this, wxID_ANY);
	this->webView->SetMaxSize(wxSize(600, 400));
	this->webView->SetMinSize(wxSize(600, 400));
	this->webView->SetPage(license_html, wxEmptyString);
	this->webView->Bind(wxEVT_WEBVIEW_NAVIGATING, &AboutDialog::WebView_OnNavigating, this);
	szrMainInner->Add(this->webView, wxSizerFlags(1).Expand());
	szrMainInner->AddSpacer(5);
	auto* szrButtons = new wxBoxSizer(wxHORIZONTAL);
	szrButtons->AddStretchSpacer(1);
	auto* btnClose = new wxButton(this, wxID_CLOSE, L"Close");
	szrButtons->Add(btnClose, wxSizerFlags(0).CenterVertical());
	this->SetAffirmativeId(wxID_CLOSE);
	szrMainInner->Add(szrButtons, wxSizerFlags(0).Expand());
	szrMainInner->AddSpacer(12);
	szrMainOuter->Add(szrMainInner, wxSizerFlags(1).Expand());
	szrMainOuter->AddSpacer(12);
	this->SetSizerAndFit(szrMainOuter);

	this->CenterOnParent();
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void AboutDialog::WebView_OnNavigating(wxWebViewEvent& event)
{
	if (event.GetURL().starts_with("data:"))
	{
		event.Skip();
		return;
	}

	wxLaunchDefaultBrowser(event.GetURL());
	event.Veto();
}

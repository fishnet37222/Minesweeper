// Copyright (c) 2023 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

#include "pch.h"
#include "App.h"
#include "MainWindow.h"

#pragma warning(suppress : 28251)
wxIMPLEMENT_APP(App);

bool App::OnInit()
{
	if (!wxApp::OnInit())
		return false;

	auto* win = new MainWindow();
	this->SetTopWindow(win);
	win->Show();

	return true;
}

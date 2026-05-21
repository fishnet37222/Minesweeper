// Copyright (c) 2026 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

#include "MainWindow.h"

#ifdef __linux__
#include "bitmaps/bomb128.xpm"
#include "bitmaps/bomb16.xpm"
#include "bitmaps/bomb256.xpm"
#include "bitmaps/bomb32.xpm"
#include "bitmaps/bomb64.xpm"
#endif

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Minesweeper", wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
	wxFrame::SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_FRAMEBK));

	wxIconBundle icons;

#ifdef _WINDOWS
	icons = wxIconBundle("APP_ICON", nullptr);
#elif defined(__linux__)
	icons.AddIcon(wxIcon(bomb16_xpm));
	icons.AddIcon(wxIcon(bomb32_xpm));
	icons.AddIcon(wxIcon(bomb64_xpm));
	icons.AddIcon(wxIcon(bomb128_xpm));
	icons.AddIcon(wxIcon(bomb256_xpm));
#endif
	
	wxFrame::SetIcons(icons);

	CenterOnScreen();
}

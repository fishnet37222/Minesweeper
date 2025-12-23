// Copyright (c) 2025 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

#include "MainWindow.h"

#ifdef __linux__
#include "bitmaps/bomb16.xpm"
#include "bitmaps/bomb32.xpm"
#include "bitmaps/bomb64.xpm"
#include "bitmaps/bomb128.xpm"
#include "bitmaps/bomb256.xpm"
#endif

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Minesweeper", wxDefaultPosition, wxDefaultSize,
	wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
	wxFrame::SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_FRAMEBK));

#ifdef _WINDOWS
	const wxIconBundle icons("APP_ICON", nullptr);
#elif defined(__linux__)
	wxIconBundle icons;
	icons.AddIcon(wxIcon(bomb_16_xpm));
	icons.AddIcon(wxIcon(bomb_32_xpm));
	icons.AddIcon(wxIcon(bomb_64_xpm));
	icons.AddIcon(wxIcon(bomb_128_xpm));
	icons.AddIcon(wxIcon(bomb_256_xpm));
#endif

	wxFrame::SetIcons(icons);
}

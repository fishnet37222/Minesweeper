// Copyright (c) 2025 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

#include "pch.h"
#include "MainWindow.h"
#include "App.h"
#include <wx/config.h>
#include "CustomFieldDialog.h"

enum MenuId : uint16_t
{
	ID_GAME_NEW = wxID_HIGHEST + 1,
	ID_GAME_BEGINNER,
	ID_GAME_INTERMEDIATE,
	ID_GAME_EXPERT,
	ID_GAME_CUSTOM,
	ID_GAME_BEST_TIMES,
	ID_GAME_EXIT,
	ID_HELP_HOW_TO_PLAY,
	ID_HELP_ABOUT
};

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, wxGetApp().GetAppName(), wxDefaultPosition, wxDefaultSize,
	wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
	m_difficultyMenuIds = { ID_GAME_BEGINNER, ID_GAME_INTERMEDIATE, ID_GAME_EXPERT, ID_GAME_CUSTOM };

	wxFrame::SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_FRAMEBK));

	wxFrame::SetIcons(wxIconBundle("APP_ICON", nullptr));

	const auto config = wxConfig::Get();
	m_difficultyLevel = static_cast<uint16_t>(config->ReadLong("DifficultyLevel", ID_GAME_BEGINNER));
	m_customMineFieldSize.SetWidth(config->ReadLong("CustomMineFieldWidth", 9));
	m_customMineFieldSize.SetHeight(config->ReadLong("CustomMineFieldHeight", 9));
	m_customMineCount = config->ReadLong("CustomMineCount", 10);

	m_menuBar = new wxMenuBar();

	auto* mnuGame = new wxMenu();
	mnuGame->Append(ID_GAME_NEW, "&New\tF2");
	mnuGame->AppendSeparator();
	mnuGame->AppendCheckItem(ID_GAME_BEGINNER, "&Beginner");
	mnuGame->AppendCheckItem(ID_GAME_INTERMEDIATE, "&Intermediate");
	mnuGame->AppendCheckItem(ID_GAME_EXPERT, "&Expert");
	mnuGame->AppendCheckItem(ID_GAME_CUSTOM, "&Custom...");
	mnuGame->AppendSeparator();
	mnuGame->Append(ID_GAME_BEST_TIMES, "Best &Times...");
	mnuGame->AppendSeparator();
	mnuGame->Append(ID_GAME_EXIT, "E&xit");
	m_menuBar->Append(mnuGame, "&Game");

	auto* mnuHelp = new wxMenu();
	mnuHelp->Append(ID_HELP_HOW_TO_PLAY, "How to &Play...");
	mnuHelp->AppendSeparator();
	mnuHelp->Append(ID_HELP_ABOUT, "About Minesweeper...");
	m_menuBar->Append(mnuHelp, "&Help");
	m_menuBar->FindItem(m_difficultyLevel)->Check(true);

	m_menuBar->Bind(wxEVT_MENU, &MainWindow::MenuBar_OnItemSelect, this);

	wxFrame::SetMenuBar(m_menuBar);

	Bind(wxEVT_CLOSE_WINDOW, &MainWindow::MainWindow_OnClose, this);

	const auto posX = config->ReadLong("MainWindowPosX", -1);
	// ReSharper disable once CppTooWideScopeInitStatement
	const auto posY = config->ReadLong("MainWindowPosY", -1);

	if (posX == -1 && posY == -1)
	{
		CenterOnScreen();
	}
	else
	{
		SetPosition({ posX, posY });
	}
}

// ReSharper disable once CppMemberFunctionMayBeConst
void MainWindow::MainWindow_OnClose(wxCloseEvent& event)
{
	const auto config = wxConfig::Get();
	config->Write("MainWindowPosX", GetPosition().x);
	config->Write("MainWindowPosY", GetPosition().y);
	config->Write("DifficultyLevel", m_difficultyLevel);
	config->Write("CustomMineFieldWidth", m_customMineFieldSize.GetWidth());
	config->Write("CustomMineFieldHeight", m_customMineFieldSize.GetHeight());
	config->Write("CustomMineCount", m_customMineCount);

	event.Skip();
}

// ReSharper disable once CppParameterMayBeConstPtrOrRef
void MainWindow::MenuBar_OnItemSelect(wxCommandEvent& event)
{
	switch (event.GetId())
	{
		case ID_GAME_EXIT:
		{
			Close();

			break;
		}

		case ID_GAME_BEGINNER:
		case ID_GAME_INTERMEDIATE:
		case ID_GAME_EXPERT:
		case ID_GAME_CUSTOM:
		{
			if (event.GetId() == ID_GAME_CUSTOM)
			{
				CustomFieldDialog dlg(this, m_customMineFieldSize.GetWidth(), m_customMineFieldSize.GetHeight(), m_customMineCount);

				if (const auto result = dlg.ShowModal(); result == wxID_CANCEL)
				{
					for (const auto id : m_difficultyMenuIds)
					{
						if (id == m_difficultyLevel)
						{
							m_menuBar->FindItem(id)->Check(true);
						}
						else
						{
							m_menuBar->FindItem(id)->Check(false);
						}
					}

					break;
				}

				m_customMineCount = dlg.GetMineCount();
				m_customMineFieldSize.SetWidth(dlg.GetFieldWidth());
				m_customMineFieldSize.SetHeight(dlg.GetFieldHeight());
			}

			m_difficultyLevel = static_cast<uint16_t>(event.GetId());

			for (const auto id : m_difficultyMenuIds)
			{
				if (id == m_difficultyLevel)
				{
					m_menuBar->FindItem(id)->Check(true);
				}
				else
				{
					m_menuBar->FindItem(id)->Check(false);
				}
			}

			break;
		}

		default:
			break;
	}
}

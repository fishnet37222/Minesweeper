// Copyright (c) 2026 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

#include "pch.h"
#include "AboutDialog.h"
#include "CustomFieldDialog.h"
#include "MainWindow.h"
#include <wx/config.h>
#include <fstream>

#include "bitmaps/smile-1.xpm"
#include "bitmaps/smile-2.xpm"
#include "bitmaps/smile-3.xpm"
#include "bitmaps/smile-4.xpm"

enum : uint16_t
{
	ID_GAME_NEW = wxID_HIGHEST + 1,
	ID_GAME_BEGINNER,
	ID_GAME_INTERMEDIATE,
	ID_GAME_EXPERT,
	ID_GAME_CUSTOM,
	ID_GAME_BEST_TIMES,
	ID_GAME_EXIT,
	ID_HELP_ABOUT
};

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Minesweeper", wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
	m_bestTimesFilePath = wxStandardPaths::Get().GetUserDataDir().ToStdString() + "/best_times.json";

	wxFrame::SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_FRAMEBK));

	wxFrame::SetIcons(wxIconBundle("APP_ICON", nullptr));

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
	mnuHelp->Append(ID_HELP_ABOUT, "&About Minesweeper");
	m_menuBar->Append(mnuHelp, "&Help");
	wxFrame::SetMenuBar(m_menuBar);
	m_menuBar->Bind(wxEVT_MENU, &MainWindow::MenuBar_OnItemSelect, this);

	auto* szrMainOuter = new wxBoxSizer(wxHORIZONTAL);
	szrMainOuter->AddSpacer(10);
	auto* szrMainInner = new wxBoxSizer(wxVERTICAL);
	szrMainInner->AddSpacer(5);
	auto* szrTop = new wxBoxSizer(wxHORIZONTAL);
	m_ssdUnflaggedMineCount = new SevenSegmentDisplay(this);
	m_ssdUnflaggedMineCount->SetValue(10);
	szrTop->Add(m_ssdUnflaggedMineCount, wxSizerFlags(0).CenterVertical());
	szrTop->AddStretchSpacer(1);
	szrTop->AddSpacer(5);
	m_btnNewGame = new wxBitmapButton(this, wxID_ANY, wxBitmap(smile_1_xpm));
	m_btnNewGame->Bind(wxEVT_BUTTON, &MainWindow::BtnNewGame_OnClick, this);
	szrTop->Add(m_btnNewGame, wxSizerFlags(0).CenterVertical());
	szrTop->AddSpacer(5);
	szrTop->AddStretchSpacer(1);
	m_ssdElapsedSeconds = new SevenSegmentDisplay(this);
	szrTop->Add(m_ssdElapsedSeconds, wxSizerFlags(0).CenterVertical());
	szrMainInner->Add(szrTop, wxSizerFlags(0).Expand());
	szrMainInner->AddSpacer(5);
	m_mineField = new MineField(this);
	m_mineField->Bind(wxEVT_LEFT_DOWN, &MainWindow::MineField_OnLeftDown, this);
	m_mineField->Bind(wxEVT_LEFT_UP, &MainWindow::MineField_OnLeftUp, this);
	m_mineField->Bind(MINEFIELD_CELL_FLAG_TOGGLED, &MainWindow::MineField_OnCellFlagToggled, this);
	m_mineField->Bind(MINEFIELD_FIRST_CELL_CLICKED, &MainWindow::MineField_OnFirstCellClicked, this);
	m_mineField->Bind(MINEFIELD_GAME_OVER, &MainWindow::MineField_OnGameOver, this);
	szrMainInner->Add(m_mineField, wxSizerFlags(1).CenterHorizontal());
	szrMainInner->AddSpacer(10);
	szrMainOuter->Add(szrMainInner, wxSizerFlags(1).Expand());
	szrMainOuter->AddSpacer(10);
	SetSizerAndFit(szrMainOuter);

	if (std::filesystem::exists(m_bestTimesFilePath))
	{
		std::ifstream bestTimesFile(m_bestTimesFilePath);
		bestTimesFile >> m_bestTimes;
		bestTimesFile.close();
	}

	const auto savedPositionX = static_cast<int>(wxConfig::Get()->ReadLong("MainWindowPositionX", -1));
	// ReSharper disable once CppTooWideScopeInitStatement
	const auto savedPositionY = static_cast<int>(wxConfig::Get()->ReadLong("MainWindowPositionY", -1));

	if (savedPositionX != -1 && savedPositionY != -1)
	{
		SetPosition(wxPoint(savedPositionX, savedPositionY));
	}
	else
	{
		CenterOnScreen();
	}

	Bind(wxEVT_CLOSE_WINDOW, &MainWindow::MainWindow_OnClose, this);
	m_timer.Bind(wxEVT_TIMER, &MainWindow::Timer_OnTick, this);

	m_customMineCount = static_cast<int>(wxConfig::Get()->ReadLong("CustomMineCount", 40));
	m_customFieldSize.x = static_cast<int>(wxConfig::Get()->ReadLong("CustomFieldWidth", 16));
	m_customFieldSize.y = static_cast<int>(wxConfig::Get()->ReadLong("CustomFieldHeight", 16));

	m_difficulty = static_cast<GameDifficulty>(wxConfig::Get()->ReadLong("GameDifficulty", BEGINNER));
	switch (m_difficulty)
	{
		case BEGINNER:
		{
			auto* item = m_menuBar->FindItem(ID_GAME_BEGINNER);
			item->Check();
			m_difficultyName = "Beginner";
			break;
		}

		case INTERMEDIATE:
		{
			auto* item = m_menuBar->FindItem(ID_GAME_INTERMEDIATE);
			item->Check();
			m_difficultyName = "Intermediate";
			break;
		}

		case EXPERT:
		{
			auto* item = m_menuBar->FindItem(ID_GAME_EXPERT);
			item->Check();
			m_difficultyName = "Expert";
			break;
		}

		case CUSTOM:
		{
			auto* item = m_menuBar->FindItem(ID_GAME_CUSTOM);
			item->Check();
			m_difficultyName = "Custom";
			break;
		}
	}
	StartNewGame();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void MainWindow::MainWindow_OnClose(wxCloseEvent& event)
{
	const auto position = GetPosition();
	wxConfig::Get()->Write("MainWindowPositionX", position.x);
	wxConfig::Get()->Write("MainWindowPositionY", position.y);
	wxConfig::Get()->Write("GameDifficulty", static_cast<int>(m_difficulty));
	wxConfig::Get()->Write("CustomFieldWidth", m_customFieldSize.x);
	wxConfig::Get()->Write("CustomFieldHeight", m_customFieldSize.y);
	wxConfig::Get()->Write("CustomMineCount", m_customMineCount);
	wxConfig::Get()->Flush();

	if (!std::filesystem::exists(m_bestTimesFilePath.parent_path()))
	{
		std::filesystem::create_directories(m_bestTimesFilePath.parent_path());
	}

	std::ofstream bestTimesFile(m_bestTimesFilePath);
	bestTimesFile << m_bestTimes.toStyledString();
	bestTimesFile.close();

	event.Skip();
}

// ReSharper disable once CppParameterMayBeConstPtrOrRef
void MainWindow::MenuBar_OnItemSelect([[maybe_unused]] wxCommandEvent& event)
{
	switch (event.GetId())
	{
		case ID_GAME_NEW:
		{
			StartNewGame();
			break;
		}

		case ID_GAME_BEGINNER:
		{
			if (m_difficulty == BEGINNER)
			{
				return;
			}

			m_menuBar->FindItem(static_cast<int>(ID_GAME_BEGINNER) + static_cast<int>(m_difficulty))->Check(false);

			m_difficulty = BEGINNER;
			m_difficultyName = "Beginner";
			StartNewGame();
			m_menuBar->FindItem(ID_GAME_BEGINNER)->Check(true);

			break;
		}

		case ID_GAME_INTERMEDIATE:
		{
			if (m_difficulty == INTERMEDIATE)
			{
				return;
			}

			m_menuBar->FindItem(static_cast<int>(ID_GAME_BEGINNER) + static_cast<int>(m_difficulty))->Check(false);

			m_difficulty = INTERMEDIATE;
			m_difficultyName = "Intermediate";
			StartNewGame();
			m_menuBar->FindItem(ID_GAME_INTERMEDIATE)->Check(true);

			break;
		}

		case ID_GAME_EXPERT:
		{
			if (m_difficulty == EXPERT)
			{
				return;
			}

			m_menuBar->FindItem(static_cast<int>(ID_GAME_BEGINNER) + static_cast<int>(m_difficulty))->Check(false);

			m_difficulty = EXPERT;
			m_difficultyName = "Expert";
			StartNewGame();
			m_menuBar->FindItem(ID_GAME_EXPERT)->Check(true);

			break;
		}

		case ID_GAME_CUSTOM:
		{
			const auto previousDifficulty = m_difficulty;
			CustomFieldDialog dlg(this, m_mineField->GetFieldSize(), m_mineField->GetMineCount());
			if (const auto result = dlg.ShowModal(); result == wxID_OK)
			{
				m_customFieldSize = dlg.GetCustomFieldSize();
				m_customMineCount = dlg.GetCustomMineCount();
				m_difficulty = CUSTOM;
				m_difficultyName = "Custom";
				switch (previousDifficulty)
				{
					case BEGINNER:
						m_menuBar->FindItem(ID_GAME_BEGINNER)->Check(false);
						break;
					case INTERMEDIATE:
						m_menuBar->FindItem(ID_GAME_INTERMEDIATE)->Check(false);
						break;
					case EXPERT:
						m_menuBar->FindItem(ID_GAME_EXPERT)->Check(false);
						break;
					case CUSTOM:
						m_menuBar->FindItem(ID_GAME_CUSTOM)->Check(false);
						break;
				}
				StartNewGame();
			}
			else
			{
				m_menuBar->FindItem(ID_GAME_CUSTOM)->Check(previousDifficulty == CUSTOM);
				switch (previousDifficulty)
				{
					case BEGINNER:
						m_menuBar->FindItem(ID_GAME_BEGINNER)->Check(true);
						break;
					case INTERMEDIATE:
						m_menuBar->FindItem(ID_GAME_INTERMEDIATE)->Check(true);
						break;
					case EXPERT:
						m_menuBar->FindItem(ID_GAME_EXPERT)->Check(true);
						break;
					case CUSTOM:
						m_menuBar->FindItem(ID_GAME_CUSTOM)->Check(true);
						break;
				}
			}
			break;
		}

		case ID_GAME_EXIT:
		{
			Close();
			break;
		}

		case ID_HELP_ABOUT:
		{
			AboutDialog dlg(this);
			dlg.ShowModal();

			break;
		}

		default:
			break;
	}

}

// ReSharper disable once CppMemberFunctionMayBeConst
void MainWindow::MineField_OnLeftDown(wxMouseEvent& event)
{
	if (m_mineField->IsGameInProgress())
	{
		m_btnNewGame->SetBitmap(wxBitmap(smile_4_xpm));
	}

	event.Skip();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void MainWindow::MineField_OnLeftUp(wxMouseEvent& event)
{
	if (m_mineField->IsGameInProgress())
	{
		m_btnNewGame->SetBitmap(wxBitmap(smile_1_xpm));
	}

	event.Skip();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void MainWindow::MineField_OnCellFlagToggled([[maybe_unused]] wxCommandEvent& event)
{
	m_ssdUnflaggedMineCount->SetValue(m_mineField->GetMineCount() - m_mineField->GetFlagCount());
}

// ReSharper disable once CppMemberFunctionMayBeConst
void MainWindow::StartNewGame()
{
	switch (m_difficulty)
	{
		case BEGINNER:
			m_mineField->Reset({ 9, 9 }, 10);
			break;
		case INTERMEDIATE:
			m_mineField->Reset({ 16, 16 }, 40);
			break;
		case EXPERT:
			m_mineField->Reset({ 30, 16 }, 99);
			break;
		case CUSTOM:
			m_mineField->Reset(m_customFieldSize, m_customMineCount);
			break;
	}

	m_ssdUnflaggedMineCount->SetValue(m_mineField->GetMineCount());
	if (m_timer.IsRunning())
	{
		m_timer.Stop();
	}
	m_ssdElapsedSeconds->SetValue(0);
	m_btnNewGame->SetBitmap(wxBitmap(smile_1_xpm));
}

// ReSharper disable once CppMemberFunctionMayBeConst
void MainWindow::BtnNewGame_OnClick([[maybe_unused]] wxCommandEvent& event)
{
	StartNewGame();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void MainWindow::Timer_OnTick(wxTimerEvent& event)
{
	m_ssdElapsedSeconds->SetValue(m_ssdElapsedSeconds->GetValue() + 1);
}

void MainWindow::MineField_OnFirstCellClicked(wxCommandEvent& event)
{
	m_timer.Start(1000);
}

// ReSharper disable once CppParameterMayBeConstPtrOrRef
void MainWindow::MineField_OnGameOver(wxCommandEvent& event)
{
	switch (event.GetInt())
	{
		case MineField::LOSS:
		{
			m_btnNewGame->SetBitmap(wxBitmap(smile_3_xpm));
			break;
		}

		case MineField::WIN:
		{
			m_btnNewGame->SetBitmap(wxBitmap(smile_2_xpm));

			if (m_difficulty == CUSTOM)
			{
				break;
			}

			if (m_bestTimes.isMember(m_difficultyName))
			{
				if (m_bestTimes[m_difficultyName]["time"].asInt() > m_ssdElapsedSeconds->GetValue())
				{
					break;
				}
			}
			if (wxTextEntryDialog dialog(this, "Congratulations! You won! Enter your name for the best times list:", "You Win!", "", wxTextEntryDialogStyle);
				dialog.ShowModal() == wxID_OK)
			{
				const std::string playerName = dialog.GetValue().ToStdString();
				m_bestTimes[m_difficultyName]["name"] = playerName;
				m_bestTimes[m_difficultyName]["time"] = m_ssdElapsedSeconds->GetValue();
			}
			break;
		}

		default:
			break;
	}

	m_timer.Stop();
}

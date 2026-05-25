// Copyright (c) 2026 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

#include "MineField.h"
#include <sstream>
#include <stack>
#include <wx/dcbuffer.h>
#include <wx/graphics.h>

#include "bitmaps/explosion-small.xpm"
#include "bitmaps/flag-small.xpm"

wxDEFINE_EVENT(MINEFIELD_GAME_OVER, wxCommandEvent);
wxDEFINE_EVENT(MINEFIELD_CELL_FLAG_TOGGLED, wxCommandEvent);
wxDEFINE_EVENT(MINEFIELD_FIRST_CELL_CLICKED, wxCommandEvent);

MineField::MineField(wxWindow* parent)
{
	wxControl::SetBackgroundStyle(wxBG_STYLE_PAINT);
	Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE | wxFULL_REPAINT_ON_RESIZE);
	Bind(wxEVT_PAINT, &MineField::MineField_OnPaint, this);
	Bind(wxEVT_RIGHT_UP, &MineField::MineField_OnRightUp, this);
	Bind(wxEVT_LEFT_DOWN, &MineField::MineField_OnLeftDown, this);
	Bind(wxEVT_LEFT_UP, &MineField::MineField_OnLeftUp, this);
	Bind(wxEVT_MOTION, &MineField::MineField_OnMouseMove, this);
	Bind(wxEVT_LEFT_DCLICK, &MineField::MineField_OnLeftDoubleClick, this);
	wxControl::SetBackgroundColour(wxTheColourDatabase->Find("LIGHT GREY"));
	wxControl::SetForegroundColour(wxTheColourDatabase->Find("BLACK"));
	InitializeField();
}

void MineField::MineField_OnPaint([[maybe_unused]] wxPaintEvent& event)
{
	const wxAutoBufferedPaintDC dc(this);
	const auto gc = std::unique_ptr<wxGraphicsContext>(wxGraphicsContext::Create(dc));

	gc->SetAntialiasMode(wxANTIALIAS_DEFAULT);

	gc->SetBrush(GetBackgroundColour());
	gc->SetPen(GetBackgroundColour());

	const auto highlightColor = GetBackgroundColour().ChangeLightness(150);
	const auto shadowColor = GetBackgroundColour().ChangeLightness(50);

	const auto bmpFlag = wxBitmap(flag_small);
	const auto bmpExplosion = wxBitmap(explosion_small);

	const auto font = GetFont().Bold().Larger();

	gc->DrawRectangle(0, 0, GetSize().GetWidth(), GetSize().GetHeight());

	for (auto fieldY = 0; fieldY < m_fieldSize.GetHeight(); fieldY++)
	{
		const auto cellOriginY = fieldY * m_cellSize.GetHeight();
		for (auto fieldX = 0; fieldX < m_fieldSize.GetWidth(); fieldX++)
		{
			const auto cellOriginX = fieldX * m_cellSize.GetWidth();
			const auto& cell = m_cells[static_cast<size_t>(fieldY)][static_cast<size_t>(fieldX)];

			gc->SetBrush(GetBackgroundColour());

			if (cell->m_wasClicked && cell->m_isMine)
			{
				gc->SetBrush(wxTheColourDatabase->Find("RED"));
			}

			if (cell->m_isFlagged || (!cell->m_isRevealed && !(m_mouseLeftDown && m_hoveredCellLocation.x == fieldX && m_hoveredCellLocation.y == fieldY)))
			{
				for (auto i = 0; i < 3; i++)
				{
					gc->SetPen(wxPen(highlightColor));
					gc->StrokeLine(cellOriginX + i, cellOriginY + i, cellOriginX + m_cellSize.GetWidth() - i, cellOriginY + i);
					gc->StrokeLine(cellOriginX + i, cellOriginY + i, cellOriginX + i, cellOriginY + m_cellSize.GetHeight() - i);

					gc->SetPen(wxPen(shadowColor));
					gc->StrokeLine(cellOriginX + i, cellOriginY + m_cellSize.GetHeight() - i, cellOriginX + m_cellSize.GetWidth() - i, cellOriginY + m_cellSize.GetHeight() - i);
					gc->StrokeLine(cellOriginX + m_cellSize.GetWidth() - i, cellOriginY + i, cellOriginX + m_cellSize.GetWidth() - i, cellOriginY + m_cellSize.GetHeight() - i);
				}

				if (cell->m_isFlagged && !cell->m_isRevealed)
				{
					gc->DrawBitmap(bmpFlag, cellOriginX + 3, cellOriginY + 3, m_cellSize.GetWidth() - 6, m_cellSize.GetHeight() - 6);
				}
			}
			else
			{
				gc->SetPen(wxPen(GetForegroundColour()));
				gc->DrawRectangle(cellOriginX, cellOriginY, m_cellSize.GetWidth(), m_cellSize.GetHeight());

				if (!cell->m_isRevealed)
				{
					continue;
				}

				if (cell->m_isMine)
				{
					gc->DrawBitmap(bmpExplosion, cellOriginX + 1, cellOriginY + 1, m_cellSize.GetWidth() - 2, m_cellSize.GetHeight() - 2);
				}
				else if (cell->m_adjacentMineCount > 0)
				{
					// Set the text color based on the number of adjacent mines
					wxColour textColor;
					switch (cell->m_adjacentMineCount)
					{
						case 1: textColor = wxTheColourDatabase->Find("BLUE"); break;
						case 2: textColor = wxTheColourDatabase->Find("GREEN"); break;
						case 3: textColor = wxTheColourDatabase->Find("RED"); break;
						case 4: textColor = wxTheColourDatabase->Find("DARK BLUE"); break;
						case 5: textColor = wxTheColourDatabase->Find("DARK RED"); break;
						case 6: textColor = wxTheColourDatabase->Find("CYAN"); break;
						case 7: textColor = wxTheColourDatabase->Find("BLACK"); break;
						case 8: textColor = wxTheColourDatabase->Find("GREY"); break;
						default: textColor = GetForegroundColour(); break;
					}

					const auto text = std::to_wstring(cell->m_adjacentMineCount);
					double textWidth, textHeight;
					gc->SetFont(font, textColor);
					gc->GetTextExtent(text, &textWidth, &textHeight);
					gc->DrawText(text, cellOriginX + (m_cellSize.GetWidth() - textWidth) / 2, cellOriginY + (m_cellSize.GetHeight() - textHeight) / 2);
				}
			}

			if (cell->m_isFlagged && cell->m_isRevealed)
			{
				gc->SetBrush(GetBackgroundColour());
				gc->SetPen(wxPen(GetForegroundColour()));
				gc->DrawRectangle(cellOriginX, cellOriginY, m_cellSize.GetWidth(), m_cellSize.GetHeight());
				gc->DrawBitmap(explosion_small, cellOriginX + 1, cellOriginY + 1, m_cellSize.GetWidth() - 2, m_cellSize.GetHeight() - 2);
				gc->SetPen(wxPen(wxTheColourDatabase->Find("RED"), 2));
				gc->StrokeLine(cellOriginX, cellOriginY, cellOriginX + m_cellSize.GetWidth(), cellOriginY + m_cellSize.GetHeight());
				gc->StrokeLine(cellOriginX + m_cellSize.GetWidth(), cellOriginY, cellOriginX, cellOriginY + m_cellSize.GetHeight());
			}
		}
	}
}

wxSize MineField::DoGetBestClientSize() const
{
	const auto width = m_cellSize.GetWidth() * m_fieldSize.GetWidth() + 1;
	const auto height = m_cellSize.GetHeight() * m_fieldSize.GetHeight() + 1;
	return { width, height };
}

void MineField::SetCellSize(const wxSize cellSize)
{
	m_cellSize = cellSize;
	InvalidateBestSize();
	Refresh();
}

void MineField::MineField_OnRightUp(wxMouseEvent& event)
{
	if (!m_gameInProgress)
	{
		return;
	}

	const auto clientCoords = event.GetPosition();
	const auto fieldCoords = ClientCoordsToFieldCoords(clientCoords);

	const auto& cell = m_cells[static_cast<size_t>(fieldCoords.y)][static_cast<size_t>(fieldCoords.x)];

	if (cell->m_isRevealed)
	{
		return;
	}

	if (m_flagCount >= m_mineCount && !cell->m_isFlagged)
	{
		return;
	}

	cell->m_isFlagged = !cell->m_isFlagged;
	m_flagCount += cell->m_isFlagged ? 1 : -1;

	if (cell->m_isFlagged)
	{
		m_flagLocations.push_back(fieldCoords);
	}
	else
	{
		std::erase(m_flagLocations, fieldCoords);
	}

	SendCellFlagToggledEvent();

	Refresh();
	event.Skip();
}

wxPoint MineField::ClientCoordsToFieldCoords(const wxPoint clientCoords) const
{
	wxPoint fieldCoords{ -1,-1 };

	if (clientCoords.x >= 0 && clientCoords.y >= 0 && clientCoords.x < GetSize().GetWidth() && clientCoords.y < GetSize().GetHeight())
	{
		fieldCoords.x = clientCoords.x / m_cellSize.GetWidth();
		fieldCoords.y = clientCoords.y / m_cellSize.GetHeight();
	}

	return fieldCoords;
}

void MineField::MineField_OnLeftDown(wxMouseEvent& event)
{
	if (!m_gameInProgress)
	{
		return;
	}

	m_mouseLeftDown = true;
	CaptureMouse();
	Refresh();
	event.Skip();
}

void MineField::MineField_OnLeftUp(wxMouseEvent& event)
{
	if (!m_gameInProgress)
	{
		return;
	}

	m_mouseLeftDown = false;
	if (HasCapture())
	{
		ReleaseMouse();
	}

	if (const auto fieldCoords = ClientCoordsToFieldCoords(event.GetPosition());
		!(fieldCoords.x < 0 || fieldCoords.y < 0 || fieldCoords.x >= m_fieldSize.GetWidth() || fieldCoords.y >= m_fieldSize.GetHeight()))
	{
		if (!m_firstCellClicked)
		{
			m_firstCellClicked = true;
			SendFirstCellClickedEvent();
		}
		m_cells[static_cast<size_t>(fieldCoords.y)][static_cast<size_t>(fieldCoords.x)]->m_wasClicked = true;
		RevealCells(fieldCoords);

		std::vector<wxPoint> unrevealedCellLocations;
		for (auto y = 0; y < m_fieldSize.GetHeight(); y++)
		{
			for (auto x = 0; x < m_fieldSize.GetWidth(); x++)
			{
				if (const auto& cell = m_cells[static_cast<size_t>(y)][static_cast<size_t>(x)]; !cell->m_isRevealed)
				{
					unrevealedCellLocations.emplace_back(x, y);
				}
			}
		}

		std::ranges::sort(unrevealedCellLocations, [](const wxPoint& a, const wxPoint& b)
			{
				return a.y == b.y ? a.x < b.x : a.y < b.y;
			}
		);

		// Check if all unrevealed cells are mines, which means the player has won.
		if (std::ranges::equal(unrevealedCellLocations, m_mineLocations))
		{
#ifdef _DEBUG
			OutputDebugStringW(L"Game won.\n");
#endif
			m_gameInProgress = false;
			SendGameOverEvent(WIN);
		}
	}
	Refresh();

	event.Skip();
}

void MineField::MineField_OnMouseMove(wxMouseEvent& event)
{
	if (!m_gameInProgress)
	{
		return;
	}

	const auto clientCoords = event.GetPosition();
	m_hoveredCellLocation = ClientCoordsToFieldCoords(clientCoords);

	Refresh();

	event.Skip();
}

void MineField::InitializeField()
{
	m_mineLocations.clear();
	m_cells.clear();
	m_distX = std::uniform_int_distribution<>(0, m_fieldSize.GetWidth() - 1);
	m_distY = std::uniform_int_distribution<>(0, m_fieldSize.GetHeight() - 1);

	for (auto y = 0; y < m_fieldSize.GetHeight(); y++)
	{
		auto row = std::vector<std::unique_ptr<Cell>>{};
		for (auto x = 0; x < m_fieldSize.GetWidth(); x++)
		{
			row.push_back(std::make_unique<Cell>());
		}
		m_cells.push_back(std::move(row));
	}

	for (auto i = 0; i < m_mineCount; i++)
	{
		auto x = m_distX(m_rng);
		auto y = m_distY(m_rng);

		while (m_cells[static_cast<size_t>(y)][static_cast<size_t>(x)]->m_isMine)
		{
			x = m_distX(m_rng);
			y = m_distY(m_rng);
		}

		m_cells[static_cast<size_t>(y)][static_cast<size_t>(x)]->m_isMine = true;
		m_mineLocations.emplace_back(x, y);

		// Update adjacent mine counts
		for (auto adjY = y - 1; adjY <= y + 1; adjY++)
		{
			for (auto adjX = x - 1; adjX <= x + 1; adjX++)
			{
				if (adjX >= 0 && adjY >= 0 && adjX < m_fieldSize.GetWidth() && adjY < m_fieldSize.GetHeight())
				{
					m_cells[static_cast<size_t>(adjY)][static_cast<size_t>(adjX)]->m_adjacentMineCount += 1;
				}
			}
		}

		// Sort the list of mine locations by y and then x.
		std::ranges::sort(m_mineLocations, [](const wxPoint& a, const wxPoint& b)
			{
				return a.y == b.y ? a.x < b.x : a.y < b.y;
			}
		);
	}

#ifdef _DEBUG
	// For testing purposes, reveal all cells in debug builds
	for (auto y = 0; y < m_fieldSize.GetHeight(); y++)
	{
		std::wstringstream ss;
		for (auto x = 0; x < m_fieldSize.GetWidth(); x++)
		{
			const auto& cell = m_cells[static_cast<size_t>(y)][static_cast<size_t>(x)];
			ss << (cell->m_isMine ? L"*" : cell->m_adjacentMineCount > 0 ? std::to_wstring(cell->m_adjacentMineCount) : L"-") << L" ";
		}
		ss << L"\n";
		OutputDebugStringW(ss.str().c_str());
	}
#endif
}

// ReSharper disable once CppMemberFunctionMayBeConst
void MineField::RevealCells(const wxPoint cellCoords)
{
	std::stack<wxPoint> toReveal;
	toReveal.push(cellCoords);

	while (!toReveal.empty())
	{
		const auto current = toReveal.top();
		toReveal.pop();
		const auto& cell = m_cells[static_cast<size_t>(current.y)][static_cast<size_t>(current.x)];
		if (cell->m_isRevealed || cell->m_isFlagged)
		{
			continue;
		}
		cell->m_isRevealed = true;
		if (cell->m_isMine)
		{
#ifdef _DEBUG
			OutputDebugStringW(L"Game lost.\n");
#endif
			m_gameInProgress = false;
			RevealMines();
			SendGameOverEvent(LOSS);
			break;
		}
		if (cell->m_adjacentMineCount == 0)
		{
			for (auto adjY = current.y - 1; adjY <= current.y + 1; adjY++)
			{
				for (auto adjX = current.x - 1; adjX <= current.x + 1; adjX++)
				{
					if (adjX >= 0 && adjY >= 0 && adjX < m_fieldSize.GetWidth() && adjY < m_fieldSize.GetHeight())
					{
						toReveal.emplace(adjX, adjY);
					}
				}
			}
		}
	}
}

// ReSharper disable once CppParameterMayBeConstPtrOrRef
void MineField::MineField_OnLeftDoubleClick(wxMouseEvent& event)
{
	if (!m_gameInProgress)
	{
		return;
	}

	const auto fieldCoords = ClientCoordsToFieldCoords(event.GetPosition());

	if (fieldCoords.x < 0 || fieldCoords.y < 0 || fieldCoords.x >= m_fieldSize.GetWidth() || fieldCoords.y >= m_fieldSize.GetHeight())
	{
		return;
	}

	const auto& cell = m_cells[static_cast<size_t>(fieldCoords.y)][static_cast<size_t>(fieldCoords.x)];

	if (!cell->m_isRevealed)
	{
		return;
	}

	// Count the number adjacent flagged cells
	int flaggedCount = 0;
	for (auto adjY = fieldCoords.y - 1; adjY <= fieldCoords.y + 1; adjY++)
	{
		for (auto adjX = fieldCoords.x - 1; adjX <= fieldCoords.x + 1; adjX++)
		{
			if (adjX >= 0 && adjY >= 0 && adjX < m_fieldSize.GetWidth() && adjY < m_fieldSize.GetHeight())
			{
				if (m_cells[static_cast<size_t>(adjY)][static_cast<size_t>(adjX)]->m_isFlagged)
				{
					flaggedCount++;
				}
			}
		}
	}

	if (flaggedCount == cell->m_adjacentMineCount)
	{
		for (auto adjY = fieldCoords.y - 1; adjY <= fieldCoords.y + 1; adjY++)
		{
			for (auto adjX = fieldCoords.x - 1; adjX <= fieldCoords.x + 1; adjX++)
			{
				if (adjX >= 0 && adjY >= 0 && adjX < m_fieldSize.GetWidth() && adjY < m_fieldSize.GetHeight())
				{
					if (const auto& adjacentCell = m_cells[static_cast<size_t>(adjY)][static_cast<size_t>(adjX)];
						!(adjacentCell->m_isFlagged || adjacentCell->m_isRevealed))
					{
						RevealCells({ adjX, adjY });
					}
				}
			}
		}
	}

	Refresh();
	event.Skip();
}

void MineField::SendGameOverEvent(const GameOverReason reason)
{
	wxCommandEvent event(MINEFIELD_GAME_OVER);
	event.SetEventObject(this);
	event.SetInt(reason);
	ProcessWindowEvent(event);
}

void MineField::SendCellFlagToggledEvent()
{
	wxCommandEvent event(MINEFIELD_CELL_FLAG_TOGGLED);
	event.SetEventObject(this);
	ProcessWindowEvent(event);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void MineField::RevealMines()
{
	// Mark all mines as revealed so they will be shown in the next paint event.
	for (const auto& mineLocation : m_mineLocations)
	{
		m_cells[static_cast<size_t>(mineLocation.y)][static_cast<size_t>(mineLocation.x)]->m_isRevealed = true;
	}

	for (const auto& flagLocation : m_flagLocations)
	{
		m_cells[static_cast<size_t>(flagLocation.y)][static_cast<size_t>(flagLocation.x)]->m_isRevealed = true;
	}
}

void MineField::Reset(const wxSize newFieldSize, const int newMineCount)
{
	if (newFieldSize != wxSize(-1, -1))
	{
		m_fieldSize = newFieldSize;
		m_distX = std::uniform_int_distribution<>(0, m_fieldSize.GetWidth() - 1);
		m_distY = std::uniform_int_distribution<>(0, m_fieldSize.GetHeight() - 1);
		InvalidateBestSize();
	}
	if (newMineCount != -1)
	{
		m_mineCount = newMineCount;
	}

	InitializeField();
	m_gameInProgress = true;
	m_flagCount = 0;
	m_flagLocations.clear();
	m_firstCellClicked = false;
	Refresh();
	GetParent()->Layout();
	GetParent()->Fit();
}

void MineField::SendFirstCellClickedEvent()
{
	wxCommandEvent event(MINEFIELD_FIRST_CELL_CLICKED);
	event.SetEventObject(this);
	ProcessWindowEvent(event);
	m_firstCellClicked = true;
}

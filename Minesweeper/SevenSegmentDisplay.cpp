// Copyright (c) 2024 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

#include "pch.h"
#include "SevenSegmentDisplay.h"
#include <wx/dcbuffer.h>
#include <wx/graphics.h>

std::unordered_map<char, std::vector<SevenSegmentDisplay::Segment>> SevenSegmentDisplay::m_digitSegments
{
	{' ', {}},
	{'0', {TOP, TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT, BOTTOM}},
	{'1', {TOP_RIGHT, BOTTOM_RIGHT}},
	{'2', {TOP, TOP_RIGHT, MIDDLE, BOTTOM_LEFT, BOTTOM}},
	{'3', {TOP, TOP_RIGHT, MIDDLE, BOTTOM_RIGHT, BOTTOM}},
	{'4', {TOP_LEFT, MIDDLE, TOP_RIGHT, BOTTOM_RIGHT}},
	{'5', {TOP, TOP_LEFT, MIDDLE, BOTTOM_RIGHT, BOTTOM}},
	{'6', {TOP, TOP_LEFT, BOTTOM_LEFT, BOTTOM, BOTTOM_RIGHT, MIDDLE}},
	{'7', {TOP, TOP_RIGHT, BOTTOM_RIGHT}},
	{'8', {SEGMENT_LIST}},
	{'9', {BOTTOM, BOTTOM_RIGHT, TOP_RIGHT, TOP, TOP_LEFT, MIDDLE}}
};

SevenSegmentDisplay::SevenSegmentDisplay(wxWindow* parent)
{
	wxControl::SetBackgroundStyle(wxBG_STYLE_PAINT);
	Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE | wxBORDER_NONE);
	wxControl::SetBackgroundColour(wxTheColourDatabase->Find("BLACK"));
	wxControl::SetForegroundColour(wxTheColourDatabase->Find("YELLOW"));
	Bind(wxEVT_PAINT, &SevenSegmentDisplay::SevenSegmentDisplay_OnPaint, this);
}

void SevenSegmentDisplay::SevenSegmentDisplay_OnPaint([[maybe_unused]] wxPaintEvent& event)
{
	const wxAutoBufferedPaintDC dc(this);
	auto* gc = wxGraphicsContext::Create(dc);

	gc->SetAntialiasMode(wxANTIALIAS_DEFAULT);
	gc->SetBrush(GetParent()->GetBackgroundColour());
	gc->SetPen(GetParent()->GetBackgroundColour());

	const auto clientSize = GetClientSize();

	gc->DrawRectangle(0, 0, clientSize.GetWidth() - 1, clientSize.GetHeight() - 1);

	gc->SetBrush(GetBackgroundColour());
	gc->SetPen(GetBackgroundColour());

	gc->DrawRoundedRectangle(0, 0, clientSize.GetWidth() - 1, clientSize.GetHeight() - 1, 4);

	const auto litColor = GetForegroundColour();
	const auto unlitColor = GetForegroundColour().ChangeLightness(25);

	auto valueString = std::to_string(m_value);

	if (valueString.length() > m_digitCount)
	{
		valueString = valueString.substr(valueString.length() - m_digitCount);
	}
	else if (valueString.length() < m_digitCount)
	{
		valueString.insert(0, m_digitCount - valueString.length(), m_leadingZerosVisible ? '0' : ' ');
	}

	const auto digitOriginY = m_digitSpacing;
	const auto halfHeight = m_digitSize.GetHeight() / 2;

	for (auto i = 0; i < m_digitCount; i++)
	{
		const auto digit = valueString[i];
		const auto digitSegments = m_digitSegments[digit];

		const auto digitOriginX = m_digitSpacing + (m_digitSpacing + m_digitSize.GetWidth()) * i;

		for (const auto segment : { SEGMENT_LIST })
		{
			auto path = gc->CreatePath();

			switch (segment)
			{
				case TOP:
				{
					path.MoveToPoint(digitOriginX + 1, digitOriginY);
					path.AddLineToPoint(digitOriginX + m_digitSize.GetWidth() - 1, digitOriginY);
					path.AddLineToPoint(digitOriginX + m_digitSize.GetWidth() - m_segmentThickness - 1, digitOriginY + m_segmentThickness);
					path.AddLineToPoint(digitOriginX + m_segmentThickness + 1, digitOriginY + m_segmentThickness);
					path.CloseSubpath();

					break;
				}

				case TOP_LEFT:
				{
					path.MoveToPoint(digitOriginX, digitOriginY + 1);
					path.AddLineToPoint(digitOriginX + m_segmentThickness, digitOriginY + m_segmentThickness + 1);
					path.AddLineToPoint(digitOriginX + m_segmentThickness, digitOriginY + halfHeight - m_segmentThickness - 1);
					path.AddLineToPoint(digitOriginX, digitOriginY + halfHeight - 1);
					path.CloseSubpath();

					break;
				}

				case TOP_RIGHT:
				{
					path.MoveToPoint(digitOriginX + m_digitSize.GetWidth(), digitOriginY + 1);
					path.AddLineToPoint(digitOriginX + m_digitSize.GetWidth() - m_segmentThickness, digitOriginY + m_segmentThickness + 1);
					path.AddLineToPoint(digitOriginX + m_digitSize.GetWidth() - m_segmentThickness, digitOriginY + halfHeight - m_segmentThickness - 1);
					path.AddLineToPoint(digitOriginX + m_digitSize.GetWidth(), digitOriginY + halfHeight - 1);
					path.CloseSubpath();

					break;
				}

				case MIDDLE:
				{
					path.MoveToPoint(digitOriginX + 1, digitOriginY + halfHeight);
					path.AddLineToPoint(digitOriginX + m_segmentThickness, digitOriginY + halfHeight - m_segmentThickness + 1);
					path.AddLineToPoint(digitOriginX + m_digitSize.GetWidth() - m_segmentThickness, digitOriginY + halfHeight - m_segmentThickness + 1);
					path.AddLineToPoint(digitOriginX + m_digitSize.GetWidth() - 1, digitOriginY + halfHeight);
					path.AddLineToPoint(digitOriginX + m_digitSize.GetWidth() - m_segmentThickness, digitOriginY + halfHeight + m_segmentThickness - 1);
					path.AddLineToPoint(digitOriginX + m_segmentThickness, digitOriginY + halfHeight + m_segmentThickness - 1);
					path.CloseSubpath();

					break;
				}

				case BOTTOM_LEFT:
				{
					path.MoveToPoint(digitOriginX, digitOriginY + halfHeight + 1);
					path.AddLineToPoint(digitOriginX + m_segmentThickness, digitOriginY + halfHeight + m_segmentThickness + 1);
					path.AddLineToPoint(digitOriginX + m_segmentThickness, digitOriginY + m_digitSize.GetHeight() - m_segmentThickness - 1);
					path.AddLineToPoint(digitOriginX, digitOriginY + m_digitSize.GetHeight() - 1);
					path.CloseSubpath();

					break;
				}

				case BOTTOM_RIGHT:
				{
					path.MoveToPoint(digitOriginX + m_digitSize.GetWidth(), digitOriginY + halfHeight + 1);
					path.AddLineToPoint(digitOriginX + m_digitSize.GetWidth() - m_segmentThickness, digitOriginY + halfHeight + m_segmentThickness + 1);
					path.AddLineToPoint(digitOriginX + m_digitSize.GetWidth() - m_segmentThickness, digitOriginY + m_digitSize.GetHeight() - m_segmentThickness - 1);
					path.AddLineToPoint(digitOriginX + m_digitSize.GetWidth(), digitOriginY + m_digitSize.GetHeight() - 1);
					path.CloseSubpath();

					break;
				}

				case BOTTOM:
				{
					path.MoveToPoint(digitOriginX + 1, digitOriginY + m_digitSize.GetHeight());
					path.AddLineToPoint(digitOriginX + m_digitSize.GetWidth() - 1, digitOriginY + m_digitSize.GetHeight());
					path.AddLineToPoint(digitOriginX + m_digitSize.GetWidth() - m_segmentThickness - 1, digitOriginY + m_digitSize.GetHeight() - m_segmentThickness);
					path.AddLineToPoint(digitOriginX + m_segmentThickness + 1, digitOriginY + m_digitSize.GetHeight() - m_segmentThickness);
					path.CloseSubpath();

					break;
				}
			}

			const auto color = std::ranges::find(digitSegments, segment) == digitSegments.end() ? unlitColor : litColor;
			gc->SetBrush(color);
			gc->SetPen(color);
			gc->DrawPath(path);
		}
	}

	delete gc;
}

wxSize SevenSegmentDisplay::DoGetBestClientSize() const
{
	const auto width = m_digitSpacing * (m_digitCount + 1) + m_digitSize.GetWidth() * m_digitCount + 1;
	const auto height = m_digitSpacing * 2 + m_digitSize.GetHeight() + 1;

	return { width, height };
}

void SevenSegmentDisplay::SetValue(const uint8_t value)
{
	if (m_value == value) return;

	m_value = value;
	Refresh();
}

void SevenSegmentDisplay::SetDigitSpacing(const uint8_t digitSpacing)
{
	if (m_digitSpacing == digitSpacing) return;

	m_digitSpacing = digitSpacing;
	InvalidateBestSize();
	Refresh();
}

void SevenSegmentDisplay::SetSegmentThickness(const uint8_t segmentThickness)
{
	if (m_segmentThickness == segmentThickness) return;

	m_segmentThickness = segmentThickness;
	Refresh();
}

void SevenSegmentDisplay::SetDigitSize(const wxSize digitSize)
{
	if (m_digitSize == digitSize) return;

	m_digitSize = digitSize;
	InvalidateBestSize();
	Refresh();
}

void SevenSegmentDisplay::SetLeadingZerosVisible(const bool leadingZerosVisible)
{
	if (m_leadingZerosVisible == leadingZerosVisible) return;

	m_leadingZerosVisible = leadingZerosVisible;
	Refresh();
}

void SevenSegmentDisplay::SetDigitCount(const uint8_t digitCount)
{
	if (m_digitCount == digitCount) return;

	m_digitCount = digitCount;
	InvalidateBestSize();
	Refresh();
}

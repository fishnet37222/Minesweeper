// Copyright (c) 2025 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

#include "pch.h"
#include "SevenSegmentDisplay.h"
#include <wx/dcbuffer.h>
#include <wx/graphics.h>

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
	const auto gc = std::unique_ptr<wxGraphicsContext>(wxGraphicsContext::Create(dc));

	gc->SetBrush(GetParent()->GetBackgroundColour());
	gc->SetPen(GetParent()->GetBackgroundColour());
	gc->DrawRectangle(0, 0, GetClientSize().GetWidth(), GetClientSize().GetHeight());

	gc->SetBrush(GetBackgroundColour());
	gc->SetPen(GetBackgroundColour());
	gc->DrawRoundedRectangle(0, 0, GetClientSize().GetWidth() - 1, GetClientSize().GetHeight() - 1, 4);

	auto valueText = std::to_string(m_value);

	if (static_cast<int>(valueText.length()) > m_digitCount)
	{
		valueText = valueText.substr(valueText.length() - m_digitCount);
	}
	else if (static_cast<int>(valueText.length()) < m_digitCount)
	{
		const auto paddingChar = m_leadingZerosVisible ? '0' : ' ';
		valueText.insert(0, m_digitCount - valueText.length(), paddingChar);
	}

	const auto litColor = GetForegroundColour();
	const auto unlitColor = litColor.ChangeLightness(20);
	const auto halfHeight = m_digitSize.GetHeight() / 2;

	for (auto digitIndex = 0; digitIndex < m_digitCount; digitIndex++)
	{
		const auto digit = valueText[digitIndex];
		const auto digitSegments = m_digitSegmentMap[digit];
		const auto digitOriginX = m_digitSpacing + (m_digitSize.GetWidth() + m_digitSpacing) * digitIndex;
		const auto digitOriginY = m_digitSpacing;

		for (const auto segment : { SEGMENT_LIST })
		{
			auto segmentPath = gc->CreatePath();

			switch (segment)
			{
				case TOP:
				{
					segmentPath.MoveToPoint(digitOriginX + 1, digitOriginY);
					segmentPath.AddLineToPoint(digitOriginX + m_digitSize.GetWidth() - 1, digitOriginY);
					segmentPath.AddLineToPoint(digitOriginX + m_digitSize.GetWidth() - m_segmentThickness - 1, digitOriginY + m_segmentThickness);
					segmentPath.AddLineToPoint(digitOriginX + m_segmentThickness + 1, digitOriginY + m_segmentThickness);
					segmentPath.CloseSubpath();

					break;
				}

				case TOP_LEFT:
				{
					segmentPath.MoveToPoint(digitOriginX, digitOriginY + 1);
					segmentPath.AddLineToPoint(digitOriginX, digitOriginY + halfHeight - 1);
					segmentPath.AddLineToPoint(digitOriginX + m_segmentThickness, digitOriginY + halfHeight - m_segmentThickness - 1);
					segmentPath.AddLineToPoint(digitOriginX + m_segmentThickness, digitOriginY + m_segmentThickness + 1);
					segmentPath.CloseSubpath();

					break;
				}

				case TOP_RIGHT:
				{
					segmentPath.MoveToPoint(digitOriginX + m_digitSize.GetWidth(), digitOriginY + 1);
					segmentPath.AddLineToPoint(digitOriginX + m_digitSize.GetWidth(), digitOriginY + halfHeight - 1);
					segmentPath.AddLineToPoint(digitOriginX + m_digitSize.GetWidth() - m_segmentThickness, digitOriginY + halfHeight - m_segmentThickness - 1);
					segmentPath.AddLineToPoint(digitOriginX + m_digitSize.GetWidth() - m_segmentThickness, digitOriginY + m_segmentThickness + 1);
					segmentPath.CloseSubpath();

					break;
				}

				case MIDDLE:
				{
					segmentPath.MoveToPoint(digitOriginX + 1, digitOriginY + halfHeight);
					segmentPath.AddLineToPoint(digitOriginX + m_segmentThickness, digitOriginY + halfHeight - m_segmentThickness + 1);
					segmentPath.AddLineToPoint(digitOriginX + m_digitSize.GetWidth() - m_segmentThickness, digitOriginY + halfHeight - m_segmentThickness + 1);
					segmentPath.AddLineToPoint(digitOriginX + m_digitSize.GetWidth() - 1, digitOriginY + halfHeight);
					segmentPath.AddLineToPoint(digitOriginX + m_digitSize.GetWidth() - m_segmentThickness, digitOriginY + halfHeight + m_segmentThickness - 1);
					segmentPath.AddLineToPoint(digitOriginX + m_segmentThickness, digitOriginY + halfHeight + m_segmentThickness - 1);
					segmentPath.CloseSubpath();

					break;
				}

				case BOTTOM_LEFT:
				{
					segmentPath.MoveToPoint(digitOriginX, digitOriginY + halfHeight + 1);
					segmentPath.AddLineToPoint(digitOriginX, digitOriginY + m_digitSize.GetHeight() - 1);
					segmentPath.AddLineToPoint(digitOriginX + m_segmentThickness, digitOriginY + m_digitSize.GetHeight() - m_segmentThickness - 1);
					segmentPath.AddLineToPoint(digitOriginX + m_segmentThickness, digitOriginY + halfHeight + m_segmentThickness + 1);
					segmentPath.CloseSubpath();

					break;
				}

				case BOTTOM_RIGHT:
				{
					segmentPath.MoveToPoint(digitOriginX + m_digitSize.GetWidth(), digitOriginY + halfHeight + 1);
					segmentPath.AddLineToPoint(digitOriginX + m_digitSize.GetWidth(), digitOriginY + m_digitSize.GetHeight() - 1);
					segmentPath.AddLineToPoint(digitOriginX + m_digitSize.GetWidth() - m_segmentThickness, digitOriginY + m_digitSize.GetHeight() - m_segmentThickness - 1);
					segmentPath.AddLineToPoint(digitOriginX + m_digitSize.GetWidth() - m_segmentThickness, digitOriginY + halfHeight + m_segmentThickness + 1);
					segmentPath.CloseSubpath();

					break;
				}

				case BOTTOM:
				{
					segmentPath.MoveToPoint(digitOriginX + 1, digitOriginY + m_digitSize.GetHeight());
					segmentPath.AddLineToPoint(digitOriginX + m_digitSize.GetWidth() - 1, digitOriginY + m_digitSize.GetHeight());
					segmentPath.AddLineToPoint(digitOriginX + m_digitSize.GetWidth() - m_segmentThickness - 1, digitOriginY + m_digitSize.GetHeight() - m_segmentThickness);
					segmentPath.AddLineToPoint(digitOriginX + m_segmentThickness + 1, digitOriginY + m_digitSize.GetHeight() - m_segmentThickness);
					segmentPath.CloseSubpath();

					break;
				}

			}

			const auto segmentColor = std::ranges::find(digitSegments, segment) != digitSegments.end() ? litColor : unlitColor;
			gc->SetBrush(segmentColor);
			gc->SetPen(segmentColor);
			gc->DrawPath(segmentPath);
		}
	}
}

wxSize SevenSegmentDisplay::DoGetBestClientSize() const
{
	const auto width = m_digitSpacing + (m_digitSize.GetWidth() + m_digitSpacing) * m_digitCount + 1;
	const auto height = m_digitSpacing * 2 + m_digitSize.GetHeight() + 1;

	return { width, height };
}

void SevenSegmentDisplay::SetValue(const int value)
{
	if (m_value == value) return;

	m_value = value;
	Refresh();
}

void SevenSegmentDisplay::SetDigitCount(const int digitCount)
{
	if (m_digitCount == digitCount) return;

	m_digitCount = digitCount;
	InvalidateBestSize();
	Refresh();
}

void SevenSegmentDisplay::SetSegmentThickness(const int segmentThickness)
{
	if (m_segmentThickness == segmentThickness) return;

	m_segmentThickness = segmentThickness;
	Refresh();
}

void SevenSegmentDisplay::SetDigitSpacing(const int digitSpacing)
{
	if (m_digitSpacing == digitSpacing) return;

	m_digitSpacing = digitSpacing;
	InvalidateBestSize();
	Refresh();
}

void SevenSegmentDisplay::SetDigitSize(const wxSize& digitSize)
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

// Copyright (c) 2026 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

#include "SevenSegmentDisplay.h"
#include <wx/dcbuffer.h>
#include <wx/graphics.h>

#include <utility>

SevenSegmentDisplay::SevenSegmentDisplay(wxWindow* parent)
{
	wxControl::SetBackgroundStyle(wxBG_STYLE_PAINT);
	Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE | wxFULL_REPAINT_ON_RESIZE);
	wxControl::SetBackgroundColour(wxTheColourDatabase->Find("BLACK"));
	wxControl::SetForegroundColour(wxTheColourDatabase->Find("YELLOW"));
	Bind(wxEVT_PAINT, &SevenSegmentDisplay::SevenSegmentDisplay_OnPaint, this);
}

void SevenSegmentDisplay::SevenSegmentDisplay_OnPaint([[maybe_unused]] wxPaintEvent& event)
{
	const wxAutoBufferedPaintDC dc(this);

	const auto graphicsContext = std::unique_ptr<wxGraphicsContext>(wxGraphicsContext::Create(dc));

	graphicsContext->SetAntialiasMode(wxANTIALIAS_DEFAULT);
	graphicsContext->SetPen(wxPen(GetBackgroundColour()));
	graphicsContext->SetBrush(wxBrush(GetBackgroundColour()));
	graphicsContext->DrawRectangle(0, 0, GetSize().x, GetSize().y);

	const auto litColor = GetForegroundColour();
	const auto unlitColor = GetForegroundColour().ChangeLightness(25);

	const auto halfDigitHeight = m_digitSize.y / 2;

	auto valueString = std::to_string(m_value);
	if (std::cmp_less(valueString.length(), m_digitCount))
	{
		valueString = std::string(m_digitCount - valueString.length(), m_leadingZerosVisible ? '0' : ' ') + valueString;
	}
	else if (std::cmp_greater(valueString.length(), m_digitCount))
	{
		valueString = valueString.substr(valueString.length() - m_digitCount);
	}

	for (auto digitIndex = 0; digitIndex < m_digitCount; ++digitIndex)
	{
		const auto digit = valueString[digitIndex];
		const auto digitSegments = m_segmentMap[digit];

		const auto digitOriginX = m_digitSpacing + digitIndex * (m_digitSize.x + m_digitSpacing);
		const auto digitOriginY = m_digitSpacing;

		for (const auto& segment : { SEGMENT_LIST })
		{
			auto segmentPath = graphicsContext->CreatePath();

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
					segmentPath.AddLineToPoint(digitOriginX, digitOriginY + halfDigitHeight - 1);
					segmentPath.AddLineToPoint(digitOriginX + m_segmentThickness, digitOriginY + halfDigitHeight - m_segmentThickness - 1);
					segmentPath.AddLineToPoint(digitOriginX + m_segmentThickness, digitOriginY + 1);
					segmentPath.CloseSubpath();

					break;
				}

				case TOP_RIGHT:
				{
					segmentPath.MoveToPoint(digitOriginX + m_digitSize.GetWidth(), digitOriginY + 1);
					segmentPath.AddLineToPoint(digitOriginX + m_digitSize.GetWidth(), digitOriginY + halfDigitHeight - 1);
					segmentPath.AddLineToPoint(digitOriginX + m_digitSize.GetWidth() - m_segmentThickness, digitOriginY + halfDigitHeight - m_segmentThickness - 1);
					segmentPath.AddLineToPoint(digitOriginX + m_digitSize.GetWidth() - m_segmentThickness, digitOriginY + 1);
					segmentPath.CloseSubpath();

					break;
				}

				case MIDDLE:
				{
					segmentPath.MoveToPoint(digitOriginX + 1, digitOriginY + halfDigitHeight);
					segmentPath.AddLineToPoint(digitOriginX + m_segmentThickness, digitOriginY + halfDigitHeight - m_segmentThickness + 1);
					segmentPath.AddLineToPoint(digitOriginX + m_digitSize.GetWidth() - m_segmentThickness, digitOriginY + halfDigitHeight - m_segmentThickness + 1);
					segmentPath.AddLineToPoint(digitOriginX + m_digitSize.GetWidth() - 1, digitOriginY + halfDigitHeight);
					segmentPath.AddLineToPoint(digitOriginX + m_digitSize.GetWidth() - m_segmentThickness, digitOriginY + halfDigitHeight + m_segmentThickness - 1);
					segmentPath.AddLineToPoint(digitOriginX + m_segmentThickness, digitOriginY + halfDigitHeight + m_segmentThickness - 1);
					segmentPath.CloseSubpath();

					break;
				}

				case BOTTOM_LEFT:
				{
					segmentPath.MoveToPoint(digitOriginX, digitOriginY + halfDigitHeight + 1);
					segmentPath.AddLineToPoint(digitOriginX, digitOriginY + m_digitSize.GetHeight() - 1);
					segmentPath.AddLineToPoint(digitOriginX + m_segmentThickness, digitOriginY + m_digitSize.GetHeight() - m_segmentThickness - 1);
					segmentPath.AddLineToPoint(digitOriginX + m_segmentThickness, digitOriginY + halfDigitHeight + m_segmentThickness + 1);
					segmentPath.CloseSubpath();

					break;
				}

				case BOTTOM_RIGHT:
				{
					segmentPath.MoveToPoint(digitOriginX + m_digitSize.GetWidth(), digitOriginY + halfDigitHeight + 1);
					segmentPath.AddLineToPoint(digitOriginX + m_digitSize.GetWidth(), digitOriginY + m_digitSize.GetHeight() - 1);
					segmentPath.AddLineToPoint(digitOriginX + m_digitSize.GetWidth() - m_segmentThickness, digitOriginY + m_digitSize.GetHeight() - m_segmentThickness - 1);
					segmentPath.AddLineToPoint(digitOriginX + m_digitSize.GetWidth() - m_segmentThickness, digitOriginY + halfDigitHeight + m_segmentThickness + 1);
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
			graphicsContext->SetPen(wxPen(segmentColor));
			graphicsContext->SetBrush(wxBrush(segmentColor));
			graphicsContext->DrawPath(segmentPath);
		}
	}
}

wxSize SevenSegmentDisplay::DoGetBestClientSize() const
{
	const auto width = m_digitCount * m_digitSize.x + (m_digitCount + 1) * m_digitSpacing;
	const auto height = m_digitSize.y + 2 * m_digitSpacing;
	return { width, height };
}

void SevenSegmentDisplay::SetValue(const int value)
{
	if (m_value == value)
	{
		return;
	}

	m_value = value;
	Refresh();
}

void SevenSegmentDisplay::SetDigitCount(const int count)
{
	if (m_digitCount == count)
	{
		return;
	}

	m_digitCount = count;
	InvalidateBestSize();
	Refresh();
}

void SevenSegmentDisplay::SetLeadingZerosVisible(const bool visible)
{
	if (m_leadingZerosVisible == visible)
	{
		return;
	}

	m_leadingZerosVisible = visible;
	Refresh();
}

void SevenSegmentDisplay::SetDigitSize(const wxSize& size)
{
	if (m_digitSize == size)
	{
		return;
	}

	m_digitSize = size;
	InvalidateBestSize();
	Refresh();
}

void SevenSegmentDisplay::SetSegmentThickness(int thickness)
{
	if (m_segmentThickness == thickness)
	{
		return;
	}

	m_segmentThickness = thickness;
	Refresh();
}

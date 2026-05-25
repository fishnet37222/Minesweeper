// Copyright (c) 2026 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

#pragma once
#include <unordered_map>
#include <vector>
#include <wx/wx.h>

#define SEGMENT_LIST TOP, TOP_LEFT, TOP_RIGHT, MIDDLE, BOTTOM_LEFT, BOTTOM_RIGHT, BOTTOM
enum Segment : uint8_t { SEGMENT_LIST };

class SevenSegmentDisplay final : public wxControl
{
public:
	inline static std::unordered_map<char, std::vector<Segment>> m_segmentMap
	{
		{'0', {TOP, TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT, BOTTOM}},
		{'1', {TOP_RIGHT, BOTTOM_RIGHT}},
		{'2', {TOP, TOP_RIGHT, MIDDLE, BOTTOM_LEFT, BOTTOM}},
		{'3', {TOP, TOP_RIGHT, MIDDLE, BOTTOM_RIGHT, BOTTOM}},
		{'4', {TOP_LEFT, TOP_RIGHT, MIDDLE, BOTTOM_RIGHT}},
		{'5', {TOP, TOP_LEFT, MIDDLE, BOTTOM_RIGHT, BOTTOM}},
		{'6', {TOP, TOP_LEFT, MIDDLE, BOTTOM_LEFT, BOTTOM_RIGHT, BOTTOM}},
		{'7', {TOP, TOP_RIGHT, BOTTOM_RIGHT}},
		{'8', {TOP, TOP_LEFT, TOP_RIGHT, MIDDLE, BOTTOM_LEFT, BOTTOM_RIGHT, BOTTOM}},
		{'9', {TOP, TOP_LEFT, TOP_RIGHT, MIDDLE, BOTTOM_RIGHT, BOTTOM}},
		{' ', {}}
	};

	explicit SevenSegmentDisplay(wxWindow* parent);
	[[nodiscard]] int GetValue() const { return m_value; }
	void SetValue(int value);
	[[nodiscard]] int GetDigitCount() const { return m_digitCount; }
	void SetDigitCount(int count);
	[[nodiscard]] bool GetLeadingZerosVisible() const { return m_leadingZerosVisible; }
	void SetLeadingZerosVisible(bool visible);
	[[nodiscard]] wxSize GetDigitSize() const { return m_digitSize; }
	void SetDigitSize(const wxSize& size);
	[[nodiscard]] int GetSegmentThickness() const { return m_segmentThickness; }
	void SetSegmentThickness(int thickness);

private:
	wxSize m_digitSize{ 20, 40 };
	int m_digitSpacing{ 5 };
	int m_segmentThickness{ 3 };
	bool m_leadingZerosVisible{ false };
	int m_value{ 0 };
	int m_digitCount{ 3 };

	void SevenSegmentDisplay_OnPaint(wxPaintEvent& event);
	[[nodiscard]] wxSize DoGetBestClientSize() const override;
};

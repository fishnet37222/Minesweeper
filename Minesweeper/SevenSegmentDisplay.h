// Copyright (c) 2025 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

#pragma once
#include <wx/wx.h>
#include <unordered_map>
#include <vector>

class SevenSegmentDisplay final : public wxControl
{
public:
	explicit SevenSegmentDisplay(wxWindow* parent);
	[[nodiscard]] int GetValue() const { return m_value; }
	void SetValue(int value);
	[[nodiscard]] int GetDigitCount() const { return m_digitCount; }
	void SetDigitCount(int digitCount);
	[[nodiscard]] int GetSegmentThickness() const { return m_segmentThickness; }
	void SetSegmentThickness(int segmentThickness);
	[[nodiscard]] int GetDigitSpacing() const { return m_digitSpacing; }
	void SetDigitSpacing(int digitSpacing);
	[[nodiscard]] wxSize GetDigitSize() const { return m_digitSize; }
	void SetDigitSize(const wxSize& digitSize);
	[[nodiscard]] bool AreLeadingZerosVisible() const { return m_leadingZerosVisible; }
	void SetLeadingZerosVisible(bool leadingZerosVisible);

private:
#define SEGMENT_LIST TOP, TOP_LEFT, TOP_RIGHT, MIDDLE, BOTTOM_LEFT, BOTTOM_RIGHT, BOTTOM
	enum Segment : uint8_t { SEGMENT_LIST };
	inline static std::unordered_map<char, std::vector<Segment>> m_digitSegmentMap =
	{
		{' ', {}},
		{'0', {TOP, TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT, BOTTOM}},
		{'1', {TOP_RIGHT, BOTTOM_RIGHT}},
		{'2', {TOP, TOP_RIGHT, MIDDLE, BOTTOM_LEFT, BOTTOM}},
		{'3', {TOP, TOP_RIGHT, MIDDLE, BOTTOM_RIGHT, BOTTOM}},
		{'4', {TOP_LEFT, TOP_RIGHT, MIDDLE, BOTTOM_RIGHT}},
		{'5', {TOP, TOP_LEFT, MIDDLE, BOTTOM_RIGHT, BOTTOM}},
		{'6', {TOP, TOP_LEFT, MIDDLE, BOTTOM_LEFT, BOTTOM_RIGHT, BOTTOM}},
		{'7', {TOP, TOP_RIGHT, BOTTOM_RIGHT}},
		{'8', {SEGMENT_LIST}},
		{'9', {TOP, TOP_LEFT, TOP_RIGHT, MIDDLE, BOTTOM_LEFT, BOTTOM}},
	};

	int m_value{ 0 };
	int m_digitCount{ 3 };
	int m_segmentThickness{ 3 };
	int m_digitSpacing{ 5 };
	wxSize m_digitSize{ 20,40 };
	bool m_leadingZerosVisible{ false };

	void SevenSegmentDisplay_OnPaint(wxPaintEvent& event);
	[[nodiscard]] wxSize DoGetBestClientSize() const override;
};

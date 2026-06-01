// Copyright (c) 2026 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

#pragma once
#include <json/value.h>
#include <wx/wx.h>
#include <wx/grid.h>

class BestTimesDialog final : public wxDialog
{
public:
	explicit BestTimesDialog(wxWindow* parent);

private:
	wxGrid* m_gridBestTimes{};
	wxButton* m_btnClose{};
	wxButton* m_btnReset{};

	void BestTimesDialog_OnBtnResetClick(wxCommandEvent& event);
	void PopulateGrid(Json::Value bestTimes) const;
};

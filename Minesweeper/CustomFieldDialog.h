// Copyright (c) 2026 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

#pragma once
#include <wx/wx.h>

class CustomFieldDialog final : public wxDialog
{
public:
	CustomFieldDialog(wxWindow* parent, const wxSize& customFieldSize, int customMineCount);
	[[nodiscard]] wxSize GetCustomFieldSize() const { return m_customFieldSize; }
	[[nodiscard]] int GetCustomMineCount() const { return m_customMineCount; }

private:
	wxSize m_customFieldSize{};
	int m_customMineCount{};
	wxTextCtrl* m_txtWidth{};
	wxTextCtrl* m_txtHeight{};
	wxTextCtrl* m_txtMineCount{};
	wxButton* m_btnOK{};
	wxButton* m_btnCancel{};

	void BtnOK_OnClick(wxCommandEvent& event);
};

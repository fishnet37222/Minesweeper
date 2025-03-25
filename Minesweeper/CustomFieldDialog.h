// Copyright (c) 2025 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

#pragma once
#include <wx/wx.h>

class CustomFieldDialog final : public wxDialog
{
public:
	CustomFieldDialog(wxWindow* parent, int fieldWidth, int fieldHeight, int mineCount);
	[[nodiscard]] int GetFieldWidth() const { return m_fieldWidth; }
	[[nodiscard]] int GetFieldHeight() const { return m_fieldHeight; }
	[[nodiscard]] int GetMineCount() const { return m_mineCount; }

private:
	int m_fieldWidth{};
	int m_fieldHeight{};
	int m_mineCount{};
	wxButton* m_btnCancel{};
	wxButton* m_btnOk{};
	wxTextCtrl* m_txtFieldWidth{};
	wxTextCtrl* m_txtFieldHeight{};
	wxTextCtrl* m_txtMineCount{};

	void BtnOk_OnClick(wxCommandEvent& event);
};

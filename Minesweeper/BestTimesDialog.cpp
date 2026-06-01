// Copyright (c) 2026 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

#include "pch.h"
#include "BestTimesDialog.h"
#include "App.h"

BestTimesDialog::BestTimesDialog(wxWindow* parent)
{
	wxDialog::SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_FRAMEBK));
	Create(parent, wxID_ANY, "Best Times");

	auto* szrMainOuter = new wxBoxSizer(wxHORIZONTAL);
	szrMainOuter->AddSpacer(10);
	auto* szrMainInner = new wxBoxSizer(wxVERTICAL);
	szrMainInner->AddSpacer(10);

	m_gridBestTimes = new wxGrid(this, wxID_ANY);
	m_gridBestTimes->CreateGrid(3, 4, wxGrid::wxGridSelectNone);
	m_gridBestTimes->SetRowLabelSize(0);
	m_gridBestTimes->SetColLabelValue(0, "Difficulty");
	m_gridBestTimes->SetColLabelValue(1, "Name");
	m_gridBestTimes->SetColLabelValue(2, "Time");
	m_gridBestTimes->SetColLabelValue(3, "Date");
	szrMainInner->Add(m_gridBestTimes, wxSizerFlags(1).Expand());

	szrMainInner->AddSpacer(5);

	auto* szrBottom = new wxBoxSizer(wxHORIZONTAL);
	szrBottom->AddStretchSpacer(1);
	auto* szrButtons = new wxGridSizer(1, 2, 5, 5);
	m_btnReset = new wxButton(this, wxID_ANY, "Reset");
	m_btnReset->Bind(wxEVT_BUTTON, &BestTimesDialog::BestTimesDialog_OnBtnResetClick, this);
	szrButtons->Add(m_btnReset, wxSizerFlags(0).Expand());
	m_btnClose = new wxButton(this, wxID_CLOSE, "Close");
	szrButtons->Add(m_btnClose, wxSizerFlags(0).Expand());
	szrBottom->Add(szrButtons, wxSizerFlags(0).Expand());
	szrMainInner->Add(szrBottom, wxSizerFlags(0).Expand());
	szrMainInner->AddSpacer(10);
	szrMainOuter->Add(szrMainInner, wxSizerFlags(1).Expand());
	szrMainOuter->AddSpacer(10);
	SetSizerAndFit(szrMainOuter);

	CenterOnParent();

	SetAffirmativeId(wxID_CLOSE);
	AddMainButtonId(wxID_CLOSE);
	SetEscapeId(wxID_CLOSE);

	PopulateGrid(wxGetApp().GetBestTimes());
}

// ReSharper disable once CppMemberFunctionMayBeConst
void BestTimesDialog::BestTimesDialog_OnBtnResetClick([[maybe_unused]] wxCommandEvent& event)
{
	if (wxMessageBox("Are you sure you want to reset the best times?", "Confirm Reset", wxYES_NO | wxICON_QUESTION, this) == wxYES)
	{
		wxGetApp().SetBestTimes({});
		PopulateGrid(wxGetApp().GetBestTimes());
	}
}

void BestTimesDialog::PopulateGrid(Json::Value bestTimes) const
{
	m_gridBestTimes->ClearGrid();

	for (auto i = 0; i < 3; i++)
	{
		std::tuple<std::string, std::string, std::string, std::string> entry;

		switch (i)
		{
			case 0:
			{
				if (bestTimes.isMember("Beginner"))
				{
					entry = std::make_tuple("Beginner", bestTimes["Beginner"]["name"].asString(), std::to_string(bestTimes["Beginner"]["time"].asInt()) + "s", bestTimes["Beginner"]["date"].asString());
				}
				else
				{
					entry = std::make_tuple("Beginner", "-", "-", "-");
				}

				break;
			}

			case 1:
			{
				if (bestTimes.isMember("Intermediate"))
				{
					entry = std::make_tuple("Intermediate", bestTimes["Intermediate"]["name"].asString(), std::to_string(bestTimes["Intermediate"]["time"].asInt()) + "s", bestTimes["Intermediate"]["date"].asString());
				}
				else
				{
					entry = std::make_tuple("Intermediate", "-", "-", "-");
				}

				break;
			}

			case 2:
			{
				if (bestTimes.isMember("Expert"))
				{
					entry = std::make_tuple("Expert", bestTimes["Expert"]["name"].asString(), std::to_string(bestTimes["Expert"]["time"].asInt()) + "s", bestTimes["Expert"]["date"].asString());
				}
				else
				{
					entry = std::make_tuple("Expert", "-", "-", "-");
				}

				break;
			}

			default:
				break;
		}

		m_gridBestTimes->SetCellValue(i, 0, std::get<0>(entry));
		m_gridBestTimes->SetCellValue(i, 1, std::get<1>(entry));
		m_gridBestTimes->SetCellValue(i, 2, std::get<2>(entry));
		m_gridBestTimes->SetCellValue(i, 3, std::get<3>(entry));
	}
}

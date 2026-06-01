// Copyright (c) 2026 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

#pragma once
#include <filesystem>
#include <wx/wx.h>
#include <json/json.h>

class App final : public wxApp
{
public:
	bool OnInit() override;
	int OnExit() override;
	[[nodiscard]] Json::Value& GetBestTimes() { return m_bestTimes; }
	void SetBestTimes(const Json::Value& bestTimes);

private:
	Json::Value m_bestTimes{};
	std::filesystem::path m_bestTimesFilePath{};
};

wxDECLARE_APP(App);

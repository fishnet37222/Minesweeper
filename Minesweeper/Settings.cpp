// Copyright (c) 2023 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

#include "pch.h"
#include "Settings.h"

wxConfig* Settings::config = nullptr;
bool Settings::created = false;

void Settings::Create()
{
	if (!created)
	{
		config = dynamic_cast<wxRegConfig*>(wxConfig::Get());
		created = true;
	}
}

wxPoint Settings::GetMainWindowPosition()
{
	if (!created)
	{
		Create();
	}

	const auto mainWindowPositionX = config->ReadLong("MainWindowPositionX", -1);
	const auto mainWindowPositionY = config->ReadLong("MainWindowPositionY", -1);
	return { mainWindowPositionX, mainWindowPositionY };
}

void Settings::SetMainWindowPosition(const wxPoint& position)
{
	if (!created)
	{
		Create();
	}

	config->Write("MainWindowPositionX", position.x);
	config->Write("MainWindowPositionY", position.y);
	config->Flush();
}

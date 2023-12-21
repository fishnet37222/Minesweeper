// Copyright (c) 2023 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <wx/config.h>

class Settings final
{
public:
	[[nodiscard]] static wxPoint GetMainWindowPosition();
	static void SetMainWindowPosition(const wxPoint& position);

private:
	static wxConfig* config;
	static bool created;

	static void Create();
};

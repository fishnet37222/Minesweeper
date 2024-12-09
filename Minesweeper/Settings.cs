// Copyright (c) 2024 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

using Microsoft.Win32;

namespace Minesweeper;

internal static class Settings
{
	private const string settingsRegSubPath = @"SOFTWARE\FishNetSoft\Minesweeper";

	internal static Point? MainWindowLocation
	{
		get
		{
			using var regKey = Registry.CurrentUser.OpenSubKey(settingsRegSubPath);
			var locationX = int.Parse(regKey?.GetValue("MainWindowLocationX")?.ToString() ?? "-1");
			var locationY = int.Parse(regKey?.GetValue("MainWindowLocationY")?.ToString() ?? "-1");

			if (locationX < 0 && locationY < 0)
			{
				return null;
			}

			return new(locationX, locationY);
		}

		set
		{
			if (value == null) return;

			using var regKey = Registry.CurrentUser.CreateSubKey(settingsRegSubPath);
			regKey.SetValue("MainWindowLocationX", value.Value.X);
			regKey.SetValue("MainWindowLocationY", value.Value.Y);
		}
	}
}

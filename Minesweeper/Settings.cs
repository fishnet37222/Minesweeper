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

	internal static Difficulty? Difficulty
	{
		get
		{
			using var regKey = Registry.CurrentUser.OpenSubKey(settingsRegSubPath);
			var difficulty = regKey?.GetValue("Difficulty")?.ToString();
			if (difficulty == null)
			{
				return null;
			}

			return Enum.Parse<Difficulty>(difficulty);
		}

		set
		{
			if (value == null) return;

			using var regKey = Registry.CurrentUser.CreateSubKey(settingsRegSubPath);
			regKey.SetValue("Difficulty", value.Value);
		}
	}

	internal static Size? CustomFieldSize
	{
		get
		{
			using var regKey = Registry.CurrentUser.OpenSubKey(settingsRegSubPath);
			var customFieldSizeX = int.Parse(regKey?.GetValue("CustomFieldSizeX")?.ToString() ?? "-1");
			var customFieldSizeY = int.Parse(regKey?.GetValue("CustomFieldSizeY")?.ToString() ?? "-1");

			if (customFieldSizeX < 0 && customFieldSizeY < 0)
			{
				return null;
			}

			return new(customFieldSizeX, customFieldSizeY);
		}

		set
		{
			if (value == null) return;

			using var regKey = Registry.CurrentUser.CreateSubKey(settingsRegSubPath);
			regKey.SetValue("CustomFieldSizeX", value.Value.Width);
			regKey.SetValue("CustomFieldSizeY", value.Value.Height);
		}
	}

	internal static int? CustomMineCount
	{
		get
		{
			using var regKey = Registry.CurrentUser.OpenSubKey(settingsRegSubPath);
			var customMineCount = int.Parse(regKey?.GetValue("CustomMineCount")?.ToString() ?? "-1");

			if (customMineCount < 0)
			{
				return null;
			}

			return customMineCount;
		}

		set
		{
			if (value == null) return;

			using var regKey = Registry.CurrentUser.CreateSubKey(settingsRegSubPath);
			regKey.SetValue("CustomMineCount", value.Value);
		}
	}
}

using Microsoft.Win32;

namespace Minesweeper;

internal static class Settings
{
	private const string c_regSubPath = @"SOFTWARE\FishNetSoft\Minesweeper";

	public static Point? MainWindowLocation
	{
		get
		{
			using var regKey = Registry.CurrentUser.OpenSubKey(c_regSubPath);
			var posXText = regKey?.GetValue("MainWindowPosX")?.ToString();
			var posYText = regKey?.GetValue("MainWindowPosY")?.ToString();

			if (posXText == null || posYText == null)
			{
				return null;
			}

			var posX = int.Parse(posXText);
			var posY = int.Parse(posYText);

			return new(posX, posY);
		}

		set
		{
			using var regKey = Registry.CurrentUser.CreateSubKey(c_regSubPath);
			regKey.SetValue("MainWindowPosX", value!.Value.X);
			regKey.SetValue("MainWindowPosY", value.Value.Y);
		}
	}
}

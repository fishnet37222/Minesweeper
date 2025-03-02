// Copyright (c) 2025 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

namespace Minesweeper;

public static class ColorExtension
{
	private static uint AlphaBlend(uint fg, uint bg, double alpha)
	{
		var result = bg + (alpha * (fg - bg));
		result = Math.Max(result, 0.0);
		result = Math.Min(result, 255.0);

		return (uint)result;
	}

	public static Color ChangeLightness(this Color color, int iAlpha)
	{
		if (iAlpha == 100) return color;

		iAlpha = Math.Max(iAlpha, 0);
		iAlpha = Math.Min(iAlpha, 200);

		var alpha = (double)iAlpha;

		uint bg;
		if (iAlpha > 100)
		{
			bg = 255;
			alpha = 1.0 - alpha;
		}
		else
		{
			bg = 0;
			alpha = 1.0 + alpha;
		}

		var r = AlphaBlend(color.R, bg, alpha);
		var g = AlphaBlend(color.G, bg, alpha);
		var b = AlphaBlend(color.B, bg, alpha);

		return Color.FromArgb(color.A, (byte)r, (byte)g, (byte)b);
	}
}

/* GraphicsExtension - [Extended Graphics]
 * Author name:           Arun Reginald Zaheeruddin
 * Current version:       1.0.0.4 (12b)
 * Release documentation: http://www.codeproject.com
 * License information:   Microsoft Public License (Ms-PL) [http://www.opensource.org/licenses/ms-pl.html]
 * 
 * Enhancements and history
 * ------------------------
 * 1.0.0.1 (20 Jul 2009): Initial release with modified code from previous CodeProject article.
 * 1.0.0.2 (25 Jul 2009): Added functionality that allows selected corners on a rectangle to be rounded.
 *                        Modified code to adapt to an anti-aliased output while drawing and filling rounded rectangles.
 * 1.0.0.3 (26 Jul 2009): Added DrawRoundedRectangle and FillRoundedRectangle methods that take a Rectangle and RectangleF object.
 * 1.0.0.4 (27 Jul 2009): Added font metrics and measuring utility that measures a font's height, leading, ascent, etc.
 * 
 * Issues addressed
 * ----------------
 * 1. Rounded rectangles - rounding edges of a rectangle.
 * 2. Font Metrics - Measuring a font's height, leading, ascent, etc.
 */

using System.Drawing.Drawing2D;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using JetBrains.Annotations;

[assembly: DisableRuntimeMarshalling]

namespace Minesweeper;

internal static partial class GraphicsExtension
{
	private static GraphicsPath GenerateRoundedRectangle(this Graphics graphics, RectangleF rectangle, float radius, RectangleEdgeFilter filter)
	{
		var path = new GraphicsPath();
		if (radius <= 0.0F || filter == RectangleEdgeFilter.None)
		{
			path.AddRectangle(rectangle);
			path.CloseFigure();
			return path;
		}

		if (radius >= (Math.Min(rectangle.Width, rectangle.Height)) / 2.0)
			return graphics.GenerateCapsule(rectangle);
		var diameter = radius * 2.0F;
		var sizeF = new SizeF(diameter, diameter);
		var arc = new RectangleF(rectangle.Location, sizeF);
		if ((RectangleEdgeFilter.TopLeft & filter) == RectangleEdgeFilter.TopLeft)
			path.AddArc(arc, 180, 90);
		else
		{
			path.AddLine(arc.X, arc.Y + arc.Height, arc.X, arc.Y);
			path.AddLine(arc.X, arc.Y, arc.X + arc.Width, arc.Y);
		}
		arc.X = rectangle.Right - diameter;
		if ((RectangleEdgeFilter.TopRight & filter) == RectangleEdgeFilter.TopRight)
			path.AddArc(arc, 270, 90);
		else
		{
			path.AddLine(arc.X, arc.Y, arc.X + arc.Width, arc.Y);
			path.AddLine(arc.X + arc.Width, arc.Y + arc.Height, arc.X + arc.Width, arc.Y);
		}
		arc.Y = rectangle.Bottom - diameter;
		if ((RectangleEdgeFilter.BottomRight & filter) == RectangleEdgeFilter.BottomRight)
			path.AddArc(arc, 0, 90);
		else
		{
			path.AddLine(arc.X + arc.Width, arc.Y, arc.X + arc.Width, arc.Y + arc.Height);
			path.AddLine(arc.X, arc.Y + arc.Height, arc.X + arc.Width, arc.Y + arc.Height);
		}
		arc.X = rectangle.Left;
		if ((RectangleEdgeFilter.BottomLeft & filter) == RectangleEdgeFilter.BottomLeft)
			path.AddArc(arc, 90, 90);
		else
		{
			path.AddLine(arc.X + arc.Width, arc.Y + arc.Height, arc.X, arc.Y + arc.Height);
			path.AddLine(arc.X, arc.Y + arc.Height, arc.X, arc.Y);
		}
		path.CloseFigure();
		return path;
	}

	private static GraphicsPath GenerateCapsule(this Graphics _, RectangleF rectangle)
	{
		var path = new GraphicsPath();
		try
		{
			float diameter;
			RectangleF arc;
			if (rectangle.Width > rectangle.Height)
			{
				diameter = rectangle.Height;
				var sizeF = new SizeF(diameter, diameter);
				arc = new RectangleF(rectangle.Location, sizeF);
				path.AddArc(arc, 90, 180);
				arc.X = rectangle.Right - diameter;
				path.AddArc(arc, 270, 180);
			}
			else if (rectangle.Width < rectangle.Height)
			{
				diameter = rectangle.Width;
				var sizeF = new SizeF(diameter, diameter);
				arc = new RectangleF(rectangle.Location, sizeF);
				path.AddArc(arc, 180, 180);
				arc.Y = rectangle.Bottom - diameter;
				path.AddArc(arc, 0, 180);
			}
			else path.AddEllipse(rectangle);
		}
		catch { path.AddEllipse(rectangle); }
		finally { path.CloseFigure(); }
		return path;
	}

	[PublicAPI]
	public static void DrawRoundedRectangle(this Graphics graphics, Pen pen, float x, float y, float width, float height, float radius, RectangleEdgeFilter filter)
	{
		var rectangle = new RectangleF(x, y, width, height);
		var path = graphics.GenerateRoundedRectangle(rectangle, radius, filter);
		var old = graphics.SmoothingMode;
		graphics.SmoothingMode = SmoothingMode.AntiAlias;
		graphics.DrawPath(pen, path);
		graphics.SmoothingMode = old;
	}

	[PublicAPI]
	public static void DrawRoundedRectangle(this Graphics graphics, Pen pen, float x, float y, float width, float height, float radius)
	{
		graphics.DrawRoundedRectangle(pen, x, y, width, height, radius, RectangleEdgeFilter.All);
	}

	[PublicAPI]
	public static void DrawRoundedRectangle(this Graphics graphics, Pen pen, int x, int y, int width, int height, int radius)
	{
		graphics.DrawRoundedRectangle(pen, Convert.ToSingle(x), Convert.ToSingle(y), Convert.ToSingle(width),
			Convert.ToSingle(height), Convert.ToSingle(radius));
	}

	[PublicAPI]
	public static void DrawRoundedRectangle(this Graphics graphics, Pen pen, Rectangle rectangle, int radius, RectangleEdgeFilter filter)
	{
		graphics.DrawRoundedRectangle(pen, rectangle.X, rectangle.Y, rectangle.Width, rectangle.Height, radius, filter);
	}

	[PublicAPI]
	public static void DrawRoundedRectangle(this Graphics graphics, Pen pen, Rectangle rectangle, int radius)
	{
		graphics.DrawRoundedRectangle(pen, rectangle.X, rectangle.Y, rectangle.Width, rectangle.Height, radius, RectangleEdgeFilter.All);
	}

	[PublicAPI]
	public static void DrawRoundedRectangle(this Graphics graphics, Pen pen, RectangleF rectangle, int radius, RectangleEdgeFilter filter)
	{
		graphics.DrawRoundedRectangle(pen, rectangle.X, rectangle.Y, rectangle.Width, rectangle.Height, radius, filter);
	}

	[PublicAPI]
	public static void DrawRoundedRectangle(this Graphics graphics, Pen pen, RectangleF rectangle, int radius)
	{
		graphics.DrawRoundedRectangle(pen, rectangle.X, rectangle.Y, rectangle.Width, rectangle.Height, radius, RectangleEdgeFilter.All);
	}

	[PublicAPI]
	public static void FillRoundedRectangle(this Graphics graphics, Brush brush, float x, float y, float width, float height, float radius, RectangleEdgeFilter filter)
	{
		var rectangle = new RectangleF(x, y, width, height);
		var path = graphics.GenerateRoundedRectangle(rectangle, radius, filter);
		var old = graphics.SmoothingMode;
		graphics.SmoothingMode = SmoothingMode.AntiAlias;
		graphics.FillPath(brush, path);
		graphics.SmoothingMode = old;
	}

	[PublicAPI]
	public static void FillRoundedRectangle(this Graphics graphics, Brush brush, float x, float y, float width, float height, float radius)
	{
		graphics.FillRoundedRectangle(brush, x, y, width, height, radius, RectangleEdgeFilter.All);
	}

	[PublicAPI]
	public static void FillRoundedRectangle(this Graphics graphics, Brush brush, int x, int y, int width, int height, int radius)
	{
		graphics.FillRoundedRectangle(brush, Convert.ToSingle(x), Convert.ToSingle(y), Convert.ToSingle(width),
			Convert.ToSingle(height), Convert.ToSingle(radius));
	}

	[PublicAPI]
	public static void FillRoundedRectangle(this Graphics graphics, Brush brush, Rectangle rectangle, int radius, RectangleEdgeFilter filter)
	{
		graphics.FillRoundedRectangle(brush, rectangle.X, rectangle.Y, rectangle.Width, rectangle.Height, radius, filter);
	}

	[PublicAPI]
	public static void FillRoundedRectangle(this Graphics graphics, Brush brush, Rectangle rectangle, int radius)
	{
		graphics.FillRoundedRectangle(brush, rectangle.X, rectangle.Y, rectangle.Width, rectangle.Height, radius, RectangleEdgeFilter.All);
	}

	[PublicAPI]
	public static void FillRoundedRectangle(this Graphics graphics, Brush brush, RectangleF rectangle, int radius, RectangleEdgeFilter filter)
	{
		graphics.FillRoundedRectangle(brush, rectangle.X, rectangle.Y, rectangle.Width, rectangle.Height, radius, filter);
	}

	[PublicAPI]
	public static void FillRoundedRectangle(this Graphics graphics, Brush brush, RectangleF rectangle, int radius)
	{
		graphics.FillRoundedRectangle(brush, rectangle.X, rectangle.Y, rectangle.Width, rectangle.Height, radius, RectangleEdgeFilter.All);
	}

	[PublicAPI]
	public static FontMetrics GetFontMetrics(this Graphics graphics, Font font)
	{
		return FontMetricsImpl.GetFontMetricsImpl(graphics, font);
	}

	private sealed partial class FontMetricsImpl : FontMetrics
	{
		[StructLayout(LayoutKind.Sequential)]
		public struct TextMetric
		{
			public int tmHeight;
			public int tmAscent;
			public int tmDescent;
			public int tmInternalLeading;
			public int tmExternalLeading;
			public int tmAveCharWidth;
			public int tmMaxCharWidth;
			public int tmWeight;
			public int tmOverhang;
			public int tmDigitizedAspectX;
			public int tmDigitizedAspectY;
			public char tmFirstChar;
			public char tmLastChar;
			public char tmDefaultChar;
			public char tmBreakChar;
			public byte tmItalic;
			public byte tmUnderlined;
			public byte tmStruckOut;
			public byte tmPitchAndFamily;
			public byte tmCharSet;
		}

		[LibraryImport("gdi32.dll")]
		private static partial IntPtr SelectObject(IntPtr hdc, IntPtr hgdiobj);

		[LibraryImport("gdi32.dll")]
		[return: MarshalAs(UnmanagedType.Bool)]
		private static partial bool GetTextMetrics(IntPtr hdc, out TextMetric lptm);

		[LibraryImport("gdi32.dll")]
		[return: MarshalAs(UnmanagedType.Bool)]
		private static partial bool DeleteObject(IntPtr hdc);

		private static TextMetric GenerateTextMetrics(Graphics graphics, Font font)
		{
			var hDc = IntPtr.Zero;
			TextMetric textMetric;
			var hFont = IntPtr.Zero;
			try
			{
				hDc = graphics.GetHdc();
				hFont = font.ToHfont();
				var hFontDefault = SelectObject(hDc, hFont);
				_ = GetTextMetrics(hDc, out textMetric);
				SelectObject(hDc, hFontDefault);
			}
			finally
			{
				if (hFont != IntPtr.Zero) _ = DeleteObject(hFont);
				if (hDc != IntPtr.Zero) graphics.ReleaseHdc(hDc);
			}
			return textMetric;
		}

		private readonly TextMetric m_metrics;

		public override int Height => m_metrics.tmHeight;
		public override int Ascent => m_metrics.tmAscent;
		public override int Descent => m_metrics.tmDescent;
		public override int InternalLeading => m_metrics.tmInternalLeading;
		public override int ExternalLeading => m_metrics.tmExternalLeading;
		public override int AverageCharacterWidth => m_metrics.tmAveCharWidth;
		public override int MaximumCharacterWidth => m_metrics.tmMaxCharWidth;
		public override int Weight => m_metrics.tmWeight;
		public override int Overhang => m_metrics.tmOverhang;
		public override int DigitizedAspectX => m_metrics.tmDigitizedAspectX;
		public override int DigitizedAspectY => m_metrics.tmDigitizedAspectY;

		private FontMetricsImpl(Graphics graphics, Font font)
		{
			m_metrics = GenerateTextMetrics(graphics, font);
		}

		public static FontMetrics GetFontMetricsImpl(Graphics graphics, Font font)
		{
			return new FontMetricsImpl(graphics, font);
		}
	}
}

[Flags]
public enum RectangleEdgeFilter
{
	None = 0,
	TopLeft = 1,
	TopRight = 2,
	BottomLeft = 4,
	BottomRight = 8,
	All = TopLeft | TopRight | BottomLeft | BottomRight
}

public abstract class FontMetrics
{
	[PublicAPI] public virtual int Height => 0;
	[PublicAPI] public virtual int Ascent => 0;
	[PublicAPI] public virtual int Descent => 0;
	[PublicAPI] public virtual int InternalLeading => 0;
	[PublicAPI] public virtual int ExternalLeading => 0;
	[PublicAPI] public virtual int AverageCharacterWidth => 0;
	[PublicAPI] public virtual int MaximumCharacterWidth => 0;
	[PublicAPI] public virtual int Weight => 0;
	[PublicAPI] public virtual int Overhang => 0;
	[PublicAPI] public virtual int DigitizedAspectX => 0;
	[PublicAPI] public virtual int DigitizedAspectY => 0;
}
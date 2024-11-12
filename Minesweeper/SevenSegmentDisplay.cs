// Copyright (c) 2024 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

using System.ComponentModel;
using System.Drawing.Drawing2D;
using JetBrains.Annotations;
using Microsoft.DotNet.DesignTools.Designers;

namespace Minesweeper;

[Designer(typeof(SevenSegmentDisplayDesigner)), PublicAPI]
public sealed partial class SevenSegmentDisplay : Control
{
	private enum Segment
	{
		Top,
		TopLeft,
		TopRight,
		Middle,
		BottomLeft,
		BottomRight,
		Bottom
	}

	private static Dictionary<char, List<Segment>> s_digitSegments = new()
	{
		{' ', [] },
		{'0', [Segment.Top, Segment.TopLeft, Segment.TopRight, Segment.BottomRight, Segment.BottomLeft, Segment.Bottom]},
		{'1', [Segment.TopRight, Segment.BottomRight]},
		{'2', [Segment.Top, Segment.TopRight, Segment.Middle, Segment.BottomLeft, Segment.Bottom]},
		{'3', [Segment.Top, Segment.TopRight, Segment.Middle, Segment.BottomRight, Segment.Bottom]},
		{'4', [Segment.TopLeft, Segment.TopRight, Segment.Middle, Segment.BottomRight]},
		{'5', [Segment.Top, Segment.TopLeft, Segment.Middle, Segment.BottomRight, Segment.Bottom]},
		{'6', [Segment.Top, Segment.TopLeft, Segment.Middle, Segment.BottomRight, Segment.BottomLeft, Segment.Bottom]},
		{'7', [Segment.Top, Segment.TopRight, Segment.BottomRight]},
		{'8', [Segment.Top, Segment.TopLeft, Segment.TopRight, Segment.Middle, Segment.BottomRight, Segment.BottomLeft, Segment.Bottom]},
		{'9', [Segment.Top, Segment.TopLeft, Segment.TopRight, Segment.Middle, Segment.BottomRight, Segment.Bottom]},
	};

	private int m_value;
	private int m_digitCount = 3;
	private int m_segmentThickness = 3;
	private int m_digitSpacing = 5;
	private Size m_digitSize = new(20, 40);
	private bool m_leadingZerosVisible;

	public SevenSegmentDisplay()
	{
		InitializeComponent();
		DoubleBuffered = true;
		BackColor = Color.Black;
		ForeColor = Color.Yellow;
	}

	[Category("Data"), DefaultValue(0)]
	public int Value
	{
		get => m_value;

		set
		{
			if (m_value == value) return;

			m_value = value;
			SetBoundsCore(Location.X, Location.Y, 0, 0, BoundsSpecified.Location);
			Refresh();
		}
	}

	[Category("Layout"), DefaultValue(3)]
	public int DigitCount
	{
		get => m_digitCount;

		set
		{
			if (m_digitCount == value) return;

			m_digitCount = value;
			SetBoundsCore(Location.X, Location.Y, 0, 0, BoundsSpecified.Location);
			Refresh();
		}
	}

	[Category("Appearance"), DefaultValue(3)]
	public int SegmentThickness
	{
		get => m_segmentThickness;


		set
		{
			if (m_segmentThickness == value) return;

			m_segmentThickness = value;
			Refresh();
		}
	}

	[Category("Layout"), DefaultValue(5)]
	public int DigitSpacing
	{
		get => m_digitSpacing;

		set
		{
			if (m_digitSpacing == value) return;

			m_digitSpacing = value;
			SetBoundsCore(Location.X, Location.Y, 0, 0, BoundsSpecified.Location);
			Refresh();
		}
	}


	[Category("Layout"), DefaultValue(typeof(Size), "20, 40")]
	public Size DigitSize
	{
		get => m_digitSize;

		set
		{
			if (m_digitSize == value) return;

			m_digitSize = value;
			SetBoundsCore(Location.X, Location.Y, 0, 0, BoundsSpecified.Location);
			Refresh();
		}
	}

	[Category("Appearance"), DefaultValue(false)]
	public bool LeadingZerosVisible
	{
		get => m_leadingZerosVisible;

		set
		{
			if (m_leadingZerosVisible == value) return;

			m_leadingZerosVisible = value;
			Refresh();
		}
	}

	protected override void OnPaint(PaintEventArgs e)
	{
		var g = e.Graphics;
		g.SmoothingMode = SmoothingMode.AntiAlias;

		g.FillRectangle(new SolidBrush(Parent!.BackColor), ClientRectangle);
		g.DrawRectangle(new(Parent!.BackColor), ClientRectangle);

		g.DrawRoundedRectangle(new(BackColor), ClientRectangle with { Width = Width - 1, Height = Height - 1 }, 4);
		g.FillRoundedRectangle(new SolidBrush(BackColor), ClientRectangle with { Width = Width - 1, Height = Height - 1 }, 4);

		var valueString = m_value.ToString();
		if (valueString.Length > m_digitCount)
		{
			valueString = valueString[^m_digitCount..];
		}
		else if (valueString.Length < m_digitCount)
		{
			// Left pad valueString until its length equals m_digitCount.
			valueString = valueString.PadLeft(m_digitCount, m_leadingZerosVisible ? '0' : ' ');
		}

		var litColor = ForeColor;
		var unlitColor = litColor.ChangeLightness(25);
		var halfHeight = m_digitSize.Height / 2;

		for (var i = 0; i < m_digitCount; i++)
		{
			var digit = valueString[i];
			var digitSegments = s_digitSegments[digit];
			var digitOriginX = m_digitSpacing + (m_digitSpacing + m_digitSize.Width) * i;
			var digitOriginY = m_digitSpacing;

			foreach (var segment in Enum.GetValues<Segment>())
			{
				var path = new GraphicsPath();

				switch (segment)
				{
					case Segment.Top:
					{
						var points = new List<Point>()
						{
							new(digitOriginX + 1, digitOriginY),
							new(digitOriginX + m_digitSize.Width - 1, digitOriginY),
							new(digitOriginX + m_digitSize.Width - m_segmentThickness - 1, digitOriginY + m_segmentThickness),
							new(digitOriginX + m_segmentThickness + 1, digitOriginY + m_segmentThickness)
						};
						path.AddPolygon(points.ToArray());

						break;
					}

					case Segment.TopLeft:
					{
						var points = new List<Point>()
						{
							new(digitOriginX, digitOriginY + 1),
							new(digitOriginX, digitOriginY + halfHeight - 1),
							new(digitOriginX + m_segmentThickness, digitOriginY + halfHeight - m_segmentThickness - 1),
							new(digitOriginX + m_segmentThickness, digitOriginY + m_segmentThickness + 1)
						};
						path.AddPolygon(points.ToArray());

						break;
					}

					case Segment.TopRight:
					{
						var points = new List<Point>()
						{
							new(digitOriginX + m_digitSize.Width, digitOriginY + 1),
							new(digitOriginX + m_digitSize.Width, digitOriginY + halfHeight - 1),
							new(digitOriginX + m_digitSize.Width - m_segmentThickness, digitOriginY + halfHeight - m_segmentThickness - 1),
							new(digitOriginX + m_digitSize.Width - m_segmentThickness, digitOriginY + m_segmentThickness + 1)
						};
						path.AddPolygon(points.ToArray());

						break;
					}

					case Segment.Middle:
					{
						var points = new List<Point>()
						{
							new(digitOriginX + 1, digitOriginY + halfHeight),
							new(digitOriginX + m_segmentThickness + 1, digitOriginY + halfHeight - m_segmentThickness + 1),
							new(digitOriginX + m_digitSize.Width - m_segmentThickness - 1, digitOriginY + halfHeight - m_segmentThickness + 1),
							new(digitOriginX + m_digitSize.Width - 1, digitOriginY + halfHeight),
							new(digitOriginX + m_digitSize.Width - m_segmentThickness - 1, digitOriginY + halfHeight + m_segmentThickness - 1),
							new(digitOriginX + m_segmentThickness + 1, digitOriginY + halfHeight + m_segmentThickness - 1)
						};
						path.AddPolygon(points.ToArray());

						break;
					}

					case Segment.BottomLeft:
					{
						var points = new List<Point>()
						{
							new(digitOriginX, digitOriginY + halfHeight + 1),
							new(digitOriginX, digitOriginY + m_digitSize.Height - 1),
							new(digitOriginX + m_segmentThickness, digitOriginY + m_digitSize.Height - m_segmentThickness - 1),
							new(digitOriginX + m_segmentThickness, digitOriginY + halfHeight + m_segmentThickness + 1)
						};
						path.AddPolygon(points.ToArray());

						break;
					}

					case Segment.BottomRight:
					{
						var points = new List<Point>()
						{
							new(digitOriginX + m_digitSize.Width, digitOriginY + halfHeight + 1),
							new(digitOriginX + m_digitSize.Width, digitOriginY + m_digitSize.Height - 1),
							new(digitOriginX + m_digitSize.Width - m_segmentThickness, digitOriginY + m_digitSize.Height - m_segmentThickness - 1),
							new(digitOriginX + m_digitSize.Width - m_segmentThickness, digitOriginY + halfHeight + m_segmentThickness + 1)
						};
						path.AddPolygon(points.ToArray());

						break;
					}

					case Segment.Bottom:
					{
						var points = new List<Point>()
						{
							new(digitOriginX + 1, digitOriginY + m_digitSize.Height),
							new(digitOriginX + m_digitSize.Width - 1, digitOriginY + m_digitSize.Height),
							new(digitOriginX + m_digitSize.Width - m_segmentThickness - 1, digitOriginY + m_digitSize.Height - m_segmentThickness),
							new(digitOriginX + m_segmentThickness + 1, digitOriginY + m_digitSize.Height - m_segmentThickness)
						};
						path.AddPolygon(points.ToArray());

						break;
					}
				}

				var color = digitSegments.Contains(segment) ? litColor : unlitColor;
				g.FillPath(new SolidBrush(color), path);
				g.DrawPath(new(color), path);
			}
		}
	}

	protected override void SetBoundsCore(int x, int y, int width, int height, BoundsSpecified specified)
	{
		width = m_digitSpacing * (m_digitCount + 1) + m_digitSize.Width * m_digitCount + 1;
		height = m_digitSpacing * 2 + m_digitSize.Height + 1;

		base.SetBoundsCore(x, y, width, height, BoundsSpecified.Size);
	}

	[DefaultValue(typeof(Color), nameof(Color.Black))]
	public override Color BackColor { get; set; }

	[DefaultValue(typeof(Color), nameof(Color.Yellow))]
	public override Color ForeColor { get; set; }
}

public class SevenSegmentDisplayDesigner : ControlDesigner
{
	public override SelectionRules SelectionRules => SelectionRules.Moveable | SelectionRules.Visible;
}

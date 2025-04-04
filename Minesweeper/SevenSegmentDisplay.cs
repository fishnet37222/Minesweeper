// Copyright (c) 2025 David A. Frischknecht
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

	private static readonly Dictionary<char, List<Segment>> digitSegmentDictionary = new()
	{
		{' ', [] },
		{'0', [Segment.Top, Segment.TopLeft, Segment.TopRight, Segment.BottomLeft, Segment.BottomRight, Segment.Bottom] },
		{'1', [Segment.TopRight, Segment.BottomRight] },
		{'2', [Segment.Top, Segment.TopRight, Segment.Middle, Segment.BottomLeft, Segment.Bottom] },
		{'3', [Segment.Top, Segment.TopRight, Segment.Middle, Segment.BottomRight, Segment.Bottom] },
		{'4', [Segment.TopLeft, Segment.Middle, Segment.TopRight, Segment.BottomRight] },
		{'5', [Segment.Top, Segment.TopLeft, Segment.Middle, Segment.BottomRight, Segment.Bottom] },
		{'6', [Segment.Top, Segment.TopLeft, Segment.BottomLeft, Segment.Bottom, Segment.BottomRight, Segment.Middle] },
		{'7', [Segment.Top, Segment.TopRight, Segment.BottomRight] },
		{'8', Enum.GetValues<Segment>().ToList() },
		{'9', [Segment.Bottom, Segment.BottomRight, Segment.TopRight, Segment.Top, Segment.TopLeft, Segment.Middle] },
	};

	private int value;
	private int digitCount = 3;
	private int digitSpacing = 5;
	private int segmentThickness = 3;
	private Size digitSize = new(20, 41);
	private bool leadingZerosVisible;

	public SevenSegmentDisplay()
	{
		InitializeComponent();
		DoubleBuffered = true;
		BackColor = Color.Black;
		ForeColor = Color.Yellow;
	}

	[DefaultValue(0), Category("Data")]
	public int Value
	{
		get => value;

		set
		{
			if (this.value == value) return;

			this.value = value;
			Refresh();
		}
	}

	[DefaultValue(3), Category("Layout")]
	public int DigitCount
	{
		get => digitCount;

		set
		{
			if (digitCount == value) return;

			digitCount = value;
			SetBoundsCore(0, 0, 0, 0, BoundsSpecified.None);
			Refresh();
		}
	}

	[DefaultValue(5), Category("Layout")]
	public int DigitSpacing
	{
		get => digitSpacing;

		set
		{
			if (digitSpacing == value) return;

			digitSpacing = value;
			SetBoundsCore(0, 0, 0, 0, BoundsSpecified.None);
			Refresh();
		}
	}

	[DefaultValue(3), Category("Appearance")]
	public int SegmentThickness
	{
		get => segmentThickness;

		set
		{
			if (segmentThickness == value) return;

			segmentThickness = value;
			Refresh();
		}
	}

	[DefaultValue(typeof(Size), "20,41"), Category("Layout")]
	public Size DigitSize
	{
		get => digitSize;

		set
		{
			if (digitSize == value) return;

			digitSize = value;
			SetBoundsCore(0, 0, 0, 0, BoundsSpecified.None);
			Refresh();
		}
	}

	[DefaultValue(false), Category("Appearance")]
	public bool LeadingZerosVisible
	{
		get => leadingZerosVisible;

		set
		{
			if (leadingZerosVisible == value) return;

			leadingZerosVisible = value;
			Refresh();
		}
	}

	[DefaultValue(typeof(Color), nameof(Color.Black))]
	public override Color BackColor { get; set; }

	[DefaultValue(typeof(Color), nameof(Color.Yellow))]
	public override Color ForeColor { get; set; }

	protected override void OnPaint(PaintEventArgs e)
	{
		var g = e.Graphics;
		g.SmoothingMode = SmoothingMode.AntiAlias;

		g.FillRectangle(new SolidBrush(Parent!.BackColor), ClientRectangle);
		g.DrawRectangle(new(Parent!.BackColor), ClientRectangle);

		g.FillRoundedRectangle(new SolidBrush(BackColor), ClientRectangle with { Width = Width - 1, Height = Height - 1 }, 4);
		g.DrawRoundedRectangle(new(BackColor), ClientRectangle with { Width = Width - 1, Height = Height - 1 }, 4);

		var valueText = value.ToString();

		if (valueText.Length > digitCount)
		{
			valueText = valueText[^digitCount..];
		}
		else if (valueText.Length < digitCount)
		{
			valueText = valueText.PadLeft(digitCount, leadingZerosVisible ? '0' : ' ');
		}

		var litColor = ForeColor;
		var unlitColor = litColor.ChangeLightness(20);
		var halfHeight = digitSize.Height / 2;

		for (var digitIndex = 0; digitIndex < digitCount; digitIndex++)
		{
			var digit = valueText[digitIndex];
			var digitSegments = digitSegmentDictionary[digit];

			var digitOriginX = digitSpacing + (digitSize.Width + digitSpacing) * digitIndex;
			var digitOriginY = digitSpacing;

			foreach (var segment in Enum.GetValues<Segment>())
			{
				var segmentPath = new GraphicsPath();

				// ReSharper disable once SwitchStatementHandlesSomeKnownEnumValuesWithDefault
				switch (segment)
				{
					case Segment.Top:
					{
						segmentPath.AddPolygon(
							new Point(digitOriginX + 1, digitOriginY),
							new(digitOriginX + digitSize.Width - 1, digitOriginY),
							new(digitOriginX + digitSize.Width - segmentThickness - 1, digitOriginY + segmentThickness),
							new(digitOriginX + segmentThickness + 1, digitOriginY + segmentThickness)
						);

						break;
					}

					case Segment.TopLeft:
					{
						segmentPath.AddPolygon(
							new Point(digitOriginX, digitOriginY + 1),
							new(digitOriginX, digitOriginY + halfHeight - 1),
							new(digitOriginX + segmentThickness, digitOriginY + halfHeight - segmentThickness - 1),
							new(digitOriginX + segmentThickness, digitOriginY + segmentThickness + 1)
						);

						break;
					}

					case Segment.TopRight:
					{
						segmentPath.AddPolygon(
							new Point(digitOriginX + digitSize.Width, digitOriginY + 1),
							new(digitOriginX + digitSize.Width, digitOriginY + halfHeight - 1),
							new(digitOriginX + digitSize.Width - segmentThickness, digitOriginY + halfHeight - segmentThickness - 1),
							new(digitOriginX + digitSize.Width - segmentThickness, digitOriginY + segmentThickness + 1)
						);

						break;
					}

					case Segment.Middle:
					{
						segmentPath.AddPolygon(
							new Point(digitOriginX + 1, digitOriginY + halfHeight),
							new(digitOriginX + segmentThickness, digitOriginY + halfHeight - segmentThickness + 1),
							new(digitOriginX + digitSize.Width - segmentThickness, digitOriginY + halfHeight - segmentThickness + 1),
							new(digitOriginX + digitSize.Width - 1, digitOriginY + halfHeight),
							new(digitOriginX + digitSize.Width - segmentThickness, digitOriginY + halfHeight + segmentThickness - 1),
							new(digitOriginX + segmentThickness, digitOriginY + halfHeight + segmentThickness - 1)
						);

						break;
					}

					case Segment.BottomLeft:
					{
						segmentPath.AddPolygon(
							new Point(digitOriginX, digitOriginY + halfHeight + 1),
							new(digitOriginX, digitOriginY + digitSize.Height - 1),
							new(digitOriginX + segmentThickness, digitOriginY + digitSize.Height - segmentThickness - 1),
							new(digitOriginX + segmentThickness, digitOriginY + halfHeight + segmentThickness + 1)
						);

						break;
					}

					case Segment.BottomRight:
					{
						segmentPath.AddPolygon(
							new Point(digitOriginX + digitSize.Width, digitOriginY + halfHeight + 1),
							new(digitOriginX + digitSize.Width, digitOriginY + digitSize.Height - 1),
							new(digitOriginX + digitSize.Width - segmentThickness, digitOriginY + digitSize.Height - segmentThickness - 1),
							new(digitOriginX + digitSize.Width - segmentThickness, digitOriginY + halfHeight + segmentThickness + 1)
						);

						break;
					}

					case Segment.Bottom:
					{
						segmentPath.AddPolygon(
							new Point(digitOriginX + 1, digitOriginY + digitSize.Height),
							new(digitOriginX + digitSize.Width - 1, digitOriginY + digitSize.Height),
							new(digitOriginX + digitSize.Width - segmentThickness - 1, digitOriginY + digitSize.Height - segmentThickness),
							new(digitOriginX + segmentThickness + 1, digitOriginY + digitSize.Height - segmentThickness)
						);

						break;
					}
				}

				var segmentColor = digitSegments.Contains(segment) ? litColor : unlitColor;
				g.FillPath(new SolidBrush(segmentColor), segmentPath);
				g.DrawPath(new(segmentColor), segmentPath);
			}
		}
	}

	protected override void SetBoundsCore(int x, int y, int width, int height, BoundsSpecified specified)
	{
		width = digitSpacing + (digitSize.Width + digitSpacing) * digitCount + 1;
		height = digitSpacing * 2 + digitSize.Height + 1;

		base.SetBoundsCore(x, y, width, height, BoundsSpecified.Size);
	}
}

public class SevenSegmentDisplayDesigner : ControlDesigner
{
	public override SelectionRules SelectionRules => SelectionRules.Moveable | SelectionRules.Visible;
}

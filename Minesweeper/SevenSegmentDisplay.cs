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

	private static readonly Dictionary<char, List<Segment>> s_digitSegmentMap = new()
	{
		{ ' ', [] },
		{
			'0',
			[Segment.Top, Segment.TopLeft, Segment.TopRight, Segment.BottomLeft, Segment.BottomRight, Segment.Bottom]
		},
		{
			'1',
			[Segment.TopRight, Segment.BottomRight]
		},
		{
			'2',
			[Segment.Top, Segment.TopRight, Segment.Middle, Segment.BottomLeft, Segment.Bottom]
		},
		{
			'3',
			[Segment.Top, Segment.TopRight, Segment.Middle, Segment.BottomRight, Segment.Bottom]
		},
		{
			'4',
			[Segment.TopLeft, Segment.TopRight, Segment.Middle, Segment.BottomRight]
		},
		{
			'5',
			[Segment.Top, Segment.TopLeft, Segment.Middle, Segment.BottomRight, Segment.Bottom]
		},
		{
			'6',
			[Segment.Top, Segment.TopLeft, Segment.Middle, Segment.BottomLeft, Segment.BottomRight, Segment.Bottom]
		},
		{
			'7',
			[Segment.Top, Segment.TopRight, Segment.BottomRight]
		},
		{
			'8',
			[Segment.Top, Segment.TopLeft, Segment.TopRight, Segment.Middle, Segment.BottomLeft, Segment.BottomRight, Segment.Bottom]
		},
		{
			'9',
			[Segment.Top, Segment.TopLeft, Segment.TopRight, Segment.Middle, Segment.BottomRight, Segment.Bottom]
		}
	};

	private int m_value;
	private int m_digitSpacing = 5;
	private int m_segmentThickness = 3;
	private Size m_digitSize = new(15, 30);
	private bool m_leadingZerosVisible;
	private int m_digitCount = 3;

	public SevenSegmentDisplay()
	{
		InitializeComponent();
		DoubleBuffered = true;
		BackColor = Color.Black;
		ForeColor = Color.Yellow;
	}

	[DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden), Browsable(false)]
	public int Value
	{
		get => m_value;

		set
		{
			if (m_value == value) return;

			m_value = value;
			Refresh();
		}
	}

	[DesignerSerializationVisibility(DesignerSerializationVisibility.Content), DefaultValue(5), Category("Layout")]
	public int DigitSpacing
	{
		get => m_digitSpacing;

		set
		{
			if (m_digitSpacing == value) return;

			m_digitSpacing = value;
			SetBoundsCore(0, 0, 0, 0, BoundsSpecified.None);
			Refresh();
		}
	}

	[DesignerSerializationVisibility(DesignerSerializationVisibility.Content), DefaultValue(3), Category("Appearance")]
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

	[DesignerSerializationVisibility(DesignerSerializationVisibility.Content), DefaultValue(typeof(Size), "15, 30"), Category("Layout")]
	public Size DigitSize
	{
		get => m_digitSize;

		set
		{
			if (m_digitSize == value) return;

			m_digitSize = value;
			SetBoundsCore(0, 0, 0, 0, BoundsSpecified.None);
			Refresh();
		}
	}

	[DesignerSerializationVisibility(DesignerSerializationVisibility.Content), DefaultValue(false), Category("Appearance")]
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

	[DesignerSerializationVisibility(DesignerSerializationVisibility.Content), DefaultValue(3), Category("Layout")]
	public int DigitCount
	{
		get => m_digitCount;

		set
		{
			if (m_digitCount == value) return;

			m_digitCount = value;
			SetBoundsCore(0, 0, 0, 0, BoundsSpecified.None);
			Refresh();
		}
	}

	[DesignerSerializationVisibility(DesignerSerializationVisibility.Content), DefaultValue(typeof(Color), nameof(Color.Black))]
	public override Color BackColor { get; set; }

	[DesignerSerializationVisibility(DesignerSerializationVisibility.Content), DefaultValue(typeof(Color), nameof(Color.Yellow))]
	public override Color ForeColor { get; set; }

	protected override void SetBoundsCore(int x, int y, int width, int height, BoundsSpecified specified)
	{
		width = m_digitSpacing * (m_digitCount + 1) + m_digitSize.Width * m_digitCount;
		height = m_digitSpacing * 2 + m_digitSize.Height;

		base.SetBoundsCore(x, y, width, height, BoundsSpecified.Size);
	}

	protected override void OnPaint(PaintEventArgs e)
	{
		var g = e.Graphics;

		g.SmoothingMode = SmoothingMode.AntiAlias;

		g.FillRectangle(new SolidBrush(Parent!.BackColor), 0, 0, ClientSize.Width - 1, ClientSize.Height - 1);
		g.DrawRectangle(new(Parent!.BackColor), 0, 0, ClientSize.Width - 1, ClientSize.Height - 1);

		g.DrawRoundedRectangle(new(BackColor), 0, 0, ClientSize.Width - 1, ClientSize.Height - 1, 5);
		g.FillRoundedRectangle(new SolidBrush(BackColor), 0, 0, ClientSize.Width - 1, ClientSize.Height - 1, 5);

		var valueText = m_value.ToString();

		if (valueText.Length > m_digitCount)
		{
			valueText = valueText[^m_digitCount..];
		}
		else if (valueText.Length < m_digitCount)
		{
			var padChar = m_leadingZerosVisible ? '0' : ' ';
			valueText = valueText.PadLeft(m_digitCount, padChar);
		}

		var litColor = ForeColor;
		var unlitColor = ForeColor.ChangeLightness(25);
		var halfHeight = m_digitSize.Height / 2;

		for (var i = 0; i < m_digitCount; i++)
		{
			var digit = valueText[i];
			var digitSegments = s_digitSegmentMap[digit];

			var digitOriginX = m_digitSpacing + (m_digitSpacing + m_digitSize.Width) * i;
			var digitOriginY = m_digitSpacing;

			foreach (var segment in Enum.GetValues<Segment>())
			{
				var path = new GraphicsPath();

				switch (segment)
				{
					case Segment.Top:
					{
						path.AddPolygon(new(digitOriginX + 1, digitOriginY),
							new(digitOriginX + m_digitSize.Width - 1, digitOriginY),
							new(digitOriginX + m_digitSize.Width - m_segmentThickness - 1, digitOriginY + m_segmentThickness),
							new(digitOriginX + m_segmentThickness + 1, digitOriginY + m_segmentThickness));

						break;
					}

					case Segment.TopLeft:
					{
						path.AddPolygon(new(digitOriginX, digitOriginY + 1),
							new(digitOriginX + m_segmentThickness, digitOriginY + m_segmentThickness + 1),
							new(digitOriginX + m_segmentThickness, digitOriginY + halfHeight - m_segmentThickness - 1),
							new(digitOriginX, digitOriginY + halfHeight - 1));

						break;
					}

					case Segment.TopRight:
					{
						path.AddPolygon(new(digitOriginX + m_digitSize.Width, digitOriginY + 1),
							new(digitOriginX + m_digitSize.Width - m_segmentThickness, digitOriginY + m_segmentThickness + 1),
							new(digitOriginX + m_digitSize.Width - m_segmentThickness, digitOriginY + halfHeight - m_segmentThickness - 1),
							new(digitOriginX + m_digitSize.Width, digitOriginY + halfHeight - 1));

						break;
					}

					case Segment.Middle:
					{
						path.AddPolygon(new(digitOriginX + 1, digitOriginY + halfHeight),
							new(digitOriginX + m_segmentThickness + 1, digitOriginY + halfHeight - m_segmentThickness),
							new(digitOriginX + m_digitSize.Width - m_segmentThickness - 1, digitOriginY + halfHeight - m_segmentThickness),
							new(digitOriginX + m_digitSize.Width - 1, digitOriginY + halfHeight),
							new(digitOriginX + m_digitSize.Width - m_segmentThickness - 1, digitOriginY + halfHeight + m_segmentThickness),
							new(digitOriginX + m_segmentThickness + 1, digitOriginY + halfHeight + m_segmentThickness));

						break;
					}

					case Segment.BottomLeft:
					{
						path.AddPolygon(new(digitOriginX, digitOriginY + halfHeight + 1),
							new(digitOriginX + m_segmentThickness, digitOriginY + halfHeight + m_segmentThickness + 1),
							new(digitOriginX + m_segmentThickness, digitOriginY + m_digitSize.Height - m_segmentThickness - 1),
							new(digitOriginX, digitOriginY + m_digitSize.Height - 1));

						break;
					}

					case Segment.BottomRight:
					{
						path.AddPolygon(new(digitOriginX + m_digitSize.Width, digitOriginY + halfHeight + 1),
							new(digitOriginX + m_digitSize.Width - m_segmentThickness, digitOriginY + halfHeight + m_segmentThickness + 1),
							new(digitOriginX + m_digitSize.Width - m_segmentThickness, digitOriginY + m_digitSize.Height - m_segmentThickness - 1),
							new(digitOriginX + m_digitSize.Width, digitOriginY + m_digitSize.Height - 1));

						break;
					}

					case Segment.Bottom:
					{
						path.AddPolygon(new(digitOriginX + 1, digitOriginY + m_digitSize.Height),
							new(digitOriginX + m_digitSize.Width - 1, digitOriginY + m_digitSize.Height),
							new(digitOriginX + m_digitSize.Width - m_segmentThickness - 1, digitOriginY + m_digitSize.Height - m_segmentThickness),
							new(digitOriginX + m_segmentThickness + 1, digitOriginY + m_digitSize.Height - m_segmentThickness));

						break;
					}
				}

				var color = digitSegments.Contains(segment) ? litColor : unlitColor;
				g.DrawPath(new(color), path);
				g.FillPath(new SolidBrush(color), path);
			}
		}
	}
}

public class SevenSegmentDisplayDesigner : ControlDesigner
{
	public override SelectionRules SelectionRules => SelectionRules.Moveable | SelectionRules.Visible;
}

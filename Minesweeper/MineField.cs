// Copyright (c) 2024 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

using System.ComponentModel;
using System.Drawing.Drawing2D;
using System.Security.Cryptography;
using JetBrains.Annotations;
using Microsoft.DotNet.DesignTools.Designers;
using Minesweeper.Properties;

#if DEBUG
using System.Diagnostics;
using System.Text;
#endif

namespace Minesweeper;

[PublicAPI]
public struct Cell()
{
	public bool IsMine { get; set; }

	public bool IsFlagged { get; set; }

	public bool IsRevealed { get; set; }

	public bool WasClicked { get; set; }

	public ushort AdjacentMineCount { get; set; } = 0;
}

[Designer(typeof(MineFieldDesigner)), PublicAPI]
public sealed partial class MineField : Control
{
	private Size m_cellSize = new(25, 25);
	private Size m_gridSize = new(9, 9);
	private Cell[,] m_cells = new Cell[9, 9];
	private List<Point> m_mineLocations;
	private int m_mineCount = 10;
	private Random m_random = new(RandomNumberGenerator.GetInt32(int.MinValue, int.MaxValue));

	public MineField()
	{
		InitializeComponent();
		DoubleBuffered = true;
		BackColor = Color.LightGray;
		ForeColor = Color.Black;
		m_mineLocations = [];
		InitializeGrid();
	}

	protected override void OnPaint(PaintEventArgs e)
	{
		base.OnPaint(e);

		var g = e.Graphics;
		g.SmoothingMode = SmoothingMode.AntiAlias;

		var shadowColor = BackColor.ChangeLightness(50);
		var highlightColor = BackColor.ChangeLightness(150);

		for (var cellY = 0; cellY < m_gridSize.Height; cellY++)
		{
			var cellOriginY = cellY * m_cellSize.Height;
			for (var cellX = 0; cellX < m_gridSize.Width; cellX++)
			{
				var cellOriginX = cellX * m_cellSize.Width;

				var cell = m_cells[cellX, cellY];

				if (!cell.IsRevealed)
				{
					for (var i = 0; i < 3; i++)
					{
						g.DrawLine(new(highlightColor), cellOriginX + i, cellOriginY + i,
							cellOriginX + m_cellSize.Width - i, cellOriginY + i);
						g.DrawLine(new(highlightColor), cellOriginX + i, cellOriginY + i, cellOriginX + i,
							cellOriginY + m_cellSize.Height - i);
						g.DrawLine(new(shadowColor), cellOriginX + i, cellOriginY + m_cellSize.Height - i,
							cellOriginX + m_cellSize.Width - i, cellOriginY + m_cellSize.Height - i);
						g.DrawLine(new(shadowColor), cellOriginX + m_cellSize.Width - i, cellOriginY + i,
							cellOriginX + m_cellSize.Width - i, cellOriginY + m_cellSize.Height - i);
					}

					if (cell.IsFlagged)
					{
						g.DrawImage(Resources.Flag, cellOriginX + 3, cellOriginY + 3, m_cellSize.Width - 6, m_cellSize.Height - 6);
					}
				}
				else
				{
					if (cell is { IsMine: true, WasClicked: true })
					{
						g.FillRectangle(new SolidBrush(Color.Red), cellOriginX, cellOriginY, m_cellSize.Width, m_cellSize.Height);
					}

					if (cell.IsMine)
					{
						g.DrawImage(Resources.Explosion, cellOriginX, cellOriginY, m_cellSize.Width, m_cellSize.Height);
					}
					else if (cell.AdjacentMineCount > 0)
					{
						var text = cell.AdjacentMineCount.ToString();
						var font = new Font(Font, FontStyle.Bold);
						var textSize = g.MeasureString(text, font);

						g.DrawString(text, font, new SolidBrush(ForeColor),
							cellOriginX + m_cellSize.Width / 2f - textSize.Width / 2,
							cellOriginY + m_cellSize.Height / 2f - textSize.Height / 2);
					}

					g.DrawRectangle(new(ForeColor), cellOriginX, cellOriginY, m_cellSize.Width, m_cellSize.Height);
				}
			}
		}
	}

	[Category("Layout"), DefaultValue(typeof(Size), "25, 25")]
	public Size CellSize
	{
		get => m_cellSize;

		set
		{
			if (m_cellSize == value) return;

			m_cellSize = value;
			SetBoundsCore(Location.X, Location.Y, 0, 0, BoundsSpecified.Location);
			Refresh();
		}
	}

	[Category("Layout"), DefaultValue(typeof(Size), "9, 9")]
	public Size GridSize
	{
		get => m_gridSize;

		set
		{
			if (m_gridSize == value) return;

			m_gridSize = value;
			SetBoundsCore(Location.X, Location.Y, 0, 0, BoundsSpecified.Location);
			InitializeGrid();
			Refresh();
		}
	}

	private void InitializeGrid()
	{
		m_cells = new Cell[m_gridSize.Width, m_gridSize.Height];
		m_mineLocations.Clear();

		for (var i = 0; i < m_mineCount; i++)
		{
			int x, y;
			do
			{
				x = m_random.Next(m_gridSize.Width);
				y = m_random.Next(m_gridSize.Height);
			} while (m_cells[x, y].IsMine);
			m_cells[x, y].IsMine = true;
			m_mineLocations.Add(new(x, y));

			for (var y1 = y - 1; y1 <= y + 1; y1++)
			{
				if (y1 < 0 || y1 >= m_gridSize.Height) continue;
				for (var x1 = x - 1; x1 <= x + 1; x1++)
				{
					if (x1 < 0 || x1 >= m_gridSize.Width) continue;
					if (x1 == x && y1 == y) continue;
					m_cells[x1, y1].AdjacentMineCount++;
				}
			}
		}

#if DEBUG
		// If we're currently running in the WinForms out-of-process designer, the process name will not be "Minesweeper".
		if (Process.GetCurrentProcess().ProcessName != "Minesweeper") return;
		var sb = new StringBuilder();
		for (var y1 = 0; y1 < m_gridSize.Height; y1++)
		{
			for (var x1 = 0; x1 < m_gridSize.Width; x1++)
			{
				sb.Append(m_cells[x1, y1].IsMine ? '*' : '-');
			}

			sb.AppendLine();
		}

		Debug.WriteLine(sb.ToString());
#endif
	}

	[DefaultValue(typeof(Color), nameof(Color.LightGray))]
	public override Color BackColor { get; set; }

	[DefaultValue(typeof(Color), nameof(Color.Black))]
	public override Color ForeColor { get; set; }

	protected override void SetBoundsCore(int x, int y, int width, int height, BoundsSpecified specified)
	{
		width = m_cellSize.Width * m_gridSize.Width + 1;
		height = m_cellSize.Height * m_gridSize.Height + 1;

		base.SetBoundsCore(x, y, width, height, BoundsSpecified.Size);
	}

	protected override void OnMouseClick(MouseEventArgs e)
	{
		base.OnMouseClick(e);

		var cellX = e.Location.X / m_cellSize.Width;
		var cellY = e.Location.Y / m_cellSize.Height;

		switch (e.Button)
		{
			case MouseButtons.Right:
			{
				m_cells[cellX, cellY].IsFlagged = !m_cells[cellX, cellY].IsFlagged;
				break;
			}

			case MouseButtons.Left:
			{
				if (m_cells[cellX, cellY].IsFlagged || m_cells[cellX, cellY].IsRevealed) return;
				RevealCells(new(cellX, cellY));
				break;
			}

			case MouseButtons.Middle:
			case MouseButtons.None:
			case MouseButtons.XButton1:
			case MouseButtons.XButton2:
			default:
				break;
		}

		Refresh();
	}

	protected override void OnMouseDown(MouseEventArgs e)
	{
		base.OnMouseDown(e);
		Capture = true;
	}

	protected override void OnMouseUp(MouseEventArgs e)
	{
		base.OnMouseUp(e);
		Capture = false;
	}

	protected override void OnMouseDoubleClick(MouseEventArgs e)
	{
		base.OnMouseDoubleClick(e);

		var cellX = e.Location.X / m_cellSize.Width;
		var cellY = e.Location.Y / m_cellSize.Height;

		if (!m_cells[cellX, cellY].IsRevealed) return;

		var adjacentFlagCount = 0;
		for (var y = cellY - 1; y <= cellY + 1; y++)
		{
			if (y < 0 || y >= m_gridSize.Height) continue;
			for (var x = cellX - 1; x <= cellX + 1; x++)
			{
				if (x < 0 || x >= m_gridSize.Width) continue;
				if (x == cellX && y == cellY) continue;
				if (m_cells[x, y].IsFlagged) adjacentFlagCount++;
			}
		}

		if (adjacentFlagCount != m_cells[cellX, cellY].AdjacentMineCount) return;

		for (var y = cellY - 1; y <= cellY + 1; y++)
		{
			if (y < 0 || y >= m_gridSize.Height) continue;
			for (var x = cellX - 1; x <= cellX + 1; x++)
			{
				if (x < 0 || x >= m_gridSize.Width) continue;
				if (x == cellX && y == cellY) continue;
				if (m_cells[x, y].IsRevealed || m_cells[x, y].IsFlagged) continue;
				RevealCells(new(x, y));
			}
		}

		Refresh();
	}

	private void RevealCells(Point startingCellLocation)
	{
		var cellsToReveal = new Stack<Point>();
		cellsToReveal.Push(startingCellLocation);

		var mineRevealed = false;

		while (cellsToReveal.Count > 0)
		{
			var cellToReveal = cellsToReveal.Pop();

			m_cells[cellToReveal.X, cellToReveal.Y].IsRevealed = true;
			if (m_cells[cellToReveal.X, cellToReveal.Y].IsMine)
			{
				mineRevealed = true;
				m_cells[cellToReveal.X, cellToReveal.Y].WasClicked = true;
				break;
			}

			if (m_cells[cellToReveal.X, cellToReveal.Y].AdjacentMineCount > 0) continue;

			for (var y = cellToReveal.Y - 1; y <= cellToReveal.Y + 1; y++)
			{
				if (y < 0 || y >= m_gridSize.Height) continue;
				for (var x = cellToReveal.X - 1; x <= cellToReveal.X + 1; x++)
				{
					if (x < 0 || x >= m_gridSize.Width) continue;
					if (x == cellToReveal.X && y == cellToReveal.Y) continue;
					if (m_cells[x, y].IsRevealed || m_cells[x, y].IsFlagged) continue;
					cellsToReveal.Push(new(x, y));
				}
			}
		}

		if (!mineRevealed) return;

		foreach (var mineLocation in m_mineLocations)
		{
			m_cells[mineLocation.X, mineLocation.Y].IsRevealed = true;
		}
	}
}

public class MineFieldDesigner : ControlDesigner
{
	public override SelectionRules SelectionRules => SelectionRules.Moveable | SelectionRules.Visible;
}

// Copyright (c) 2024 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

using Minesweeper.Properties;

namespace Minesweeper;

public partial class MainWindow : Form
{
	public MainWindow()
	{
		InitializeComponent();
		CalculateDesiredClientSize();
	}

	private void MineField_Resize(object sender, EventArgs e)
	{
		CalculateDesiredClientSize();
	}

	private void CalculateDesiredClientSize()
	{
		var minDesiredUpperClientWidth = m_ssdMinesLeft.Left * 2 + m_ssdMinesLeft.Width + 5 + m_btnNewGame.Width + 5 +
										 m_ssdElapsedTime.Width;
		var minDesiredLowerClientWidth = m_ssdMinesLeft.Left * 2 + m_mineField.Width;

		var desiredClientWidth = Math.Max(minDesiredUpperClientWidth, minDesiredLowerClientWidth);
		var desiredClientHeight = m_mineField.Bottom + m_ssdMinesLeft.Left;

		ClientSize = new(desiredClientWidth, desiredClientHeight);
	}

	private void MineField_MouseDown(object sender, MouseEventArgs e)
	{
		if (e.Button != MouseButtons.Left) return;
		m_btnNewGame.Image = Resources.Smile4;
	}

	private void MineField_MouseUp(object sender, MouseEventArgs e)
	{
		if (e.Button != MouseButtons.Left) return;
		m_btnNewGame.Image = Resources.Smile1;
	}
}

// Copyright (c) 2024 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

using Minesweeper.Properties;

namespace Minesweeper;

public partial class MainWindow : Form
{
	private Difficulty m_difficulty = Difficulty.Beginner;
	private Size m_customFieldSize = new(9, 9);
	private int m_customMineCount = 10;

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

	private void MainWindow_Load(object sender, EventArgs e)
	{
		var location = Settings.MainWindowLocation;

		if (location == null)
		{
			var workingArea = Screen.FromControl(this).WorkingArea;
			var locationX = workingArea.Width / 2 - Width / 2;
			var locationY = workingArea.Height / 2 - Height / 2;
			location = new(locationX, locationY);
		}

		Location = location.Value;

		m_difficulty = Settings.Difficulty ?? Difficulty.Beginner;
		// ReSharper disable once SwitchStatementHandlesSomeKnownEnumValuesWithDefault
		switch (m_difficulty)
		{
			case Difficulty.Beginner:
			{
				beginnerToolStripMenuItem.Checked = true;
				break;
			}

			case Difficulty.Intermediate:
			{
				intermediateToolStripMenuItem.Checked = true;
				break;
			}

			case Difficulty.Expert:
			{
				expertToolStripMenuItem.Checked = true;
				break;
			}

			case Difficulty.Custom:
			{
				customToolStripMenuItem.Checked = true;
				m_customFieldSize = Settings.CustomFieldSize ?? new(9, 9);
				m_customMineCount = Settings.CustomMineCount ?? 10;
				break;
			}
		}
	}

	private void MainWindow_FormClosing(object sender, FormClosingEventArgs e)
	{
		Settings.MainWindowLocation = Location;
		Settings.Difficulty = m_difficulty;
		Settings.CustomFieldSize = m_customFieldSize;
		Settings.CustomMineCount = m_customMineCount;
	}

	private void BeginnerToolStripMenuItem_Click(object sender, EventArgs e)
	{
		UncheckDifficultyMenuItems();
		m_difficulty = Difficulty.Beginner;
		beginnerToolStripMenuItem.Checked = true;
	}

	private void IntermediateToolStripMenuItem_Click(object sender, EventArgs e)
	{
		UncheckDifficultyMenuItems();
		m_difficulty = Difficulty.Intermediate;
		intermediateToolStripMenuItem.Checked = true;
	}

	private void ExpertToolStripMenuItem_Click(object sender, EventArgs e)
	{
		UncheckDifficultyMenuItems();
		m_difficulty = Difficulty.Expert;
		expertToolStripMenuItem.Checked = true;
	}

	private void CustomToolStripMenuItem_Click(object sender, EventArgs e)
	{
		var dlg = new CustomDifficultyDialog();
		dlg.CustomFieldWidth = m_customFieldSize.Width;
		dlg.CustomFieldHeight = m_customFieldSize.Height;
		dlg.CustomMineCount = m_customMineCount;
		var result = dlg.ShowDialog(this);

		if (result == DialogResult.Cancel) return;

		UncheckDifficultyMenuItems();
		m_difficulty = Difficulty.Custom;
		customToolStripMenuItem.Checked = true;
		m_customFieldSize = new(dlg.CustomFieldWidth, dlg.CustomFieldHeight);
		m_customMineCount = dlg.CustomMineCount;
	}

	private void UncheckDifficultyMenuItems()
	{
		beginnerToolStripMenuItem.Checked = false;
		intermediateToolStripMenuItem.Checked = false;
		expertToolStripMenuItem.Checked = false;
		customToolStripMenuItem.Checked = false;
	}

	private void ExitToolStripMenuItem_Click(object sender, EventArgs e)
	{
		Close();
	}
}

// Copyright (c) 2025 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

namespace Minesweeper;

public partial class MainWindow : Form
{
	public MainWindow()
	{
		InitializeComponent();
	}

	private void ExitToolStripMenuItem_Click(object sender, EventArgs e)
	{
		Close();
	}

	private void MainWindow_Load(object sender, EventArgs e)
	{
		var location = Settings.MainWindowLocation;

		if (location == null)
		{
			var workArea = Screen.FromControl(this).WorkingArea;

			var x = workArea.Width / 2 - Width / 2;
			var y = workArea.Height / 2 - Height / 2;

			location = new(x, y);
		}

		Location = location.Value;
	}

	private void MainWindow_FormClosing(object sender, FormClosingEventArgs e)
	{
		Settings.MainWindowLocation = Location;
	}
}

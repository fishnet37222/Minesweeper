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

	private void MainWindow_Load(object sender, EventArgs e)
	{
		var workArea = Screen.FromControl(this).WorkingArea;

		var posX = workArea.Width / 2 - Width / 2;
		var posY = workArea.Height / 2 - Height / 2;

		Location = new(posX, posY);
	}
}
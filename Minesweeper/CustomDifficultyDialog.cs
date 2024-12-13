// Copyright (c) 2024 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

using System.ComponentModel;

namespace Minesweeper;

internal partial class CustomDifficultyDialog : Form
{
	public CustomDifficultyDialog()
	{
		InitializeComponent();
	}

	[Browsable(false), DefaultValue(9)]
	internal int CustomFieldWidth { get; set; } = 9;

	[Browsable(false), DefaultValue(9)]
	internal int CustomFieldHeight { get; set; } = 9;

	[Browsable(false), DefaultValue(10)]
	internal int CustomMineCount { get; set; } = 10;

	private void CustomDifficultyDialog_Load(object sender, EventArgs e)
	{
		m_txtWidth.Text = CustomFieldWidth.ToString();
		m_txtHeight.Text = CustomFieldHeight.ToString();
		m_txtMines.Text = CustomMineCount.ToString();
	}

	private void m_btnOK_Click(object sender, EventArgs e)
	{
		var okToClose = true;

		if (int.TryParse(m_txtWidth.Text, out var width))
		{
			CustomFieldWidth = width;
		}
		else
		{
			okToClose = false;
		}

		if (int.TryParse(m_txtHeight.Text, out var height))
		{
			CustomFieldHeight = height;
		}
		else
		{
			okToClose = false;
		}

		if (int.TryParse(m_txtMines.Text, out var mineCount))
		{
			CustomMineCount = mineCount;
		}
		else
		{
			okToClose = false;
		}

		if (okToClose)
		{
			Close();
		}
	}
}

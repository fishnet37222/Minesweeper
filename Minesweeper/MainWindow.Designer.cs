// Copyright (c) 2024 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

namespace Minesweeper;

partial class MainWindow
{
	private System.ComponentModel.IContainer components = null;

	protected override void Dispose(bool disposing)
	{
		if (disposing && (components != null))
		{
			components.Dispose();
		}
		base.Dispose(disposing);
	}

	#region Windows Form Designer generated code

	/// <summary>
	///  Required method for Designer support - do not modify
	///  the contents of this method with the code editor.
	/// </summary>
	private void InitializeComponent()
	{
		MenuStrip m_menuStrip;
		ToolStripMenuItem gameToolStripMenuItem;
		ToolStripSeparator toolStripMenuItem1;
		ToolStripSeparator toolStripMenuItem2;
		ToolStripSeparator toolStripMenuItem3;
		ToolStripMenuItem helpToolStripMenuItem;
		ToolStripSeparator toolStripMenuItem4;
		var resources = new System.ComponentModel.ComponentResourceManager(typeof(MainWindow));
		this.newToolStripMenuItem = new ToolStripMenuItem();
		this.beginnerToolStripMenuItem = new ToolStripMenuItem();
		this.intermediateToolStripMenuItem = new ToolStripMenuItem();
		this.expertToolStripMenuItem = new ToolStripMenuItem();
		this.customToolStripMenuItem = new ToolStripMenuItem();
		this.bestTimesToolStripMenuItem = new ToolStripMenuItem();
		this.exitToolStripMenuItem = new ToolStripMenuItem();
		this.howToPlayToolStripMenuItem = new ToolStripMenuItem();
		this.aboutMinesweeperToolStripMenuItem = new ToolStripMenuItem();
		this.m_btnNewGame = new Button();
		this.m_ssdMinesLeft = new SevenSegmentDisplay();
		this.m_ssdElapsedTime = new SevenSegmentDisplay();
		this.m_mineField = new MineField();
		m_menuStrip = new MenuStrip();
		gameToolStripMenuItem = new ToolStripMenuItem();
		toolStripMenuItem1 = new ToolStripSeparator();
		toolStripMenuItem2 = new ToolStripSeparator();
		toolStripMenuItem3 = new ToolStripSeparator();
		helpToolStripMenuItem = new ToolStripMenuItem();
		toolStripMenuItem4 = new ToolStripSeparator();
		m_menuStrip.SuspendLayout();
		this.SuspendLayout();
		// 
		// m_menuStrip
		// 
		m_menuStrip.Items.AddRange(new ToolStripItem[] { gameToolStripMenuItem, helpToolStripMenuItem });
		m_menuStrip.Location = new Point(0, 0);
		m_menuStrip.Name = "m_menuStrip";
		m_menuStrip.RenderMode = ToolStripRenderMode.System;
		m_menuStrip.Size = new Size(800, 24);
		m_menuStrip.TabIndex = 0;
		m_menuStrip.Text = "menuStrip1";
		// 
		// gameToolStripMenuItem
		// 
		gameToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[] { this.newToolStripMenuItem, toolStripMenuItem1, this.beginnerToolStripMenuItem, this.intermediateToolStripMenuItem, this.expertToolStripMenuItem, this.customToolStripMenuItem, toolStripMenuItem2, this.bestTimesToolStripMenuItem, toolStripMenuItem3, this.exitToolStripMenuItem });
		gameToolStripMenuItem.Name = "gameToolStripMenuItem";
		gameToolStripMenuItem.Size = new Size(50, 20);
		gameToolStripMenuItem.Text = "&Game";
		// 
		// newToolStripMenuItem
		// 
		this.newToolStripMenuItem.Name = "newToolStripMenuItem";
		this.newToolStripMenuItem.ShortcutKeys = Keys.F2;
		this.newToolStripMenuItem.Size = new Size(180, 22);
		this.newToolStripMenuItem.Text = "&New";
		// 
		// toolStripMenuItem1
		// 
		toolStripMenuItem1.Name = "toolStripMenuItem1";
		toolStripMenuItem1.Size = new Size(177, 6);
		// 
		// beginnerToolStripMenuItem
		// 
		this.beginnerToolStripMenuItem.Name = "beginnerToolStripMenuItem";
		this.beginnerToolStripMenuItem.Size = new Size(180, 22);
		this.beginnerToolStripMenuItem.Text = "&Beginner";
		this.beginnerToolStripMenuItem.Click += this.BeginnerToolStripMenuItem_Click;
		// 
		// intermediateToolStripMenuItem
		// 
		this.intermediateToolStripMenuItem.Name = "intermediateToolStripMenuItem";
		this.intermediateToolStripMenuItem.Size = new Size(180, 22);
		this.intermediateToolStripMenuItem.Text = "&Intermediate";
		this.intermediateToolStripMenuItem.Click += this.IntermediateToolStripMenuItem_Click;
		// 
		// expertToolStripMenuItem
		// 
		this.expertToolStripMenuItem.Name = "expertToolStripMenuItem";
		this.expertToolStripMenuItem.Size = new Size(180, 22);
		this.expertToolStripMenuItem.Text = "&Expert";
		this.expertToolStripMenuItem.Click += this.ExpertToolStripMenuItem_Click;
		// 
		// customToolStripMenuItem
		// 
		this.customToolStripMenuItem.Name = "customToolStripMenuItem";
		this.customToolStripMenuItem.Size = new Size(180, 22);
		this.customToolStripMenuItem.Text = "&Custom...";
		this.customToolStripMenuItem.Click += this.CustomToolStripMenuItem_Click;
		// 
		// toolStripMenuItem2
		// 
		toolStripMenuItem2.Name = "toolStripMenuItem2";
		toolStripMenuItem2.Size = new Size(177, 6);
		// 
		// bestTimesToolStripMenuItem
		// 
		this.bestTimesToolStripMenuItem.Name = "bestTimesToolStripMenuItem";
		this.bestTimesToolStripMenuItem.Size = new Size(180, 22);
		this.bestTimesToolStripMenuItem.Text = "Best &Times...";
		// 
		// toolStripMenuItem3
		// 
		toolStripMenuItem3.Name = "toolStripMenuItem3";
		toolStripMenuItem3.Size = new Size(177, 6);
		// 
		// exitToolStripMenuItem
		// 
		this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
		this.exitToolStripMenuItem.Size = new Size(180, 22);
		this.exitToolStripMenuItem.Text = "E&xit";
		this.exitToolStripMenuItem.Click += this.ExitToolStripMenuItem_Click;
		// 
		// helpToolStripMenuItem
		// 
		helpToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[] { this.howToPlayToolStripMenuItem, toolStripMenuItem4, this.aboutMinesweeperToolStripMenuItem });
		helpToolStripMenuItem.Name = "helpToolStripMenuItem";
		helpToolStripMenuItem.Size = new Size(44, 20);
		helpToolStripMenuItem.Text = "&Help";
		// 
		// howToPlayToolStripMenuItem
		// 
		this.howToPlayToolStripMenuItem.Name = "howToPlayToolStripMenuItem";
		this.howToPlayToolStripMenuItem.Size = new Size(180, 22);
		this.howToPlayToolStripMenuItem.Text = "&How to Play";
		// 
		// toolStripMenuItem4
		// 
		toolStripMenuItem4.Name = "toolStripMenuItem4";
		toolStripMenuItem4.Size = new Size(177, 6);
		// 
		// aboutMinesweeperToolStripMenuItem
		// 
		this.aboutMinesweeperToolStripMenuItem.Name = "aboutMinesweeperToolStripMenuItem";
		this.aboutMinesweeperToolStripMenuItem.Size = new Size(180, 22);
		this.aboutMinesweeperToolStripMenuItem.Text = "&About Minesweeper";
		// 
		// m_btnNewGame
		// 
		this.m_btnNewGame.Anchor = AnchorStyles.Top;
		this.m_btnNewGame.AutoSize = true;
		this.m_btnNewGame.AutoSizeMode = AutoSizeMode.GrowAndShrink;
		this.m_btnNewGame.Image = Properties.Resources.Smile1;
		this.m_btnNewGame.Location = new Point(378, 30);
		this.m_btnNewGame.Name = "m_btnNewGame";
		this.m_btnNewGame.Padding = new Padding(3);
		this.m_btnNewGame.Size = new Size(44, 44);
		this.m_btnNewGame.TabIndex = 1;
		this.m_btnNewGame.UseVisualStyleBackColor = true;
		// 
		// m_ssdMinesLeft
		// 
		this.m_ssdMinesLeft.Location = new Point(12, 27);
		this.m_ssdMinesLeft.Name = "m_ssdMinesLeft";
		this.m_ssdMinesLeft.Size = new Size(81, 51);
		this.m_ssdMinesLeft.TabIndex = 2;
		this.m_ssdMinesLeft.Text = "sevenSegmentDisplay1";
		// 
		// m_ssdElapsedTime
		// 
		this.m_ssdElapsedTime.Anchor = AnchorStyles.Top | AnchorStyles.Right;
		this.m_ssdElapsedTime.Location = new Point(707, 27);
		this.m_ssdElapsedTime.Name = "m_ssdElapsedTime";
		this.m_ssdElapsedTime.Size = new Size(81, 51);
		this.m_ssdElapsedTime.TabIndex = 3;
		this.m_ssdElapsedTime.Text = "sevenSegmentDisplay2";
		// 
		// m_mineField
		// 
		this.m_mineField.Anchor = AnchorStyles.Top;
		this.m_mineField.Location = new Point(287, 84);
		this.m_mineField.Name = "m_mineField";
		this.m_mineField.Size = new Size(226, 226);
		this.m_mineField.TabIndex = 4;
		this.m_mineField.Text = "mineField1";
		this.m_mineField.MouseDown += this.MineField_MouseDown;
		this.m_mineField.MouseUp += this.MineField_MouseUp;
		this.m_mineField.Resize += this.MineField_Resize;
		// 
		// MainWindow
		// 
		this.AutoScaleDimensions = new SizeF(7F, 15F);
		this.AutoScaleMode = AutoScaleMode.Font;
		this.ClientSize = new Size(800, 450);
		this.Controls.Add(this.m_mineField);
		this.Controls.Add(this.m_ssdElapsedTime);
		this.Controls.Add(this.m_ssdMinesLeft);
		this.Controls.Add(this.m_btnNewGame);
		this.Controls.Add(m_menuStrip);
		this.FormBorderStyle = FormBorderStyle.FixedSingle;
		this.Icon = (Icon)resources.GetObject("$this.Icon");
		this.MainMenuStrip = m_menuStrip;
		this.MaximizeBox = false;
		this.Name = "MainWindow";
		this.Text = "Minesweeper";
		this.FormClosing += this.MainWindow_FormClosing;
		this.Load += this.MainWindow_Load;
		m_menuStrip.ResumeLayout(false);
		m_menuStrip.PerformLayout();
		this.ResumeLayout(false);
		this.PerformLayout();
	}

	#endregion

	private ToolStripMenuItem newToolStripMenuItem;
	private ToolStripMenuItem beginnerToolStripMenuItem;
	private ToolStripMenuItem intermediateToolStripMenuItem;
	private ToolStripMenuItem expertToolStripMenuItem;
	private ToolStripMenuItem customToolStripMenuItem;
	private ToolStripMenuItem bestTimesToolStripMenuItem;
	private ToolStripMenuItem exitToolStripMenuItem;
	private ToolStripMenuItem howToPlayToolStripMenuItem;
	private ToolStripMenuItem aboutMinesweeperToolStripMenuItem;
	private Button m_btnNewGame;
	private SevenSegmentDisplay m_ssdMinesLeft;
	private SevenSegmentDisplay m_ssdElapsedTime;
	private MineField m_mineField;
}
// Copyright (c) 2025 David A. Frischknecht
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

	private void InitializeComponent()
	{
		MenuStrip menuStrip;
		ToolStripMenuItem gameToolStripMenuItem;
		ToolStripSeparator toolStripMenuItem2;
		ToolStripSeparator toolStripMenuItem3;
		ToolStripSeparator toolStripMenuItem4;
		ToolStripMenuItem helpToolStripMenuItem;
		ToolStripSeparator toolStripMenuItem1;
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
		this.btnNewGame = new Button();
		this.ssdMinesLeft = new SevenSegmentDisplay();
		this.ssdElapsedTime = new SevenSegmentDisplay();
		menuStrip = new MenuStrip();
		gameToolStripMenuItem = new ToolStripMenuItem();
		toolStripMenuItem2 = new ToolStripSeparator();
		toolStripMenuItem3 = new ToolStripSeparator();
		toolStripMenuItem4 = new ToolStripSeparator();
		helpToolStripMenuItem = new ToolStripMenuItem();
		toolStripMenuItem1 = new ToolStripSeparator();
		menuStrip.SuspendLayout();
		this.SuspendLayout();
		// 
		// menuStrip
		// 
		menuStrip.Items.AddRange(new ToolStripItem[] { gameToolStripMenuItem, helpToolStripMenuItem });
		menuStrip.Location = new Point(0, 0);
		menuStrip.Name = "menuStrip";
		menuStrip.RenderMode = ToolStripRenderMode.System;
		menuStrip.Size = new Size(800, 24);
		menuStrip.TabIndex = 0;
		menuStrip.Text = "menuStrip1";
		// 
		// gameToolStripMenuItem
		// 
		gameToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[] { this.newToolStripMenuItem, toolStripMenuItem2, this.beginnerToolStripMenuItem, this.intermediateToolStripMenuItem, this.expertToolStripMenuItem, this.customToolStripMenuItem, toolStripMenuItem3, this.bestTimesToolStripMenuItem, toolStripMenuItem4, this.exitToolStripMenuItem });
		gameToolStripMenuItem.Name = "gameToolStripMenuItem";
		gameToolStripMenuItem.Size = new Size(50, 20);
		gameToolStripMenuItem.Text = "&Game";
		// 
		// newToolStripMenuItem
		// 
		this.newToolStripMenuItem.Name = "newToolStripMenuItem";
		this.newToolStripMenuItem.ShortcutKeys = Keys.F2;
		this.newToolStripMenuItem.Size = new Size(141, 22);
		this.newToolStripMenuItem.Text = "&New";
		// 
		// toolStripMenuItem2
		// 
		toolStripMenuItem2.Name = "toolStripMenuItem2";
		toolStripMenuItem2.Size = new Size(138, 6);
		// 
		// beginnerToolStripMenuItem
		// 
		this.beginnerToolStripMenuItem.Name = "beginnerToolStripMenuItem";
		this.beginnerToolStripMenuItem.Size = new Size(141, 22);
		this.beginnerToolStripMenuItem.Text = "&Beginner";
		// 
		// intermediateToolStripMenuItem
		// 
		this.intermediateToolStripMenuItem.Name = "intermediateToolStripMenuItem";
		this.intermediateToolStripMenuItem.Size = new Size(141, 22);
		this.intermediateToolStripMenuItem.Text = "&Intermediate";
		// 
		// expertToolStripMenuItem
		// 
		this.expertToolStripMenuItem.Name = "expertToolStripMenuItem";
		this.expertToolStripMenuItem.Size = new Size(141, 22);
		this.expertToolStripMenuItem.Text = "&Expert";
		// 
		// customToolStripMenuItem
		// 
		this.customToolStripMenuItem.Name = "customToolStripMenuItem";
		this.customToolStripMenuItem.Size = new Size(141, 22);
		this.customToolStripMenuItem.Text = "&Custom...";
		// 
		// toolStripMenuItem3
		// 
		toolStripMenuItem3.Name = "toolStripMenuItem3";
		toolStripMenuItem3.Size = new Size(138, 6);
		// 
		// bestTimesToolStripMenuItem
		// 
		this.bestTimesToolStripMenuItem.Name = "bestTimesToolStripMenuItem";
		this.bestTimesToolStripMenuItem.Size = new Size(141, 22);
		this.bestTimesToolStripMenuItem.Text = "Best &Times...";
		// 
		// toolStripMenuItem4
		// 
		toolStripMenuItem4.Name = "toolStripMenuItem4";
		toolStripMenuItem4.Size = new Size(138, 6);
		// 
		// exitToolStripMenuItem
		// 
		this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
		this.exitToolStripMenuItem.Size = new Size(141, 22);
		this.exitToolStripMenuItem.Text = "E&xit";
		this.exitToolStripMenuItem.Click += this.ExitToolStripMenuItem_Click;
		// 
		// helpToolStripMenuItem
		// 
		helpToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[] { this.howToPlayToolStripMenuItem, toolStripMenuItem1, this.aboutMinesweeperToolStripMenuItem });
		helpToolStripMenuItem.Name = "helpToolStripMenuItem";
		helpToolStripMenuItem.Size = new Size(44, 20);
		helpToolStripMenuItem.Text = "&Help";
		// 
		// howToPlayToolStripMenuItem
		// 
		this.howToPlayToolStripMenuItem.Name = "howToPlayToolStripMenuItem";
		this.howToPlayToolStripMenuItem.Size = new Size(189, 22);
		this.howToPlayToolStripMenuItem.Text = "How to &Play...";
		// 
		// toolStripMenuItem1
		// 
		toolStripMenuItem1.Name = "toolStripMenuItem1";
		toolStripMenuItem1.Size = new Size(186, 6);
		// 
		// aboutMinesweeperToolStripMenuItem
		// 
		this.aboutMinesweeperToolStripMenuItem.Name = "aboutMinesweeperToolStripMenuItem";
		this.aboutMinesweeperToolStripMenuItem.Size = new Size(189, 22);
		this.aboutMinesweeperToolStripMenuItem.Text = "&About Minesweeper...";
		// 
		// btnNewGame
		// 
		this.btnNewGame.Anchor = AnchorStyles.Top;
		this.btnNewGame.AutoSize = true;
		this.btnNewGame.AutoSizeMode = AutoSizeMode.GrowAndShrink;
		this.btnNewGame.Image = Properties.Resources.smile_1;
		this.btnNewGame.Location = new Point(377, 30);
		this.btnNewGame.Name = "btnNewGame";
		this.btnNewGame.Padding = new Padding(4);
		this.btnNewGame.Size = new Size(46, 46);
		this.btnNewGame.TabIndex = 1;
		this.btnNewGame.UseVisualStyleBackColor = true;
		// 
		// ssdMinesLeft
		// 
		this.ssdMinesLeft.Location = new Point(12, 27);
		this.ssdMinesLeft.Name = "ssdMinesLeft";
		this.ssdMinesLeft.Size = new Size(81, 52);
		this.ssdMinesLeft.TabIndex = 2;
		this.ssdMinesLeft.Text = "sevenSegmentDisplay1";
		// 
		// ssdElapsedTime
		// 
		this.ssdElapsedTime.Anchor = AnchorStyles.Top | AnchorStyles.Right;
		this.ssdElapsedTime.Location = new Point(707, 27);
		this.ssdElapsedTime.Name = "ssdElapsedTime";
		this.ssdElapsedTime.Size = new Size(81, 52);
		this.ssdElapsedTime.TabIndex = 3;
		this.ssdElapsedTime.Text = "sevenSegmentDisplay2";
		// 
		// MainWindow
		// 
		this.AutoScaleDimensions = new SizeF(7F, 15F);
		this.AutoScaleMode = AutoScaleMode.Font;
		this.ClientSize = new Size(800, 450);
		this.Controls.Add(this.ssdElapsedTime);
		this.Controls.Add(this.ssdMinesLeft);
		this.Controls.Add(this.btnNewGame);
		this.Controls.Add(menuStrip);
		this.FormBorderStyle = FormBorderStyle.FixedSingle;
		this.Icon = (Icon)resources.GetObject("$this.Icon");
		this.MainMenuStrip = menuStrip;
		this.Name = "MainWindow";
		this.Text = "Minesweeper";
		this.FormClosing += this.MainWindow_FormClosing;
		this.Load += this.MainWindow_Load;
		menuStrip.ResumeLayout(false);
		menuStrip.PerformLayout();
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
	private Button btnNewGame;
	private SevenSegmentDisplay ssdMinesLeft;
	private SevenSegmentDisplay ssdElapsedTime;
}

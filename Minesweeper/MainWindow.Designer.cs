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
		ToolStripMenuItem helpToolStripMenuItem;
		ToolStripSeparator toolStripMenuItem1;
		ToolStripSeparator toolStripMenuItem2;
		ToolStripSeparator toolStripMenuItem3;
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
		m_menuStrip = new MenuStrip();
		gameToolStripMenuItem = new ToolStripMenuItem();
		helpToolStripMenuItem = new ToolStripMenuItem();
		toolStripMenuItem1 = new ToolStripSeparator();
		toolStripMenuItem2 = new ToolStripSeparator();
		toolStripMenuItem3 = new ToolStripSeparator();
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
		// helpToolStripMenuItem
		// 
		helpToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[] { this.howToPlayToolStripMenuItem, toolStripMenuItem4, this.aboutMinesweeperToolStripMenuItem });
		helpToolStripMenuItem.Name = "helpToolStripMenuItem";
		helpToolStripMenuItem.Size = new Size(44, 20);
		helpToolStripMenuItem.Text = "&Help";
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
		// 
		// intermediateToolStripMenuItem
		// 
		this.intermediateToolStripMenuItem.Name = "intermediateToolStripMenuItem";
		this.intermediateToolStripMenuItem.Size = new Size(180, 22);
		this.intermediateToolStripMenuItem.Text = "&Intermediate";
		// 
		// expertToolStripMenuItem
		// 
		this.expertToolStripMenuItem.Name = "expertToolStripMenuItem";
		this.expertToolStripMenuItem.Size = new Size(180, 22);
		this.expertToolStripMenuItem.Text = "&Expert";
		// 
		// customToolStripMenuItem
		// 
		this.customToolStripMenuItem.Name = "customToolStripMenuItem";
		this.customToolStripMenuItem.Size = new Size(180, 22);
		this.customToolStripMenuItem.Text = "&Custom...";
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
		// MainWindow
		// 
		this.AutoScaleDimensions = new SizeF(7F, 15F);
		this.AutoScaleMode = AutoScaleMode.Font;
		this.ClientSize = new Size(800, 450);
		this.Controls.Add(m_menuStrip);
		this.FormBorderStyle = FormBorderStyle.FixedSingle;
		this.Icon = (Icon)resources.GetObject("$this.Icon");
		this.MainMenuStrip = m_menuStrip;
		this.MaximizeBox = false;
		this.Name = "MainWindow";
		this.Text = "Minesweeper";
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
}
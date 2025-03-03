// Copyright (c) 2025 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

namespace Minesweeper;

partial class MainWindow
{
	/// <summary>
	///  Required designer variable.
	/// </summary>
	private System.ComponentModel.IContainer components = null;

	/// <summary>
	///  Clean up any resources being used.
	/// </summary>
	/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
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
		ToolStripMenuItem gameToolStripMenuItem;
		ToolStripMenuItem helpToolStripMenuItem;
		var resources = new System.ComponentModel.ComponentResourceManager(typeof(MainWindow));
		this.m_menuStrip = new MenuStrip();
		this.m_btnNewGame = new Button();
		this.m_ssdMinesLeft = new SevenSegmentDisplay();
		this.m_ssdElapsedTime = new SevenSegmentDisplay();
		gameToolStripMenuItem = new ToolStripMenuItem();
		helpToolStripMenuItem = new ToolStripMenuItem();
		this.m_menuStrip.SuspendLayout();
		this.SuspendLayout();
		// 
		// gameToolStripMenuItem
		// 
		gameToolStripMenuItem.Name = "gameToolStripMenuItem";
		gameToolStripMenuItem.Size = new Size(50, 20);
		gameToolStripMenuItem.Text = "&Game";
		// 
		// helpToolStripMenuItem
		// 
		helpToolStripMenuItem.Name = "helpToolStripMenuItem";
		helpToolStripMenuItem.Size = new Size(44, 20);
		helpToolStripMenuItem.Text = "&Help";
		// 
		// m_menuStrip
		// 
		this.m_menuStrip.Items.AddRange(new ToolStripItem[] { gameToolStripMenuItem, helpToolStripMenuItem });
		this.m_menuStrip.Location = new Point(0, 0);
		this.m_menuStrip.Name = "m_menuStrip";
		this.m_menuStrip.RenderMode = ToolStripRenderMode.System;
		this.m_menuStrip.Size = new Size(800, 24);
		this.m_menuStrip.TabIndex = 0;
		this.m_menuStrip.Text = "menuStrip1";
		// 
		// m_btnNewGame
		// 
		this.m_btnNewGame.Anchor = AnchorStyles.Top;
		this.m_btnNewGame.AutoSize = true;
		this.m_btnNewGame.AutoSizeMode = AutoSizeMode.GrowAndShrink;
		this.m_btnNewGame.Image = Properties.Resources.Smile1;
		this.m_btnNewGame.Location = new Point(378, 27);
		this.m_btnNewGame.Name = "m_btnNewGame";
		this.m_btnNewGame.Padding = new Padding(3);
		this.m_btnNewGame.Size = new Size(44, 44);
		this.m_btnNewGame.TabIndex = 1;
		this.m_btnNewGame.UseVisualStyleBackColor = true;
		// 
		// m_ssdMinesLeft
		// 
		this.m_ssdMinesLeft.Location = new Point(12, 29);
		this.m_ssdMinesLeft.Name = "m_ssdMinesLeft";
		this.m_ssdMinesLeft.Size = new Size(65, 40);
		this.m_ssdMinesLeft.TabIndex = 2;
		this.m_ssdMinesLeft.Text = "sevenSegmentDisplay1";
		// 
		// m_ssdElapsedTime
		// 
		this.m_ssdElapsedTime.Anchor = AnchorStyles.Top | AnchorStyles.Right;
		this.m_ssdElapsedTime.Location = new Point(723, 29);
		this.m_ssdElapsedTime.Name = "m_ssdElapsedTime";
		this.m_ssdElapsedTime.Size = new Size(65, 40);
		this.m_ssdElapsedTime.TabIndex = 3;
		this.m_ssdElapsedTime.Text = "sevenSegmentDisplay2";
		// 
		// MainWindow
		// 
		this.AutoScaleDimensions = new SizeF(7F, 15F);
		this.AutoScaleMode = AutoScaleMode.Font;
		this.ClientSize = new Size(800, 450);
		this.Controls.Add(this.m_ssdElapsedTime);
		this.Controls.Add(this.m_ssdMinesLeft);
		this.Controls.Add(this.m_btnNewGame);
		this.Controls.Add(this.m_menuStrip);
		this.FormBorderStyle = FormBorderStyle.FixedSingle;
		this.Icon = (Icon)resources.GetObject("$this.Icon");
		this.MainMenuStrip = this.m_menuStrip;
		this.MaximizeBox = false;
		this.Name = "MainWindow";
		this.Text = "Minesweeper";
		this.Load += this.MainWindow_Load;
		this.m_menuStrip.ResumeLayout(false);
		this.m_menuStrip.PerformLayout();
		this.ResumeLayout(false);
		this.PerformLayout();
	}

	#endregion

	private MenuStrip m_menuStrip;
	private Button m_btnNewGame;
	private SevenSegmentDisplay m_ssdMinesLeft;
	private SevenSegmentDisplay m_ssdElapsedTime;
}
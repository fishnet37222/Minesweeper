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
		var resources = new System.ComponentModel.ComponentResourceManager(typeof(MainWindow));
		this.SuspendLayout();
		// 
		// MainWindow
		// 
		this.AutoScaleDimensions = new SizeF(7F, 15F);
		this.AutoScaleMode = AutoScaleMode.Font;
		this.ClientSize = new Size(800, 450);
		this.FormBorderStyle = FormBorderStyle.FixedSingle;
		this.Icon = (Icon)resources.GetObject("$this.Icon");
		this.Name = "MainWindow";
		this.Text = "Minesweeper";
		this.ResumeLayout(false);
	}

	#endregion
}

// Copyright (c) 2024 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

namespace Minesweeper;

partial class CustomDifficultyDialog
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
	/// Required method for Designer support - do not modify
	/// the contents of this method with the code editor.
	/// </summary>
	private void InitializeComponent()
	{
		this.m_btnCancel = new Button();
		this.m_btnOK = new Button();
		this.label1 = new Label();
		this.label2 = new Label();
		this.label3 = new Label();
		this.m_txtWidth = new TextBox();
		this.m_txtHeight = new TextBox();
		this.m_txtMines = new TextBox();
		this.SuspendLayout();
		// 
		// m_btnCancel
		// 
		this.m_btnCancel.Anchor = AnchorStyles.Bottom | AnchorStyles.Right;
		this.m_btnCancel.DialogResult = DialogResult.Cancel;
		this.m_btnCancel.Location = new Point(167, 99);
		this.m_btnCancel.Name = "m_btnCancel";
		this.m_btnCancel.Size = new Size(75, 23);
		this.m_btnCancel.TabIndex = 0;
		this.m_btnCancel.Text = "Cancel";
		this.m_btnCancel.UseVisualStyleBackColor = true;
		// 
		// m_btnOK
		// 
		this.m_btnOK.Anchor = AnchorStyles.Bottom | AnchorStyles.Right;
		this.m_btnOK.DialogResult = DialogResult.OK;
		this.m_btnOK.Location = new Point(86, 99);
		this.m_btnOK.Name = "m_btnOK";
		this.m_btnOK.Size = new Size(75, 23);
		this.m_btnOK.TabIndex = 1;
		this.m_btnOK.Text = "OK";
		this.m_btnOK.UseVisualStyleBackColor = true;
		this.m_btnOK.Click += this.m_btnOK_Click;
		// 
		// label1
		// 
		this.label1.AutoSize = true;
		this.label1.Location = new Point(12, 15);
		this.label1.Name = "label1";
		this.label1.Size = new Size(39, 15);
		this.label1.TabIndex = 2;
		this.label1.Text = "Width";
		// 
		// label2
		// 
		this.label2.AutoSize = true;
		this.label2.Location = new Point(12, 44);
		this.label2.Name = "label2";
		this.label2.Size = new Size(43, 15);
		this.label2.TabIndex = 3;
		this.label2.Text = "Height";
		// 
		// label3
		// 
		this.label3.AutoSize = true;
		this.label3.Location = new Point(12, 73);
		this.label3.Name = "label3";
		this.label3.Size = new Size(39, 15);
		this.label3.TabIndex = 4;
		this.label3.Text = "Mines";
		// 
		// m_txtWidth
		// 
		this.m_txtWidth.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
		this.m_txtWidth.Location = new Point(61, 12);
		this.m_txtWidth.Name = "m_txtWidth";
		this.m_txtWidth.Size = new Size(181, 23);
		this.m_txtWidth.TabIndex = 5;
		this.m_txtWidth.TextAlign = HorizontalAlignment.Right;
		// 
		// m_txtHeight
		// 
		this.m_txtHeight.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
		this.m_txtHeight.Location = new Point(61, 41);
		this.m_txtHeight.Name = "m_txtHeight";
		this.m_txtHeight.Size = new Size(181, 23);
		this.m_txtHeight.TabIndex = 6;
		this.m_txtHeight.TextAlign = HorizontalAlignment.Right;
		// 
		// m_txtMines
		// 
		this.m_txtMines.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
		this.m_txtMines.Location = new Point(61, 70);
		this.m_txtMines.Name = "m_txtMines";
		this.m_txtMines.Size = new Size(181, 23);
		this.m_txtMines.TabIndex = 7;
		this.m_txtMines.TextAlign = HorizontalAlignment.Right;
		// 
		// CustomDifficultyDialog
		// 
		this.AcceptButton = this.m_btnOK;
		this.AutoScaleDimensions = new SizeF(7F, 15F);
		this.AutoScaleMode = AutoScaleMode.Font;
		this.CancelButton = this.m_btnCancel;
		this.ClientSize = new Size(254, 134);
		this.Controls.Add(this.m_txtMines);
		this.Controls.Add(this.m_txtHeight);
		this.Controls.Add(this.m_txtWidth);
		this.Controls.Add(this.label3);
		this.Controls.Add(this.label2);
		this.Controls.Add(this.label1);
		this.Controls.Add(this.m_btnOK);
		this.Controls.Add(this.m_btnCancel);
		this.FormBorderStyle = FormBorderStyle.FixedDialog;
		this.MaximizeBox = false;
		this.MinimizeBox = false;
		this.Name = "CustomDifficultyDialog";
		this.ShowInTaskbar = false;
		this.StartPosition = FormStartPosition.CenterParent;
		this.Text = "Custom Difficulty";
		this.Load += this.CustomDifficultyDialog_Load;
		this.ResumeLayout(false);
		this.PerformLayout();
	}

	#endregion

	private Button m_btnCancel;
	private Button m_btnOK;
	private Label label1;
	private Label label2;
	private Label label3;
	private TextBox m_txtWidth;
	private TextBox m_txtHeight;
	private TextBox m_txtMines;
}
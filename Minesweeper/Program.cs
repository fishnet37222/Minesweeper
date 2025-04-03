// Copyright (c) 2025 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

namespace Minesweeper;

public static class Program
{
	[STAThread]
	public static void Main()
	{
		ApplicationConfiguration.Initialize();
		Application.Run(new MainWindow());
	}
}

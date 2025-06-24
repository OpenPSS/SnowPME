using System;
using System.Collections.Generic;

using Sce.PlayStation.Core;
using Sce.PlayStation.Core.Environment;
using Sce.PlayStation.Core.Graphics;
using Sce.PlayStation.Core.Input;

namespace WebsiteOpen
{
	public class AppMain
	{
		
		public static int Main (string[] args)
		{
			Shell.Action action = Shell.Action.BrowserAction(@"https://psmreborn.com");
			Shell.Execute(ref action);
			return 0;
		}
	}
}

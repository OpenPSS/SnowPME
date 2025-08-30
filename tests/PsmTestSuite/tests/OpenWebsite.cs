using System;
using Sce.PlayStation.Core.Environment;

namespace PsmTestSuite
{
	public class OpenWebsite : PsmTest
	{
		public override void Run() {
			string url = "https://psmreborn.com";
			Shell.Action action = Shell.Action.BrowserAction(url);
			Shell.Execute(ref action);
			Log ("Opening: " + url);
		}
	}
}


using System;
using System.Collections.Generic;

using Sce.PlayStation.Core;
using Sce.PlayStation.Core.Environment;
using Sce.PlayStation.Core.Graphics;
using Sce.PlayStation.Core.Input;

namespace PsmTestSuite
{
	public class AppMain
	{
		private static List<PsmTest> tests = new List<PsmTest>();
		
		public static void Main (string[] args)
		{
			tests.Add(new DeviceID());
			tests.Add(new PM());
			tests.Add(new BackgroundMusic());
			
			int passed = 0;
			foreach(PsmTest test in tests) {
				if(test.Check()) passed++;
			}
			
			if(passed == tests.Count) {
				Console.WriteLine("ALL TESTS PASSED");	
			}
		
		}
	}
}

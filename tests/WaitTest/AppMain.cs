using System;
using System.Threading;
using System.IO;

using Sce.PlayStation.Core.Graphics;
using Sce.PlayStation.Core;

namespace WaitTest
{
	public class AppMain
	{	
		static GraphicsContext ctx;
		public static int Initalize() {
			ctx = new GraphicsContext();
			ctx.SetClearColor(255, 0, 0, 255);
			return 0;
		}
		public static int Update() {
			Console.WriteLine ("Sleeping ...");
			Thread.Sleep(new TimeSpan(0,0,5));
			return 0;
		}
		public static int Render() {
			Console.WriteLine ("Rendering ...");
			ctx.SetClearColor(new Vector4(1.0f, 0.0f, 0.0f, 1.0f));
			ctx.Clear();
			ctx.SwapBuffers();
			return 0;
		}
		public static int Main (string[] args)
		{
			Initalize();
			
			for(int i = 0; i < 3; i++) {
				Update();
				Render();
			}
			
			return 0;
		}
	}
}

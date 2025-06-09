using System;
using System.Collections.Generic;

using Sce.PlayStation.Core;
using Sce.PlayStation.Core.Environment;
using Sce.PlayStation.Core.Graphics;
using Sce.PlayStation.Core.Input;

namespace PmTest
{
	public class AppMain
	{
		private static GraphicsContext graphics;
		
		public static void Main (string[] args)
		{
			Initialize ();
			
			byte[] pm = PersistentMemory.Read();
			pm[0] = 0x1;
			PersistentMemory.Write(pm);
			
			// check it worked
			
			byte[] pm2 = PersistentMemory.Read();
			if(pm2[0] == 0x1){
				Console.WriteLine("TEST SUCCESS!");	
			}
			else{
				Console.WriteLine ("TEST FAIL!");	
			}
		}

		public static void Initialize ()
		{
			// Set up the graphics system
			graphics = new GraphicsContext ();
		}

	}
}

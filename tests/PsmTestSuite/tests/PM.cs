using System;
using Sce.PlayStation.Core.Environment;

namespace PsmTestSuite
{
	public class PM : PsmTest
	{
		public override void Run() {
			byte[] pm = PersistentMemory.Read();
			pm[0] = 0x1;
			PersistentMemory.Write(pm);
			
			// check it worked
			
			byte[] pm2 = PersistentMemory.Read();
			Log ("Value is: "+pm2[0].ToString());
			
			pm2[0] = 0x4;
			PersistentMemory.Write(pm2);
			
			byte[] pm3 = PersistentMemory.Read();
			Log ("Value is: "+pm3[0].ToString());
			
			
		}
	}
}


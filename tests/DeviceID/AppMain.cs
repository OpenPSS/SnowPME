using System;
using System.IO;
using Sce.PlayStation.Core.Services;
namespace DeviceID
{
	public class AppMain
	{		
		public static int Main (string[] args)
		{
			string uid = BitConverter.ToString(AccountInformation.UniqueID).Replace("-", "");
			Console.WriteLine(uid);
			return 0;
		}
	}
}

using System;
using Sce.PlayStation.Core.Services;

namespace PsmTestSuite
{
	public class DeviceID : PsmTest
	{
		public override void Run() {
			string uid = BitConverter.ToString(AccountInformation.UniqueID).Replace("-", "");
			Log(uid);
		}
	}
}


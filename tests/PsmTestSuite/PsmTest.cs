using System;
using System.IO;
using System.Linq;
using System.Collections;
using System.Collections.Generic;
using Sce.PlayStation.Core.Input;
using Sce.PlayStation.Core.Environment;
using Sce.PlayStation.Core.Services;

namespace PsmTestSuite
{
	public abstract class PsmTest
	{		
		private List<string> results = new List<string>(); 
		public string[] Results {  
			get{
				return results.ToArray();	
			}
		}
		
		/*
		 * Fingerprint SDK Target
		 * PSM does not offer a function to check what your running on
		 * However, certain functions in PSM behave differnetly on differnet platforms
		 * as we are unit-testing SnowPME; i need to make sure we select the right expected result, 
		 * for the right "Config::TargetImplementation" setting.
		 */
		public static string PsmPlatform {
			get{
				
				// NOTE: this is more of a fingerprint of SDK1.21 than anything else;
				// Android never got SDK2.00; and no android device has a Rear Touchpad,
				// but technically this check will fail on Vita 1.21, or Simulator on SDK 1.21.
				try{
					Touch.GetRearTouchData(0);						
				}
				catch(Exception) {
					return "ANDROID";	
				}
				
				// Otherwise, on Windows UniqueID is your windows username;
				// on Vita it is a CMAC hash calculated from your Account ID.
				byte[] uid = AccountInformation.UniqueID;
				for(int i = 0; i < uid.Length; i++) { 
					if(uid[i] == 0x00) continue;
					
					if(uid[i] < 0x20 || uid[i] >= 0x7F) {
						return "VITA"; 
					}
				}
				return "WINDOWS";				
			}
		}
		
		public string TestName {
			get{
				string name = this.GetType().Name;
				return name;
			}
		}
		
		public void TryThing(string thing, Action action) {
			try {
				action();
				Log (thing+": SUCCESS");
			}
			catch (Exception e) {
				Log(thing+": FAIL, "+e.Message);		
			}
		}
		
		
		public string TestFile {
			get{
				string fnamePlatform = TestName+"-"+PsmPlatform+".result";
				string fname = TestName+".result";
				string applicationResults = "/Application/results/";
				string documents = "/Documents/";
				
				string path = Path.Combine(applicationResults,fnamePlatform);
				if(File.Exists(path)) return path;
				
				path = Path.Combine (applicationResults, fname);
				if(File.Exists(path)) return path;
				
				path = Path.Combine(documents, fnamePlatform);
				
				return path;
			}
		}
		
		public abstract void Run();
		
		public virtual void Log(string msg) {
			msg = msg.Replace("\n", "").Replace("\r", "");
			this.results.Add(msg);
			Console.WriteLine(TestName+": "+msg);
		}
		
		public virtual void Log(string tag, string msg) {
			this.results.Add("["+tag+"] "+msg);
			Console.WriteLine(TestName+": "+"["+tag+"] "+msg);
		}

		public virtual void Log(Object msg) {
			Log(msg.ToString());	
		}
		
		public virtual void Log(String tag, Object msg) {
			Log(tag, msg.ToString());
		}
		
		public virtual void TryRun() {
			results.Clear();
			try {
				Run ();	
			} catch (Exception ex) {
				Log("Message", ex.Message);
				Log("InnerException", ex.InnerException.ToString());
				Log("StackTrace", ex.StackTrace);

			}
		}
		
		public virtual void Record() {
			Console.WriteLine ("Recording: " + TestName);
			TryRun();
			File.WriteAllText(TestFile, String.Join("\n", Results)); 
		}
		public virtual bool Check(){
			bool valid = true;
			
			if(!File.Exists(TestFile)) {
			this.Record();
			}
			
			String[] expected = File.ReadAllText(TestFile).Split('\n');
			TryRun();
			
			if(Results.Length != expected.Length) {
				valid = false;
				
				for(int i = 0; i < Math.Max(Results.Length, expected.Length); i++) {
					if(i >= expected.Length) {
						Console.WriteLine ("err ("+i.ToString()+"): got: "+Results[i]+", expected: nothing");
						continue;
					}
					else if(i >= Results.Length) {
						Console.WriteLine ("err ("+i.ToString()+"): got: nothing, expected: "+expected[i]);
						continue;
					}
					else if(expected[i] != Results[i]) {
						Console.WriteLine("err ("+i.ToString()+"): got: "+Results[i] + ", expected: "+expected[i]);
						continue;
					}
				}
				
				File.WriteAllText (TestFile, String.Join ("\n", Results));
								
				Console.WriteLine ("err: expected result is not expacted length ("+expected.Length.ToString()+")");
			}
			else {
				for(int i = 0; i < Results.Length; i++){
					if(expected[i] != Results[i]) {
						Console.WriteLine("err ("+i.ToString()+"): got: "+Results[i] + ", expected: "+expected[i]);
						valid = false;
					}
				}
				
			}
			
			if(valid) {
				Console.WriteLine (TestName + " -- PASSED");
				return true;
			}
			else {
				Console.WriteLine (TestName + " -- FAILED");
				return false;
			}
		}
	}
}


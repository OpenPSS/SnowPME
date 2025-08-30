using System;
using System.IO;
using System.Linq;
using System.Collections;
using System.Collections.Generic;

namespace PsmTestSuite
{
	public abstract class PsmTest
	{		
		private List<string> results = new List<string>(); 
		
		public string TestName {
			get{
				string name = this.GetType().Name;
				return name;
			}
		}
		public string TestFile {
			get{
				string path = "/Documents/"+TestName+".result";	
				return path;
			}
		}
		
		
		public abstract void Run();
		
		public virtual void Log(string msg) {
			this.results.Add(msg);
			Console.WriteLine(TestName+": "+msg);
		}
		
		public virtual void Log(string tag, string msg) {
			this.results.Add("["+tag+"] "+msg);
			Console.WriteLine(TestName+": "+"["+tag+"] "+msg);
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
			File.WriteAllLines(TestFile, results.ToArray()); 
		}
		public virtual bool Check(){
			bool valid = true;
			
			if(!File.Exists(TestFile)) {
				this.Record();
			}
			
			String[] expected = File.ReadAllLines(TestFile);
			TryRun();
			
			for(int i = 0; i < results.Count; i++){
				if(expected[i] != results[i]) {
					Console.WriteLine("got: "+results[i] + ", expected: "+expected[i]);
					valid = false;
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


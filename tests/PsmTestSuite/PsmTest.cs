using System;
using System.IO;
using System.Linq;
using System.Collections;
using System.Collections.Generic;
using Sce.PlayStation.Core.Input;

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
				string path = "/Application/results/"+TestName+".result";
				if(File.Exists(path)) return path;
				else return "/Documents/"+TestName+".result";
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
			File.WriteAllLines(TestFile, results.ToArray()); 
		}
		public virtual bool Check(){
			bool valid = true;
			
			if(!File.Exists(TestFile)) {
				this.Record();
			}
			
			String[] expected = File.ReadAllLines(TestFile);
			TryRun();
			
			if(results.Count != expected.Length) {
				valid = false;
				Console.WriteLine ("err: expected result is not expacted length ("+expected.Length.ToString()+")");
			}
			else {
				for(int i = 0; i < results.Count; i++){
					if(expected[i] != results[i]) {
						Console.WriteLine("err: got: "+results[i] + ", expected: "+expected[i]);
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


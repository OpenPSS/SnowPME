using System;
using System.IO;
using System.Collections.Generic;

using Sce.PlayStation.Core;
using Sce.PlayStation.Core.Environment;
using Sce.PlayStation.Core.Graphics;
using Sce.PlayStation.Core.Input;

namespace IoTest
{
	public class AppMain
	{
		public static int Main (string[] args)
		{
			Console.WriteLine("- Trying to read non existent file .. ( should fail )");
			try{
				File.ReadAllText("/Documents/Test.txt");
				Console.WriteLine ("Succeeded");
			}
			catch(Exception e) {Console.WriteLine (e.Message);};
			
			Console.WriteLine ("- Trying to write to /Application .. ( should fail )");
			try{
				File.WriteAllText("/Applications/Test.txt", "trans rights");	
				Console.WriteLine ("Succeeded");
			}
			catch(Exception e) {Console.WriteLine (e.Message);};

			Console.WriteLine ("- Trying to write to /System .. ( should fail )");
			try{
				File.WriteAllText("/System/Test.txt", "trans rights");	
				Console.WriteLine ("Succeeded");

			}
			catch(Exception e) {Console.WriteLine (e.Message);};
			
			Console.WriteLine ("- Trying to read from /System ( should fail )");
			try{
				File.ReadAllText("/System/pm.dat");
				Console.WriteLine ("Succeeded");
			}
			catch(Exception e) {Console.WriteLine (e.Message);};
			
			
			Console.WriteLine (" - Trying to write to root .. ( should fail )");
			try{
				File.WriteAllText("/Test.txt", "trans rights");	
				Console.WriteLine ("Succeeded");
			}
			catch(Exception e) {Console.WriteLine (e.Message);};
			
			Console.WriteLine (" - Trying to relative write to root");
			try{
				File.WriteAllText("Test.txt", "trans rights");
				Console.WriteLine ("Succeeded");
			}
			catch(Exception e) {Console.WriteLine (e.Message);};
			
			
			Console.WriteLine (" - Directory listing of /");
			try{
				foreach(string filename in Directory.GetFileSystemEntries("/")) {	
					Console.WriteLine ("- {}", filename);	
				}
				Console.WriteLine ("Succeeded");
			}
			catch(Exception e) {Console.WriteLine (e.Message);}
			
			Console.WriteLine (" - Directory listing of /Application");
			try{
				foreach(string filename in Directory.GetFileSystemEntries("/Application")) {	
					Console.WriteLine ("- {}", filename);	
				}
				Console.WriteLine ("Succeeded");
			}
			catch(Exception e) {Console.WriteLine (e.Message);}
			
			Console.WriteLine (" - Directory listing of /Temp");
			try{
				foreach(string filename in Directory.GetFileSystemEntries("/Temp")) {	
					Console.WriteLine ("- {}", filename);	
				}
				Console.WriteLine ("Succeeded");
			}
			catch(Exception e) {Console.WriteLine (e.Message);}
			
			Console.WriteLine (" - Directory listing of /System (should fail)");
			try{
				foreach(string filename in Directory.GetFileSystemEntries("/System")) {	
					Console.WriteLine ("- {}", filename);	
				}
				Console.WriteLine ("Succeeded");
			}
			catch(Exception e) {Console.WriteLine (e.Message);}
			
			Console.WriteLine (" - Directory listing of /Documents (should fail)");
			try{
				foreach(string filename in Directory.GetFileSystemEntries("/Documents")) {	
					Console.WriteLine ("- {}", filename);	
				}
				Console.WriteLine ("Succeeded");
			}
			catch(Exception e) {Console.WriteLine (e.Message);}
			
			
			Console.WriteLine ("- Setting Working Directory to /Application");
			try{
				Directory.SetCurrentDirectory("/Application");
				Console.WriteLine ("Succeeded");
			}
			catch(Exception e) {Console.WriteLine(e.Message);}
			
			try{
				Console.WriteLine ("- Current Directory is: {}", Directory.GetCurrentDirectory());				
				Console.WriteLine ("Succeeded");
			}
			catch(Exception e) {Console.WriteLine (e.Message);}
			
			Console.WriteLine ("- Trying relative write to /Application .. ( should fail )");
			try{
				File.WriteAllText("Test.txt", "trans rights");
				Console.WriteLine ("Succeeded");
			}
			catch(Exception e) {Console.WriteLine (e.Message);};
			
			Console.WriteLine ("- Setting Working Directory to /Application");
			try{
				Directory.SetCurrentDirectory("/Application");				
				Console.WriteLine ("Succeeded");
			}
			catch(Exception e) {Console.WriteLine(e.Message);}
			
			try{
				Console.WriteLine ("- Current Directory is: {}", Directory.GetCurrentDirectory());
				Console.WriteLine ("Succeeded");
			}
			catch(Exception e) {Console.WriteLine (e.Message);}

			Console.WriteLine ("- Trying relative write to /Documents .. ( should succeed )");
			try{
				File.WriteAllText("Test.txt", "trans rights");	
				Console.WriteLine ("Succeeded");
			}
			catch(Exception e) {Console.WriteLine (e.Message);};

			Console.WriteLine ("- Trying absolute write to /Documents .. ( should succeed )");
			try{
				File.WriteAllText("/Documents/Test.txt", "trans rights");	
				Console.WriteLine ("Succeeded");
			}
			catch(Exception e) {Console.WriteLine (e.Message);};
			
			Console.WriteLine ("- Trying path traversal (write to /Application/Test/Trans/Rights/../../../../../../Documents/test.txt)  .. ( should succeed )");
			try{
				File.WriteAllText("/Application/Test/Trans/Rights/../../../../../../Documents/test.txt", "trans rights");	
				Console.WriteLine ("Succeeded");
			}
			catch(Exception e) {Console.WriteLine (e.Message);};
			
			Console.WriteLine("- Trying to change creation time");
			try{
				File.SetCreationTime("/Documents/test.txt", DateTime.MinValue);
				Console.WriteLine ("Succeeded");
			}catch(Exception e) {Console.WriteLine (e.Message);}

			Console.WriteLine("- Trying to change modified time");
			try{
				File.SetLastWriteTime("/Documents/test.txt", DateTime.MinValue);
				Console.WriteLine ("Succeeded");
			}catch(Exception e) {Console.WriteLine (e.Message);}
			
			Console.WriteLine("- Trying to change access time");
			try{
				File.SetLastAccessTime("/Documents/test.txt", DateTime.MinValue);
				Console.WriteLine ("Succeeded");
			}catch(Exception e) {Console.WriteLine (e.Message);}
			
			try{
				Console.WriteLine ("- Creation time {}", File.GetCreationTime("/Documents/test.txt"));
				Console.WriteLine ("Succeeded");
			}
			catch(Exception e) {Console.WriteLine (e.Message);}
			try{
				Console.WriteLine ("- Modified time {}", File.GetLastWriteTime("/Documents/test.txt"));
				Console.WriteLine ("Succeeded");
			}catch(Exception e) {Console.WriteLine (e.Message);}
			try{
				Console.WriteLine ("- Accessed time {}", File.GetLastAccessTime("/Documents/test.txt"));
				Console.WriteLine ("Succeeded");
			}
			catch(Exception e) {Console.WriteLine (e.Message);}
			
			Console.WriteLine (" - Trying to delete /Documents/test.txt ( should succeed )");
			try{
				File.Delete("/Documents/test.txt");
				Console.WriteLine ("Succeeded");
			}catch(Exception e) { Console.WriteLine (e.Message);}
			
			Console.WriteLine (" - Trying to delete /Documents/test.txt again ( should fail )");
			try{
				File.Delete("/Documents/test.txt");
				Console.WriteLine ("Succeeded");
			}catch(Exception e) { Console.WriteLine (e.Message);}

			
			Console.WriteLine (" - Trying to delete /Application/app.exe again ( should fail )");
			try{
				File.Delete("/Application/app.exe");
				Console.WriteLine ("Succeeded");
			}catch(Exception e) { Console.WriteLine (e.Message);}
			
			return 0;
		}
	}
}

using System;
using System.Collections.Generic;

using Sce.PlayStation.Core;
using Sce.PlayStation.Core.Environment;
using Sce.PlayStation.Core.Graphics;
using Sce.PlayStation.Core.Input;
using Sce.PlayStation.Core.Audio;


/*
 * ♬ MUSIC ♬
 * Artist: tubebackr
 * Track: Chill With Me
 * @tubebackr
 * hypeddit.com/tubebackr/chillwithme-1
*/

namespace BgmTest
{
	public class AppMain
	{
		public static int Main (string[] args)
		{
			Bgm bgm = new Bgm("/Application/test.mp3");

			BgmPlayer player = bgm.CreatePlayer();
			player.Dispose();
			player = bgm.CreatePlayer();
			Console.WriteLine ("Status = "+player.Status);
			player.Play();
			Console.WriteLine ("Status = "+player.Status);
			player.Pause();
			Console.WriteLine ("Status = "+player.Status);
			player.Resume();
			
			player.Loop = true;
			player.PlaybackRate = 3;
			
			Console.WriteLine("Looping = "+player.Loop);
			Console.WriteLine("LoopStart = "+player.LoopStart);
			Console.WriteLine("LoopEnd  = "+player.LoopEnd);
			Console.WriteLine("Duration = "+player.Duration);
			Console.WriteLine("Time = "+player.Time);
			Console.WriteLine("PlaybackRate = "+player.PlaybackRate);
			Console.WriteLine("Volume = "+player.Volume);
			
			
			DateTime finish = DateTime.Now.AddSeconds(15);
			
			for(;DateTime.Now < finish;) { SystemEvents.CheckEvents(); };
			
			Console.WriteLine ("Test Succeeded");
			return 0;
		}
	}
}

using System;
using System.Threading;

using Sce.PlayStation.Core;
using Sce.PlayStation.Core.Audio;

namespace PsmTestSuite
{
	public class BackgroundMusic : PsmTest
	{
		
		/*
		 * ♬ MUSIC ♬
		 * Artist: tubebackr
		 * Track: Chill With Me
		 * @tubebackr
		 * hypeddit.com/tubebackr/chillwithme-1
		*/
		public override void Run() {
			using(Bgm bgm = new Bgm("/Application/assets/test.mp3")) 
			{
				using(BgmPlayer player = bgm.CreatePlayer()) 
				{
					Log ("Status", player.Status);
					player.Stop();
					
					Log ("Status", player.Status);
					player.Play();
					
					Log ("Status", player.Status);
					player.Pause();
					
					Log ("Status", player.Status);
					player.Resume();
					
					
					player.Loop = true;
					player.PlaybackRate = 3;
					
					Log("Looping", player.Loop);
					Log("LoopStart", player.LoopStart);
					Log("LoopEnd", player.LoopEnd);
					Log("Duration", player.Duration);
					Log("Time", player.Time);
					Log("PlaybackRate", player.PlaybackRate);
					Log("Volume", player.Volume);
					
					Thread.Sleep(3000);
				}
			}
		}
	}
}


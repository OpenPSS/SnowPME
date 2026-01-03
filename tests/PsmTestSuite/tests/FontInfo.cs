using System;
using Sce.PlayStation.Core;
using Sce.PlayStation.Core.Imaging;

namespace PsmTestSuite
{
	public class FontInfo : PsmTest
	{		
		public override void Run() {
			Font fnt = new Font(FontAlias.System, 24, FontStyle.Bold);
			
			Log("Name", fnt.Name);
			Log("Style", fnt.Style);
			Log("Size", fnt.Size);
			Log("Metrics.Ascent", fnt.Metrics.Ascent);
			Log("Metrics.Descent", fnt.Metrics.Descent);
			Log("Metrics.Leading", fnt.Metrics.Leading);
			
			Log("GetTextWidth", fnt.GetTextWidth("Trans Rights"));
			
			CharMetrics[] metrics = fnt.GetTextMetrics("Trans Rights");
			foreach(CharMetrics metric in metrics) {
				Log("Metric.X", metric.X);				
				Log("Metric.Y", metric.Y);				
				Log("Metric.HorizontalBearingX", metric.HorizontalBearingX);				
				Log("Metric.HorizontalBearingY", metric.HorizontalBearingY);	
				Log("Metric.HorizontalAdvance", metric.HorizontalAdvance);	
				Log("Metric.Width", metric.Width);				
				Log("Metric.Height", metric.Height);

			}
			
			
			Log ("Shallow Clone");
			Font fnt2 = (Font)fnt.ShallowClone();
			
			Log ("Dispose");
			fnt2.Dispose();

		}
	}
}


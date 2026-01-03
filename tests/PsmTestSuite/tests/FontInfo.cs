using System;
using Sce.PlayStation.Core;
using Sce.PlayStation.Core.Imaging;

namespace PsmTestSuite
{
	public class FontInfo : PsmTest
	{
		public override void Run() {
			Font fnt = new Font(FontAlias.System, 1, FontStyle.Bold);
			
			Log("Name", fnt.Name);
			Log("Style", fnt.Style);
			Log("Size", fnt.Size);
			Log("Metrics.Ascent", fnt.Metrics.Ascent);
			Log("Metrics.Descent", fnt.Metrics.Descent);
			Log("Metrics.Leading", fnt.Metrics.Leading);
			
			Log("GetTextWidth", fnt.GetTextWidth("Trans Rights"));
			Log("GetTextMetrics", fnt.GetTextMetrics("Trans Rights"));
			
			Log ("Shallow Clone");
			Font fnt2 = (Font)fnt.ShallowClone();
			
			Log ("Dispose");
			fnt2.Dispose();

		}
	}
}


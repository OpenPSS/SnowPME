using System;

using System.Collections.Generic;
using System.Linq;

using Sce.PlayStation.Core;
using Sce.PlayStation.Core.Services;
using Sce.PlayStation.Core.Environment;

namespace IapTest
{
	public class AppMain
	{
		private static InAppPurchaseDialog dialog;
		
		public static void Main (string[] args)
		{
			
			dialog = new InAppPurchaseDialog();
			TestIap();
		}
		
		public static CommonDialogResult getResult () {
			while(dialog.State != CommonDialogState.Finished) { SystemEvents.CheckEvents (); };
			return dialog.Result;
		}
		
		
		public static void TestIap() 
		{
			int fail = 0;
			
			// try to make a purchase without prodcut info
			Console.Write ("Purchase without ProductInfo Test: ");
			try {dialog.Purchase(dialog.ProductList.Last().Label); Console.WriteLine ("FAIL"); } catch(Exception e) {Console.WriteLine ("PASS "+e.Message.Replace("\n", ""));};		

			Console.Write ("Consume without ProductInfo Test: ");
			try {dialog.Consume(dialog.ProductList.Last().Label); Console.WriteLine ("FAIL"); } catch(Exception e) {Console.WriteLine ("PASS "+e.Message.Replace("\n", ""));};		

			Console.Write ("Product Fail Test: ");
			for(int i = 0; i < 5; i++) try { dialog.GetProductInfo(null); } catch(Exception) {fail++;};
			if(fail == 4) Console.WriteLine ("PASS");
			else Console.WriteLine ("FAIL");
			
			Console.Write ("Get Product Info Test: ");			
			if(getResult() == CommonDialogResult.OK) {
				if(dialog.IsProductInfoComplete) Console.Write ("PASS");
				
				// try to make a purchase without prodcut info
				Console.Write ("Purchase without TicketInfo Test: ");
				try {dialog.Purchase(dialog.ProductList.Last().Label); Console.WriteLine ("FAIL"); } catch(Exception e) {Console.WriteLine ("PASS "+e.Message.Replace("\n", ""));};		
	
				Console.Write ("Consume without TicketInfo Test: ");
				try {dialog.Consume(dialog.ProductList.Last().Label); Console.WriteLine ("FAIL"); } catch(Exception e) {Console.WriteLine ("PASS "+e.Message.Replace("\n", ""));};		

				
				fail = 0;
				Console.Write ("Ticket Fail Test: ");
				for(int i = 0; i < 5; i++) try { dialog.GetTicketInfo(); } catch(Exception) {fail++;};	
				if(fail == 4) Console.WriteLine ("PASS");
				else Console.WriteLine ("FAIL");
				
				Console.Write ("Get Ticket Info Test: ");
				if(getResult() == CommonDialogResult.OK) {
					Console.WriteLine("PASS");
					
					foreach(InAppPurchaseProduct product in dialog.ProductList) {
						if(product.IsTicketValid) { continue; }

						Console.Write ("Purchase Fail Test: ");
						fail = 0;
						for(int i = 0; i < 5; i++) try { dialog.Purchase(product.Label); } catch(Exception) {fail++;};	
						if(fail == 4) Console.WriteLine ("PASS");
						else Console.WriteLine ("FAIL");
						
						Console.Write ("Test Purchase ("+product.Label+"): ");
						if(getResult() == CommonDialogResult.OK) {
							if(product.TicketType == InAppPurchaseTicketType.Consumable) {
								if(product.ConsumableTicketCount == 1) Console.WriteLine ("PASS");
								else Console.WriteLine ("FAIL");
								
								Console.Write ("Consume Fail Test: ");
								
								fail = 0;
								for(int i = 0; i < 5; i++) try { dialog.Consume(product.Label); } catch(Exception) {fail++;}
								if(fail == 4) Console.WriteLine ("PASS");
								else Console.WriteLine ("FAIL");

								Console.Write ("Test Consume ("+product.Label+"): ");
								if(getResult() == CommonDialogResult.OK) {
									if(product.ConsumableTicketCount == 0) Console.WriteLine ("PASS");
									else Console.WriteLine ("FAIL");
								}
							}
							else{
								if(product.IsTicketValid) Console.WriteLine ("PASS");
								else Console.WriteLine ("FAIL");
								continue;	
							}
						}
						else {
							Console.WriteLine ("FAIL");
						}
					}
				}
				else {
					Console.WriteLine ("FAIL");
				}
			}
			else {
				Console.WriteLine ("FAIL");
			}
			
			Console.Write ("Test Abort: ");
			dialog.Purchase(dialog.ProductList.Last().Label);
			for(int i = 0; ; i++){
				if (i == 2000) try { dialog.Abort(); } catch (NotSupportedException) {Console.WriteLine ("PASS (win32)");};

				if(dialog.State == CommonDialogState.Finished) {
					if(dialog.Result == CommonDialogResult.Aborted){
						Console.WriteLine ("PASS");	
						break;
					}
					else {
						Console.WriteLine ("FAIL");
						break;
					}
				}
				SystemEvents.CheckEvents();
				
			}
			
			
			
			
		}
		
	}
}

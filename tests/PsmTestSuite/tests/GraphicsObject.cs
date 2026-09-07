using System;
using Sce.PlayStation.Core.Graphics;
using System.Threading;

namespace PsmTestSuite
{
	public class GraphicsObject : PsmTest
	{
		
		
		public override void Run() {
			
			GraphicsContext gCTX = null;
			ShaderProgram prog = null;
			VertexBuffer vbuf = null;
			Texture2D tex = null;
			
			Log ("Create without initalizing graphics ...");
			
			TryThing ("Shader without gCTX", () => {using(new ShaderProgram("/Application/shaders/Simple.cgx")){}});
			TryThing ("Vertex without gCTX", () => {using(new VertexBuffer(10, VertexFormat.Byte2N)){}});
			TryThing ("Texture without gCTX", () => {using(new Texture2D(10, 10, false, PixelFormat.Rgba)){}});
			
			TryThing ("gCTX Create", () => {gCTX = new GraphicsContext();});
			
			Log ("Create after initalizing graphics ...");
			
			TryThing ("Shader with gCTX", () => {using(new ShaderProgram("/Application/shaders/Simple.cgx")){}});
			TryThing ("Vertex with gCTX", () => {using(new VertexBuffer(10, VertexFormat.Byte2N)){}});
			TryThing ("Texture with gCTX", () => {using(new Texture2D(10, 10, false, PixelFormat.Rgba)){}});
			
			Log ("Cross thread create ...");

			Thread t1 = new Thread(delegate()
            {                 
				TryThing ("Cross-Thread Shader with gCTX", () => {using(new ShaderProgram("/Application/shaders/Simple.cgx")){}});
				TryThing ("Cross-Thread Vertex with gCTX", () => {using(new VertexBuffer(10, VertexFormat.Byte2N)){}});
				TryThing ("Cross-Thread Texture with gCTX", () => {using(new Texture2D(10, 10, false, PixelFormat.Rgba)){}});                
            });
			
			t1.Start();
			t1.Join();
			
			TryThing("Delete gCTX ..", () => { gCTX.Dispose(); });

			TryThing ("gCTX Re-Create", () => {gCTX = new GraphicsContext();});
			
			
			TryThing ("Create Shader ..", () => {prog = new ShaderProgram("/Application/shaders/Simple.cgx");});
			TryThing ("Create Vertex ..", () => {vbuf = new VertexBuffer(10, VertexFormat.Byte2N);});
			TryThing ("Create Texture ..", () => {tex = new Texture2D(10, 10, false, PixelFormat.Rgba);}); 
			
			TryThing("Delete gCTX with dangling objects ", () => {gCTX.Dispose();});
			
			TryThing ("Access dangling program", () => { prog.FindUniform("WorldViewProj"); });
			TryThing ("Access dangling vertex", () => { vbuf.SetVertices(0, new short[] {0, 1, 2}); });
			TryThing ("Access dangling texture", () => { tex.SetPixels(0, new int[] {0, 1, 2}); });

			TryThing ("gCTX Re-Create", () => {gCTX = new GraphicsContext();});
			
			TryThing ("Create Shader ..", () => {prog = new ShaderProgram("/Application/shaders/Simple.cgx");});
			TryThing ("Create Vertex ..", () => {vbuf = new VertexBuffer(10, VertexFormat.Byte2N);});
			TryThing ("Create Texture ..", () => {tex = new Texture2D(10, 10, false, PixelFormat.Rgba);}); 
			
			Thread t2 = new Thread(delegate()
            {                 
				TryThing("Delete gCTX cross-thread", () => {gCTX.Dispose();}); 
	        });
						
			t2.Start();
			t2.Join();

			TryThing ("Access dangling program", () => { prog.FindUniform("WorldViewProj"); });
			
			TryThing ("gCTX Re-Create", () => {gCTX = new GraphicsContext();});			
			TryThing ("Access dangling program", () => { prog.FindUniform("WorldViewProj"); });
			
			TryThing ("gCTX Delete", () => { gCTX.Dispose(); });
			
		}
	}
}


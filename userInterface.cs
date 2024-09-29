using System;
using System.Drawing;
using System.ComponentModel;
using System.Windows.Forms;
using System.Runtime.InteropServices;

public class Form1 : Form 
{
	 
	// [DllImport("firewall.dll")]    // THIS LINE WORKS
	 [DllImport("resolvePath.dll", CharSet = CharSet.Unicode, SetLastError = true)]   // THIS LINE WORKS
	static extern int addRule(string pathOfExeFileOrShortcut);

	public Form1()
	{
		/* Button btn = new Button();
		btn.Text = "Click me"; */

		this.AllowDrop = true;
		this.DragDrop += new DragEventHandler(drag_drop);
		this.DragEnter += new DragEventHandler(drag_enter);
		this.CenterToScreen();
		this.Text = "Alto Grade Firewall";

		// Controls.Add(btn);

	}

	private void drag_enter(Object sender, DragEventArgs e)
	{
		 Console.WriteLine("drag_enter");
		e.Effect = DragDropEffects.Move;		
	}

	private void drag_drop(Object sender, DragEventArgs e)
	{
		  Console.WriteLine("drag_drop");
		
			if(e.Data.GetDataPresent(DataFormats.FileDrop) )
			{
				  Console.WriteLine("file drop");

				try{
					string[] files = (string[]) e.Data.GetData(DataFormats.FileDrop);
					for(int i = 0; i < files.Length ; i++)
					{
						  Console.WriteLine(files[i]);

						/**************** EXPERIMENT **************************/
							addRule(files[i]);
						/*****************************************************/
					}

				}catch(Exception ex){
						  Console.WriteLine(ex);
				}
			}
	}



	[STAThread]
	static void Main()
	{
		Application.EnableVisualStyles();
		Application.Run(new Form1());
	}
}
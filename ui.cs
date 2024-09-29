using System;
using System.Drawing;
using System.ComponentModel;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Drawing.Text; 

public class Form1 : Form 
{
	public Form1()
	{
		[DllImport("firewall.dll")]
		 static extern int SampleMethod();

		SampleMethod();
		

		this.CenterToScreen();
		this.Text = "Alto Grade Firewall";
		this.BackColor  =  Color.FromArgb(255, 66, 00);

		FontFamily[] fontFamilies;
		PrivateFontCollection privateFontCollection = new PrivateFontCollection();
		privateFontCollection.AddFontFile("agdollar.ttf");
		fontFamilies = privateFontCollection.Families;

		this.Font = new Font(fontFamilies[0].Name, 16, FontStyle.Regular,GraphicsUnit.Pixel);

		// this.Icon = new Icon("myLogo.png", 16, 16);

		TabControl tabControl1 =  new System.Windows.Forms.TabControl();
		TabPage tabPage1;
		TabPage tabPage2;
		TabPage tabPage3;

		tabPage1 = new TabPage();
		tabPage2 = new TabPage();
		tabPage3 = new TabPage();

		tabPage1.Text = "Add Rules";
		tabPage2.Text = "List Rules";
		tabPage3.Text = "About Us";

		tabControl1.Size = this.Size;
		// tabControl1.Size = new System.Drawing.Size(264, 240);


		tabControl1.TabPages.Add(tabPage1);
		tabControl1.TabPages.Add(tabPage2);
		tabControl1.TabPages.Add(tabPage3);

		tabPage1.BackColor  =  Color.FromArgb(255, 66, 00);
		
		tabControl1.BorderStyle   =  BorderStyle.None;

		Button btn = new Button();
		btn.Text = "Click to select an application";
		btn.AutoSize = true;
		btn.BackColor = Color.FromArgb(00, 00, 00);
		btn.ForeColor = Color.FromArgb(255, 255, 255);
		btn.Click += new EventHandler(button_Click);


		
		tabPage1.Controls.Add(btn);
		Controls.Add(tabControl1);
		
	}

	private void button_Click(object sender, EventArgs e)
	{
		OpenFileDialog openFileDialog1  = new OpenFileDialog();
		openFileDialog1.Filter = "EXE files|*.exe|Shortcut files|*.lnk";
		openFileDialog1.ShowDialog();
	}


	[STAThread]
	static void Main()
	{
		Application.EnableVisualStyles();
		Application.Run(new Form1());
	}
}
using System;

namespace RectangleApplication
{
    class Rectangle
    {
        // 成员变量
        double length;
        double width;
		string info;
        public void Acceptdetails()
        {
            length = 4.5;    
            width = 3.5;
        }
        public double GetArea()
        {
            return length * width;
        }
        public void Display ()
		{
			//info = Console.ReadLine ();
			Console.WriteLine ("Length: {0}", length);
			Console.WriteLine ("Width: {0}", width);
			Console.WriteLine ("Area: {0}", GetArea ());
			
			//Console.WriteLine (info);
        }
    }
    
    class ExecuteRectangle
    {
        static void Main (string[] args)
		{
			Rectangle r = new Rectangle ();
			r.Acceptdetails ();
			r.Display ();
			//string str = Console.ReadLine ();
			//Console.WriteLine (str);
        }
    }
}
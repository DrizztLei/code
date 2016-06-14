using System;
using System.Runtime;
using System.IO;
using System.Text;

namespace AdvanceSQL
{
    public class Scanner
    {
        private StreamReader sr;
        private String path , line;
        public Scanner (String path)
        {
            this.path = path;
            sr = new StreamReader (path, Encoding.Default);
        }
        
        public String getPath()
        {
            return path;
        }

        public void setPath(String path)
        {
            this.path = path;
            sr = new StreamReader (path, Encoding.Default);
        }
        
        public int nextQQ ()
        {
            return 0;
        }
        
        public string nextName ()
        {
            return null;
        }
        
        public int nextAge ()
        {
            return 0;
        }
        
        public bool nextSex ()
        {
            return false;
        }
        
        public String nextLine()
        {
            if ((line = sr.ReadLine ()) != null) 
            {
                return line.ToString();
            }
            else 
            {
                return null;
            }
        }
     
        public void readAll(string path)
        {
            StreamReader sr = new StreamReader(path,Encoding.Default);
            String line;
            while ((line = sr.ReadLine()) != null) 
            {
                Console.WriteLine(line.ToString());
            }
        }
    }
}


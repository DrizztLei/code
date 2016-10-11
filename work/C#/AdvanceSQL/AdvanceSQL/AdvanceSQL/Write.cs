using System;
using System.IO;
using System.Text;
using Trie;

namespace Write
{
    public class Write
    {
        private String path ;
        private String content ;
        FileStream fs;
        StreamWriter sw;
        public Write (String path)
        {
            this.path = path;
            content = null;
            fs = new FileStream(path, FileMode.Create);
            sw = new StreamWriter(fs);
        }
        
        public void changeToContent(Trie.Trie trie)
        {
            
        }
        
        public void setContent(String content)
        {
            
        }
        
        public void setPath(String path)
        {
            this.path = path;
        }
        
        public String getPath()
        {
            return path;
        }
        
        public void save()
        {
            //开始写入
            sw.Write (content);
            //清空缓冲区
            sw.Flush();
            //关闭流
            sw.Close();
            fs.Close();
        }
    }
}


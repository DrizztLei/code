using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;

namespace ConsoleApplication7
{
    class Program
    {
        /*
        static void Main(string[] args)
        {
            //在网站启动时候，批量添加词库。也可以在运行中单独添加新词。
            //注意，核心容器是Static的全局变量，如果一个站运行多个词库，复制Trie类为其他名字，比如TrieFeeling,TrieOtherWord等
            //操作实例可以各个页面随意创建新实例，其中添加操作是影响全局的，搜索是动态的互不干扰的。
            int n = 100;//期望结果大小

            Trie T = new Trie(n);
            int count = 10 * 10000;
            Double M1 = getMem();
            string[] Arr = new string[count];
            for (int i = 0; i < Arr.Length; i++)
            {
                Arr[i] = (Guid.NewGuid()).ToString();
            }
            Stopwatch SW = new Stopwatch();
            Console.WriteLine("原始内存消耗（兆）" + (getMem() - M1));
            M1 = getMem();

            SW.Start();
            for (int i = 0; i < Arr.Length; i++)
            {
                T.AddWord(Arr[i]);
            }
            SW.Stop();
            Console.WriteLine("插入" + Arr.Length + "条单词耗时：" + SW.ElapsedMilliseconds + "毫秒,增加内存消耗（兆）" + (getMem() - M1));
            //搜索测试一
            M1 = getMem();
            Console.WriteLine("-------------输入：‘‘12’’---------------");
            SW.Start();
            List<string> Result1 = T.Search("12");
            SW.Stop();

            Console.WriteLine("查询耗时：" + SW.ElapsedMilliseconds + "毫秒,增加内存消耗（兆）" + (getMem() - M1));
            foreach (string S in Result1)
            {
                Console.WriteLine(S);
            }
            //搜索测试二
            Console.WriteLine("-------------对比测试，常规IndexOf：‘‘12’’---------------");
            int Num = 0;
            SW.Start();
            foreach (string S in Arr)
            {
                if (S.IndexOf("12") == 0)
                {
                    Console.WriteLine(S);
                    Num++;
                }
                if (Num == n)
                {
                    break;
                }
            }
            SW.Stop();
            Console.WriteLine("查询耗时：" + SW.ElapsedMilliseconds + "毫秒");
            Console.WriteLine("仅仅快了一两百毫秒，却消耗了大量内存来存储？");
            Console.Read();
        }
        */
        static Double getMem()
        {
            Process CurrentProcess = Process.GetCurrentProcess();
            return CurrentProcess.WorkingSet64 / 1024 / 1024;//占用内存

        }

    }
}


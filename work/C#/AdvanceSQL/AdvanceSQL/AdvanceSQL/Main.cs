using System;
using Trie;
using AdvanceSQL;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace main{
    public class main
    {
        private static Trie.Trie tree;
        public static void Main(String[] args)
        {
            String path = "/home/elvis/Documents/info";
            readFileFromFile (path);
            while (true) {
                Console.WriteLine ("Input the qq you wanna query : ");
                int qq = Int32.Parse (Console.ReadLine ());
                Console.WriteLine (query(qq));
            }
        }
        
        public static void readFileFromFile(String path)
        {
            if (tree == null) {
                tree = new Trie.Trie (path);
            }
            Scanner scanner = new Scanner (path);
            String info;
            int count = 0;
            int man = "男".GetHashCode ();
            int woman = "女".GetHashCode ();
            while((info = scanner.nextLine()) != null){
                count++;
                count %= 9;
                if (count == 0) {
                    tree.setDescribe (info);
                    tree.insert ();
                } else {
                    switch (count) 
                    {
                    case 1 :
                        tree.setQQ (Int32.Parse(info));
                        break;
                    case 2:
                        tree.setAge (Int32.Parse (info));
                        break;
                    case 3:
                        int message = info.GetHashCode ();
                        if (message == man) {
                            tree.setSex (true);
                        } else if (message == woman) {
                            tree.setSex (false);
                        } else {
                            tree.setSex (null);
                        }
                        break;
                    case 4:
                        tree.setName (info);
                        break;
                    case 5:
                        tree.setGroupID (Int32.Parse (info));
                        break;
                    case 6:
                        tree.setGroupName (info);
                        break;
                    case 7:
                        tree.setPrivilege (info);
                        break;
                    case 8:
                        tree.setCreateTime (info);
                        break;
                    }
                }
            }
        }
        public static String query(int info){
            tree.search (info);
            return tree.outputInfo ();
        }
    }
}

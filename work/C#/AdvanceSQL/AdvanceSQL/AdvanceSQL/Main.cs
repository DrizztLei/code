using System;
using Trie;
using AdvanceSQL;

namespace main{
    public class main
    {
        public static void Main(String[] args)
        {
            String path = "/home/elvis/qq_group.sql";
            Scanner scanner = new Scanner (path);
            String info = scanner.nextLine ();
            if (info == null) 
            {
                Console.WriteLine ("Error for file empty " );
                return;
            }
            Console.WriteLine (info);
            Trie.Trie tree = new Trie.Trie (path);
            tree.insert (info);
            //scanner.readAll (path);
        }
    }
}

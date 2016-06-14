using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ConsoleApplication7
{
    public class Trie
    {
        private static Node Root = new Node(' ');
        private int Capbility = 10;
        public Trie(int capbility)
        {
            Capbility = capbility;
        }
        public void AddWord(string Word)
        {
            List<char> charArr = new List<char>(Word.ToCharArray());
            AddNode(Root, charArr);
        }
        public List<string> Search(string Word)
        {
            List<string> SearchResult = new List<string>();
            //先深度先直线搜索，到达节点，再广度优先搜索。
            Node DFSCurrentNode = Root;
            char[] CharArr = Word.ToCharArray();
            bool IsExists = true;
            for (int i = 0; i < Word.Length; i++)
            {                
                if (DFSCurrentNode.Nodes != null)
                {                
                    //如果找到了
                    if (DFSCurrentNode.Nodes.ContainsKey(CharArr[i]))
                    {
                        //继续找。
                        DFSCurrentNode = DFSCurrentNode.Nodes[CharArr[i]];
                    }
                    else
                    {
                        //没找到中断。
                        IsExists = false;
                    }
                }
            }
            //深搜到了节点，在此节点上广搜。
            if (IsExists)
            {
                List<SearchInfo> CurrentNodeList = new List<SearchInfo>() { new SearchInfo(DFSCurrentNode, Word) };
                BFS(SearchResult, CurrentNodeList);
            }
            return SearchResult;
        }
  

        //广度优先搜索
        private void BFS(List<string> SearchResult, List<SearchInfo> CurrentNodeList)
        {
            //结果足够，退出
            if (SearchResult.Count >= Capbility || CurrentNodeList.Count == 0)
            { return; }
            bool IsOver = false;
            //记录当前节点CurrentNodeList旧长度OldCount，以便于事后移除。
            int OldCount = CurrentNodeList.Count;
            //遍历当前节点集合。
            //foreach (SearchInfo SI in CurrentNodeList)
            for (int i = 0; i < OldCount; i++)
            {
                SearchInfo SI = CurrentNodeList[i];
                ////遍历当前单个节点的子节点。
                if (SI.CurrentNode.Nodes != null)
                {
                    foreach (Node N in SI.CurrentNode.Nodes.Values)
                    {
                        //记录路径。
                        string Word = SI.Word + N.Char;
                        //路径有结尾标记，进入结果。
                        if (N.IsEnd)
                        {
                            SearchResult.Add(Word);
                        }
                        //结果足够，退出
                        if (SearchResult.Count >= Capbility)
                        {
                            IsOver = true;
                            break;
                        }
                        else
                        {
                            //把子节点追加到CurrentNodeList尾部。
                            CurrentNodeList.Add(new SearchInfo(N, Word));
                        }
                    }
                }
                if (IsOver)
                {
                    break;
                }
            }
            //如果结果还不够
            if (!IsOver)
            {
                //移除当前节点,就是CurrentNodeList在L0以前的记录。
                CurrentNodeList.RemoveRange(0, OldCount);
                //进入下一轮搜索。 
                BFS(SearchResult, CurrentNodeList);
            }
        }
        private void AddNode(Node N, List<char> charArr)
        {
            if (charArr.Count > 0)
            {
                char C = charArr[0];
                if (N.Nodes == null)
                {
                    N.Nodes = new Dictionary<char, Node>();
                }
                if (!N.Nodes.ContainsKey(C))
                {
                    Node newNode = new Node(C);
                    N.Nodes.Add(C, newNode);
                }
                if (charArr.Count == 1)
                {
                    N.Nodes[C].IsEnd = true;
                }
                charArr.RemoveAt(0);
                AddNode(N.Nodes[C], charArr);
            }
        }
        //当前搜索的节点信息。相当于键值对

        private bool Contains(Dictionary<char, Node> Nodes, char C)
        {

            return true;
        }
        private class SearchInfo
        {
            public SearchInfo(Node N, string W)
            {
                CurrentNode = N;
                Word = W;
            }
            public string Word;
            public Node CurrentNode;
        }
        private class Node
        {
            public Node(char C)
            {
                Char = C;
            }
            public char Char;
            public bool IsEnd = false;
            public Dictionary<char, Node> Nodes;
        }
    }
}

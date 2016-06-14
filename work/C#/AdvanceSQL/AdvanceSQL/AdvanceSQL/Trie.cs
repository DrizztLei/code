using System;
using Node;
using AdvanceSQL;

namespace Trie
{
    public class Trie
    {
        private Node.Node root;
        
        public Trie (String path)
        {
            root = null;
            init ();
        }
        
        private void init ()
        {
            root = new Node.Node ();
            root.setSon (new SeqDS.SeqList<Node.Node>());
        }
        
        public Node.Node getRoot()
        {
            return root;
        }
        
        public void insert (String info)
        {
            int qq  = 1415076175 , groupId = 23344, age = 20;
            String name = "测试", privilege = "管理员", groupName = "测试群", createTime = "", describe = "没有什么好讲的";
            Boolean? sex = null;
            Boolean? hasgroup = false;
            /*
            Node.Node node = new Node.Node ();
            node.setQQ (qq);
            node.setAge (age);
            node.setInfo (info);
            node.setSex (sex);
            */
            Int64 temp = qq;
            string position = temp.ToString ();
            Console.WriteLine (position);
            Node.Node buoy = getRoot ();
            for (int i = 0; i < position.Length; i++) 
            {
                char shadown = position [i];
                int key = shadown - '0';
                Console.WriteLine (key);
                if (i != position.Length - 1) {
                    if (buoy.getSon () == null) {
                        buoy.getSon ().Append (createNullNode ());
                        buoy.getSon ().GetElem (0).setQQ (key);
                        buoy = buoy.getSon ().GetElem (0);
                    } else {
                        bool flag = true;
                        for(int j = 0 ; j < buoy.getSon().GetLength() ; j++){
                            if (buoy.getSon ().GetElem (j).getQQ () == key) {
                                flag = false;
                                buoy = buoy.getSon ().GetElem (j);
                                break;
                            }
                        }
                        if (flag) {
                            buoy.getSon ().Append (createNullNode ());
                            buoy = buoy.getSon ().GetElem (buoy.getSon ().GetLength () - 1);
                        }
                    }
                } else {
                    if (buoy.getSon () == null) {
                        buoy.setSon (new SeqDS.SeqList<Node.Node>());
                        buoy.getSon ().Append (createNullNode());
                        if (hasgroup == true) {
                            buoy.getSon ().GetElem (0).setQQ (key);
                            buoy.getSon ().GetElem (0).setInfo (describe);
                            buoy.getSon ().GetElem (0).setGroupName (groupName);
                            buoy.getSon ().GetElem (0).setTime (createTime);
                            buoy.getSon ().GetElem (0).setHasGroup (true);
                        } else {
                            buoy.getSon ().GetElem (0).setQQ (key);
                            buoy.getSon ().GetElem (0).setName (name);
                            buoy.getSon ().GetElem (0).setAge (age);
                            buoy.getSon ().GetElem (0).setSex (sex);
                            buoy.getSon ().GetElem (0).setGroupName (groupName);
                            buoy.getSon ().GetElem (0).setGroup (new SeqDS.SeqList<GroupNode.GroupNode>());
                            buoy.getSon ().GetElem (0).getGroup ().GetElem (0).setId (groupId);
                            buoy.getSon ().GetElem (0).getGroup ().GetElem (0).setName (groupName);
                            buoy.getSon ().GetElem (0).getGroup ().GetElem (0).setPrivilege (privilege);
                            buoy.getSon ().GetElem (0).setTime (createTime);   
                            buoy.getSon ().GetElem (0).setHasGroup (false);
                        }
                        //buoy.getSon().GetElem(0).getGroup().GetElem(
                        Console.WriteLine (buoy.getSon().GetElem(0).getQQ());
                    } else {
                        for(int j = 0 ; j < buoy.getSon().GetLength() ; j++)
                        {
                            if (buoy.getSon ().GetElem (j).getQQ () == key) {
                                if (hasgroup == null) {
                                    Console.WriteLine ("Error for the hasGroup flag unknow ");
                                    Environment.Exit (1);
                                } else if (hasgroup == true) {
                                    if (buoy.getSon ().GetElem (j).getHasGroup () == true) {
                                        //so , the info has beent recored.skip it .    
                                    } else {
                                        buoy.getSon ().GetElem (j).setHasGroup (true);
                                        buoy.getSon ().GetElem (j).setGroupName (groupName);
                                        buoy.getSon ().GetElem (j).setInfo (describe);
                                        buoy.getSon ().GetElem (j).setTime (createTime);
                                    }
                                } else if (hasgroup == false) {
                                    if (buoy.getSon ().GetElem (j).getGroup () != null) {
                                        for (int k = 0; k < buoy.getSon ().GetElem (j).getGroup ().GetLength (); k++) {
                                            if(buoy.getSon().GetElem(j).getGroup().GetElem(k).getGroupId() == groupId){
                                                buoy.getSon ().GetElem (j).getGroup ().GetElem (k).setName (groupName);
                                                buoy.getSon ().GetElem (j).getGroup ().GetElem (k).setPrivilege (privilege);
                                                return;
                                            }
                                        }
                                        buoy.getSon ().GetElem (j).getGroup ().Append (new GroupNode.GroupNode ());
                                        int index = buoy.getSon ().GetElem (j).getGroup ().GetLength () - 1;
                                        buoy.getSon ().GetElem (j).getGroup ().GetElem (index).setId (groupId);
                                        buoy.getSon ().GetElem (j).getGroup ().GetElem (index).setName (groupName);
                                        buoy.getSon ().GetElem (j).getGroup ().GetElem (index).setPrivilege (privilege);
                                    } else {
                                        buoy.getSon ().GetElem (j).setGroup (new SeqDS.SeqList<GroupNode.GroupNode> ());
                                        buoy.getSon ().GetElem (j).getGroup ().Append (new GroupNode.GroupNode ());
                                        buoy.getSon ().GetElem (j).getGroup ().GetElem (0).setId (groupId);
                                        buoy.getSon ().GetElem (j).getGroup ().GetElem (0).setName (groupName);
                                        buoy.getSon ().GetElem (j).getGroup ().GetElem (0).setPrivilege (privilege);
                                    }
                                }
                                break;
                            }
                        }
                    }
                }
            }
        }
        
        public Node.Node createNullNode()
        {
            return new Node.Node ();
        }
        
        public Node.Node search (int info)
        {
            Int64 temp = info;
            String shadow = temp.ToString ();
            Node.Node aim = getRoot ();
            for (int i = 0; i < shadow.Length; i++) {
                char key = shadow [i];
                if (aim == null) {
                    return null;
                } else if (aim.getSon () == null) {
                    for (int j = 0; j < aim.getSon ().GetLength (); j++) {
                        
                    }
                } else {
                    
                }
            }
            return null;
        }
        
        public void save ()
        {
            
        }

    }
}
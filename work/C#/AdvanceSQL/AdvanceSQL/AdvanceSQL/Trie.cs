using System;
using Node;
using AdvanceSQL;
using System.Linq;
using System.Collections.Generic;
using System.Text;

namespace Trie
{
    public class Trie
    {
        private Node.Node root;
        private String output;
        private int qq , groupId , age ;
        private String name , privilege , groupName , createTime , describe;
        private Boolean? sex;
        private Boolean? hasgroup;
        
        public void setCreateTime(String createTime){
            this.createTime = createTime;
        }
        
        public void setDescribe(String describe){
            this.describe = describe;
        }
        
        public void setQQ(int qq)
        {
            this.qq = qq;
        }
        
        public void setGroupID(int id)
        {
            this.groupId = id;
        }
        
        public void setAge(int age)
        {
            this.age = age;
        }
        
        public void setName(String name){
            this.name = name;
        }
        
        public void setPrivilege(String privilege){
            this.privilege = privilege;
        }
        
        public void setGroupName(String groupName){
            this.groupName = groupName;
        }
        
        public void setSex(Boolean? sex){
            this.sex = sex;
        }
        
        public void setHasGroup(Boolean? hasgroup){
            this.hasgroup = hasgroup;
        }
        
        public Trie (String path)
        {
            root = null;
            init ();
        }
        
        public String outputInfo(){
            String temp = new String(output.ToCharArray());
            output = null;
            return temp;
        }
            
        private void init ()
        {
            root = new Node.Node ();
        }
        public Node.Node getRoot()
        {
            return root;
        }
        public void insert ()
        {
            if (age == -1 && sex == null && name.GetHashCode () == "NULL".GetHashCode ()) {
                setHasGroup (true);
            } else {
                setHasGroup (false);
            }
            Int64 temp = qq;
            string position = temp.ToString ();
            Node.Node buoy = getRoot ();
            for (int i = 0; i < position.Length; i++)
            {
                char shadown = position [i];
                int key = shadown - '0';
                if (i != position.Length - 1) {
                    if (buoy.getSon () == null) {
                        buoy.setSon (new LinkedList<Node.Node> ());
                        buoy.getSon ().AddLast (createNullNode ());
                        buoy.getSon ().ElementAt (0).setQQ (key);
                        buoy = buoy.getSon ().ElementAt (0);
                    } else {
                        bool flag = true;
                        for(int j = 0 ; j < buoy.getSon().Count() ; j++){
                            if (buoy.getSon ().ElementAt(j).getQQ () == key) {
                                flag = false;
                                buoy = buoy.getSon ().ElementAt (j);
                                break;
                            }
                        }
                        if (flag) {
                            buoy.getSon ().AddLast (createNullNode ());
                            buoy = buoy.getSon ().ElementAt (buoy.getSon ().Count () - 1);
                        }
                    }
                } else {
                    if (buoy.getSon () == null) {
                        buoy.setSon (new LinkedList<Node.Node> ());
                        buoy.getSon ().AddLast (createNullNode ());
                        if (hasgroup == true) {
                            buoy.getSon ().ElementAt (0).setQQ (key);
                            buoy.getSon ().ElementAt (0).setInfo (describe);
                            buoy.getSon ().ElementAt (0).setGroupName (groupName);
                            buoy.getSon ().ElementAt (0).setTime (createTime);
                            buoy.getSon ().ElementAt (0).setHasGroup (true);
                        } else {
                            buoy.getSon ().ElementAt (0).setQQ (key);
                            buoy.getSon ().ElementAt (0).setAge (age);
                            buoy.getSon ().ElementAt (0).setSex (sex);
                            buoy.getSon ().ElementAt (0).setName (name);
                            buoy.getSon ().ElementAt (0).setGroup (new LinkedList<GroupNode.GroupNode>());
                            buoy.getSon ().ElementAt (0).getGroup ().AddLast (new GroupNode.GroupNode ());
                            buoy.getSon ().ElementAt (0).getGroup ().ElementAt (0).setId (groupId);
                            buoy.getSon ().ElementAt (0).getGroup ().ElementAt (0).setName (groupName);
                            buoy.getSon ().ElementAt (0).getGroup ().ElementAt (0).setPrivilege (privilege);
                        }
                    } else {
                        for(int j = 0 ; j < buoy.getSon().Count() ; j++)
                        {
                            if (buoy.getSon ().ElementAt (j).getQQ () == key) {
                                if (hasgroup == null) {
                                    Environment.Exit (1);
                                } else if (hasgroup == true) {
                                    buoy.getSon ().ElementAt (j).setHasGroup (true);
                                    buoy.getSon ().ElementAt (j).setQQ (key);
                                    buoy.getSon ().ElementAt (j).setGroupName (groupName);
                                    buoy.getSon ().ElementAt (j).setInfo (describe);
                                    buoy.getSon ().ElementAt (j).setTime (createTime);
                                } else if (hasgroup == false) {
                                    buoy.getSon ().ElementAt (j).setQQ (key);
                                    buoy.getSon ().ElementAt (j).setAge (age);
                                    buoy.getSon ().ElementAt (j).setSex (sex);
                                    buoy.getSon ().ElementAt (j).setName (name);
                                    if (buoy.getSon ().ElementAt (j).getGroup () != null) {
                                        for (int k = 0; k < buoy.getSon ().ElementAt (j).getGroup ().Count (); k++) {
                                            if(buoy.getSon().ElementAt(j).getGroup().ElementAt(k).getGroupId() == groupId){
                                                buoy.getSon ().ElementAt (j).getGroup ().ElementAt (k).setName (groupName);
                                                buoy.getSon ().ElementAt (j).getGroup ().ElementAt (k).setPrivilege (privilege);
                                                return;
                                            }
                                        }
                                        buoy.getSon ().ElementAt (j).getGroup ().AddLast (new GroupNode.GroupNode ());
                                        int index = buoy.getSon ().ElementAt (j).getGroup ().Count () - 1;
                                        buoy.getSon ().ElementAt (j).getGroup ().ElementAt (index).setId (groupId);
                                        buoy.getSon ().ElementAt (j).getGroup ().ElementAt (index).setName (groupName);
                                        buoy.getSon ().ElementAt (j).getGroup ().ElementAt (index).setPrivilege (privilege);
                                    } else {
                                        buoy.getSon ().ElementAt (j).setGroup (new LinkedList<GroupNode.GroupNode> ());
                                        buoy.getSon ().ElementAt (j).getGroup ().AddLast (new GroupNode.GroupNode ());
                                        buoy.getSon ().ElementAt (j).getGroup ().ElementAt (0).setId (groupId);
                                        buoy.getSon ().ElementAt (j).getGroup ().ElementAt (0).setName (groupName);
                                        buoy.getSon ().ElementAt (j).getGroup ().ElementAt (0).setPrivilege (privilege);
                                    }
                                }
                                return;                                   
                            }
                        }
                        buoy.getSon ().AddLast (createNullNode ());
                        int shadow = buoy.getSon ().Count () - 1;
                        if (hasgroup == null) {
                            Environment.Exit (1);
                        } else if (hasgroup == true) {
                                buoy.getSon ().ElementAt (shadow).setQQ (key);
                                buoy.getSon ().ElementAt (shadow).setHasGroup (true);
                                buoy.getSon ().ElementAt (shadow).setGroupName (groupName);
                                buoy.getSon ().ElementAt (shadow).setInfo (describe);
                                buoy.getSon ().ElementAt (shadow).setTime (createTime);
                        } else if (hasgroup == false) {
                            buoy.getSon ().ElementAt (shadow).setQQ (key);
                            buoy.getSon ().ElementAt (shadow).setAge (age);
                            buoy.getSon ().ElementAt (shadow).setSex (sex);
                            buoy.getSon ().ElementAt (shadow).setName (name);
                            if (buoy.getSon ().ElementAt (shadow).getGroup () != null) {
                                for (int k = 0; k < buoy.getSon ().ElementAt (shadow).getGroup ().Count (); k++) {
                                    if(buoy.getSon().ElementAt(shadow).getGroup().ElementAt(k).getGroupId() == groupId){
                                        buoy.getSon ().ElementAt (shadow).getGroup ().ElementAt (k).setName (groupName);
                                        buoy.getSon ().ElementAt (shadow).getGroup ().ElementAt (k).setPrivilege (privilege);
                                        return;
                                    }
                                }
                                buoy.getSon ().ElementAt (shadow).getGroup ().AddLast (new GroupNode.GroupNode ());
                                int index = buoy.getSon ().ElementAt (shadow).getGroup ().Count () - 1;
                                buoy.getSon ().ElementAt (shadow).getGroup ().ElementAt (index).setId (groupId);
                                buoy.getSon ().ElementAt (shadow).getGroup ().ElementAt (index).setName (groupName);
                                buoy.getSon ().ElementAt (shadow).getGroup ().ElementAt (index).setPrivilege (privilege);
                            } else {
                                buoy.getSon ().ElementAt (shadow).setGroup (new LinkedList<GroupNode.GroupNode> ());
                                buoy.getSon ().ElementAt (shadow).getGroup ().AddLast (new GroupNode.GroupNode ());
                                buoy.getSon ().ElementAt (shadow).getGroup ().ElementAt (0).setId (groupId);
                                buoy.getSon ().ElementAt (shadow).getGroup ().ElementAt (0).setName (groupName);
                                buoy.getSon ().ElementAt (shadow).getGroup ().ElementAt (0).setPrivilege (privilege);
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
            for (int i = 0; i < shadow.Length; i++)
            {
                int key = shadow [i] - '0';
                if(i != shadow.Length - 1)
                {
                    if (aim == null)
                    {
                        return null;
                    }
                    else
                    {
                        bool flag = true;
                        for (int j = 0; j < aim.getSon ().Count (); j++)
                        {
                            if(aim.getSon().ElementAt(j).getQQ() == key){
                                flag = false;
                                aim = aim.getSon().ElementAt(j);
                                break;
                            }
                        }
                        if(flag)
                        {
                            return null;
                        }
                    }
                }
                else
                {
                    if (aim.getSon () == null)
                    {
                        return null;
                    }
                    else
                    {
                        for (int j = 0; j < aim.getSon ().Count (); j++){
                            if(aim.getSon().ElementAt(j).getQQ() == key){
                                Node.Node node = aim.getSon ().ElementAt (j);
                                this.output = "QQ : " + info;
                                if (node.getName ().GetHashCode () != "NULL".GetHashCode ()) {
                                    this.output += "\n昵称 : " + node.getName ();
                                }
                                if (node.getHasGroup () == true) {
                                    this.output += "\n群名 : " + node.getGroupName ();
                                    this.output += "\n创建时间 : " + node.getTime ();
                                }
                                if(node.getAge() != -1 ){
                                    this.output += "\n年龄 : " + node.getAge();
                                }
                                if (node.getSex () != null) {
                                    this.output += "\n性别 : " + (node.getSex () == true ? "男" : "女");
                                }
                                if (node.getGroup () != null) {
                                    for (int k = 0; k < node.getGroup ().Count (); k++) {
                                        this.output += "\n群号 : " + node.getGroup ().ElementAt (k).getGroupId () +
                                                  "\n群内昵称 : " + node.getGroup ().ElementAt (k).getName () +
                                                  "\n群内权限 : " + node.getGroup ().ElementAt (k).getPrivilege ();
                                    }
                                }
                                return aim.getSon().ElementAt(j);
                            }
                        }
                    }
                }
            }
            return null;
        }
        public void save (String path)
        {
            output = path;
            Node.Node node = getRoot();
            if(node == null || node.getSon() == null || node.getSon().Count() == 0){
                return ;
            }else{
                save(node);
            }
        }
        public void save(Node.Node node){
            if(node.getSon() == null || node.getSon().Count() == 0)
            {
                return;
            }
            for(int i = 0 ; i < node.getSon().Count() ; i++)
            {
                if(node.getSon().ElementAt(i).getName() != null)
                {
                    //show(node.getSon().ElementAt(i));
                    writeInFile(node.getSon().ElementAt(i));
                }
                save(node.getSon().ElementAt(i));
            }
        }
        public void writeInFile(Node.Node node){
            
        }
    }
}

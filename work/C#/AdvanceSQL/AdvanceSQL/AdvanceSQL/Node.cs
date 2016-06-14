using System;
using SeqDS;
using GroupNode;

namespace Node
{
    public class Node
    {
        
        private String name;
        private String groupName;
        private int? qq, age;
        private Boolean? sex;
        private SeqList<Node> son;
        private SeqList<GroupNode.GroupNode> group;
        private Boolean hasGroup;
        private String info;
        private String time;
        
        public Node()
        {
            name = null;
            qq = age = null;
            sex = null;
            group = null;
            hasGroup = false;
            info = null;
        }
        
        public String getTime(){
            return time;
        }
        
        public void setTime(String time){
            this.time = time;
        }  
        
        
        public String getGroupName(){
            return groupName;
        }
        
        public void setGroupName(String groupName){
            this.groupName = groupName;
        }
        
        public void setSon(SeqList<Node> son)
        {
            this.son = son;
        }
        
        public void setHasGroup(Boolean hasGroup)
        {
            this.hasGroup = hasGroup;
        }
        
        public Boolean getHasGroup()
        {
            return hasGroup;
        }
        
        public void setInfo(String info)
        {
            this.info = info;
        }
        
        public String getInfo()
        {
            return info;
        }
        
        public SeqList<Node> getSon()
        {
            return son;
        }
        
        public string getName()
        {
            return name;
        }
        
        public int? getQQ()
        {
            return qq;
        }
        
        public int? getAge()
        {
            return age;
        }
        
        public Boolean? getSex()
        {
            return sex;
        }
        
        public SeqList<GroupNode.GroupNode> getGroup()
        {
            return group;
        }
        
        public void setName (string name)
        {
            this.name = name;
        }
        
        public void setQQ (int qq)
        {
            this.qq = qq;
        }
        
        public void setAge (int age)
        {
            this.age = age;
        }
        
        public void setSex (Boolean? sex)
        {
            this.sex = sex;
        }
        
        public void setGroup (SeqList<GroupNode.GroupNode> group)
        {
            this.group = group;
        }
             
        public Node (int qq , Boolean? sex = null, int age = -1 , string name = null , SeqList<GroupNode.GroupNode> group = null , SeqList<Node> son = null)
        {
            this.qq = qq;
            this.age = age;
            this.name = name;
            this.son = son;
            this.sex = sex;
        }
    }
}


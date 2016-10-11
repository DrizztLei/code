using System;
using System.Collections.Generic;
using System.Text;

namespace GroupNode
{
    public class GroupNode
    {
        private String name = null;
        private int groupId;
        private String privilege = null;
        
        public void setName(String name)
        {
            this.name = name;
        }
        
        public String getName()
        {
            return name;
        }
        
        public int getGroupId()
        {
            return groupId;
        }
        
        public String getPrivilege()
        {
            return privilege;
        }
        
        public void setId(int id)
        {
            this.groupId = id;   
        }
        
        public void setPrivilege(String privilege)
        {
            this.privilege = privilege;
        }
        
        public GroupNode ()
        {
            this.name = null;
        }
    }
}
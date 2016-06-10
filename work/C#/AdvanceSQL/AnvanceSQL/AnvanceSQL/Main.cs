using System;

namespace AdvanceSQL
{
  public class TrieTree    
   {        
     TrieNode _root = null;  
     private TrieTree()     
   {           
     _root = new TrieNode(char.MaxValue,0);  
     charCount = 0;   
   }       
      static TrieTree _instance = null; 
     public static TrieTree GetInstance()   
   {            
   if (_instance == null)        
   {             
   _instance = new TrieTree();       
   }           
   return _instance;   
   }        
   public TrieNode Root   
   {           
   get { return _root; 
   }   
   }        
   public void AddWord(char ch) 
   {           
TrieNode newnode=_root.AddChild(ch);   
newnode.IncreaseFrequency();           
newnode.WordEnded = true;      
}        int charCount;    
public void AddWord(string word)   
{          
if (word.Length == 1)     
{               
AddWord(word[0]);     
charCount++;       
}         
else    
{                 
char[] chars=word.ToCharArray();     
TrieNode node = _root;           
charCount += chars.Length;      
for (int i = 0; i < chars.Length; i++)  
{                    
TrieNode newnode=node.AddChild(chars[i]);    
newnode.IncreaseFrequency();           
node = newnode;           
}           
node.WordEnded = true;  
}       
}       
public int GetFrequency(char ch)   
{           
TrieNode matchedNode = _root.Children.FirstOrDefault(n => n.Character == ch);  
if (matchedNode == null)      
{               
return 0;        
}           
return matchedNode.Frequency;  
}       
public int GetFrequency(string word)
{        
if (word.Length == 1) 
{              
return GetFrequency(word[0]); 
}            
else      
{            
char[] chars = word.ToCharArray(); 
TrieNode node = _root;        
for (int i = 0; i < chars.Length; i++)   
{                 
if (node.Children == null)   
return 0;              
TrieNode matchednode = node.Children.FirstOrDefault(n => n.Character == chars[i]);
if (matchednode == null)          
{                      
return 0;         
}                  
node = matchednode;    
}              
if (node.WordEnded == true)        
return node.Frequency;       
else                   
return -1;           
}      
}   
}
}

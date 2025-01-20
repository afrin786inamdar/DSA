#include<iostream>
using namespace std;

class Node
{
public:

 string data;
 Node *children[10];
 int childCount;
 
  public:
  
   Node(const string &value)
   {
     data=value;
     childCount=0;
     for(int i=0;i<10;i++)
     {
        children[i]=nullptr;
     }
   }
   
    void addChild(Node* child)
    {
      if(childCount<10)
      {
         children[childCount++]=child;
      }
    }
    
    void printTree(int level=0)
    {
      for(int i=0;i<level;i++)cout<<" ";
      cout<<data<<endl;
      for(int i=0;i<childCount;i++)
      {
        children[i]->printTree(level+1);
      }
   }
   };
   int main()
   {
     Node* book=new Node("BOOK");
     
     Node* chapter1=new Node("CHAPTER1");
      Node* chapter2=new Node("CHAPTER2");
      
      book->addChild(chapter1);
      book->addChild(chapter2);
      
       Node* section1=new Node("SECTION1");
      Node* section2=new Node("SECTION2");
      
      chapter1->addChild(section1);
      chapter1->addChild(section2);
      
      Node* sub_section1=new Node("SUB_SECTION1");
      Node* sub_section2=new Node("SUB_SECTION2");
      
      section1->addChild(sub_section1);
      section1->addChild(sub_section2);
      
      cout<<"Tree Structure:"<<endl;
      book->printTree();
      
      return 0;
      }
      
      
   

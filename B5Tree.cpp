#include<iostream>
using namespace std;

const int MAX_NODES=100;
const int MAX_CHILD=10;

string nodeName[MAX_NODES];
int children[MAX_NODES][MAX_CHILD];
int childCount[MAX_NODES]={0};
int nodeCount=0;

int addNode(const string &name)
{
  nodeName[nodeCount]=name;
  return nodeCount++;
 }
 
 void addChild(int parent,int child)
 {
   children[parent][childCount[parent]]=child;
   childCount[parent]++;
   
 }
 
 void printTree(int nodeIndex,string prefix="")
 {
 cout<<prefix<<nodeName[nodeIndex]<<endl;
 for(int i=0;i<childCount[nodeIndex];i++)
 {
 printTree(children[nodeIndex][i],prefix + " ");
 }
 }
 int main()
 {
   int book=addNode("Book");
   int chapter1=addNode("Chapterc 1");
   int chapter2=addNode("Chapterc 2");
   int section1=addNode("Section  1.1");
   int section2=addNode("Section  1.2");
   
   int subsection1=addNode("Subsection 1.1.1");
   
   
   addChild(book,chapter1);
   addChild(book,chapter2);
   addChild(chapter1,section1);
   addChild(chapter1,section2);
   addChild(section1,subsection1);
   
  printTree(book);
  return 0;
  } 
   
   
   
    
    
   

using namespace std;
#include <string.h>
#include <string>
#include "FamilyTree.hpp"
#include <stdio.h>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <exception>
#include <vector>



namespace family
{

Tree &Tree::addFather(string child, string dad)
 {
   Tree *sun = findName(this, child);
   if(sun!=nullptr && sun->father==nullptr){
     sun->father= new Tree (dad);
     Tree *father=sun->father;
     father->sun=sun;
     father->sex="male";
     father->rank=(sun->rank+1);

  return *this;
   }
   else{
      std::string errorMessage = std::string("unrelated");
   throw std::out_of_range(errorMessage);
   }
    
}


Tree &Tree::addMother(string child, string mom)
{
    Tree *sun = findName(this, child);
   if(sun!=nullptr && sun->mother==nullptr){
     sun->mother= new Tree (mom);
Tree *mother=sun->mother;
     mother->sun=sun;
     mother->sex="female";
     mother->rank=(sun->rank+1);
  return *this;
   }
   else{
      std::string errorMessage = std::string("unrelated");
   throw std::out_of_range(errorMessage);
   }
}

string Tree::relation(string s)
{
  string relat="";
  if(s==this->name)
    relat="me";
  else
  if(s==this->mother->name)
  relat ="mother";
  else if(s==this->father->name)
  relat ="father";
  else {
    Tree *re = findName(this,s);
    if(re!=nullptr){
      if(re->sex=="male"){
        for(int i=0; i<re->rank-2;i++)
        relat=relat+"great-";
        relat=relat+"grandfather";
      }
      else{
        for(int i=0; i<re->rank-2;i++)
        relat=relat+"great-";
        relat=relat+"grandmother";
      }
      
    }

  }  if(relat==""){
      relat="unrelated";
   }
  return relat;
    
}

string Tree::find(string s)
 {
if(s=="root" || s=="me") return this->name;
if(s=="mother" && this->mother!=nullptr) return this->mother->name;
if(s=="father" && this->father!=nullptr ) return this->father->name;

 std::vector<std::string> v = split (s, '-');
 int n=v.size();
 string name ="";
 if(v[n-1]=="grandmother")
   name = nameF(this,v.size(),"female");
 if(v[n-1]=="grandfather")  name = nameF(this,v.size(),"male");

if(name!="")
    return name;
 else{
      std::string errorMessage = std::string("The tree cannot handle the '" +s+"' relation");
   throw std::out_of_range(errorMessage);
   }

}


std::vector<std::string> Tree::split (const string &s, char delim) {
    vector<string> result;
    stringstream ss (s);
    string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result;
}

std::string Tree::nameF(Tree *t,int size,string sex1){
if(size==0) return "";
if((t->rank-1)==size) {
  if(t->sex==sex1){
  return t->name;
}}
if(t->mother!=nullptr){
 string name= nameF(t->mother,size,sex1);
 if(name!="") return name;
}

if(t->father!=nullptr){
 string name= nameF(t->father,size,sex1);
 if(name!="") return name;
}

return "";
}

void Tree::remove(string s)
{
Tree *name= findName(this,s);
if(name!=nullptr){
removeF(name);
}
else{
   std::string errorMessage = std::string("unrelated");
   throw std::out_of_range(errorMessage);
}
}

void Tree::removeF(Tree *name){
  if(name->sun->mother==name) name->sun->mother=nullptr;
  if(name->sun->father==name) name->sun->father=nullptr;
  delete name;
  return;

}

void Tree::display()
{
   print2DUtil(this, 0);
}

void Tree::print2DUtil(Tree *root, int space)  
{  
    // Base case  
    if (root == NULL)  
        return;  
  int COUNT=10;
    // Increase distance between levels  
    space += COUNT;  
  
    // Process right child first  
    print2DUtil(root->mother, space);  
  
    // Print current node after space  
    // count  
    cout<<endl;  
    for (int i = COUNT; i < space; i++)  
        cout<<" ";  
    cout<<root->name<<"\n";  
  
    // Process left child  
    print2DUtil(root->father, space);  
}  

Tree *Tree::findName(Tree *t,string name1){
    if (t->name.compare(name1)==0 ){
   return t;
   }
  
if(t->mother!=nullptr){
  Tree *temp =  findName(t->mother,name1);
  if(temp!=nullptr)
  return temp;
}
if(t->father!=nullptr){  
   Tree *temp =  findName(t->father,name1);
  if(temp!=nullptr)
  return temp;
}
return nullptr;
}


} // namespace family
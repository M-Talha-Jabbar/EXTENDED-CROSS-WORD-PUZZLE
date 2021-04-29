#include<iostream>
#include<fstream>
#define RED 1
#define BLACK 0
using namespace std;
struct dictionary{
	string word;
	string meaning;
};
struct Node{
	dictionary data;
	Node *left,*right,*parent;
	int color; //0 black 1 red
	Node(){
		color= 1;
		left=right=parent=NULL;
	}
};
class RBT{
	public:
		Node *root;
	RBT(){
		root=NULL;
	}
	Node* BSTinsert(Node *&root,Node *&pt)
	{
		if(root==NULL)
		{ //cout<<pt->data.word<<endl;
			return pt;
		}
	    if(pt->data.word>=root->data.word)
	    {
	    	root->right=BSTinsert(root->right,pt);
	    	root->right->parent=root;
		}
		else if(pt->data.word<root->data.word)
		{
			root->left=BSTinsert(root->left,pt);
			root->left->parent=root;
		}
		else{
		cout<<"Eqi"<<pt->data.word;
		}
		return root;
	}
	void RR(Node *&root,Node *&p)
	{
		Node *x=p->left;
		Node *y=x->right;
		if(y!=NULL)
		y->parent=p;
		x->parent=p->parent;
		x->right=p;
		p->left=y;
		if(p->parent==NULL)
		root=x;
		else if(p==p->parent->left)
		      p->parent->left=x;
		else 
			  p->parent->right=x;
			  p->parent=x;
			}
	void LL(Node *&root, Node *&p){
		Node *x=p->right;
		Node *y=x->left;
		p->right=y;
		if(y!=NULL)
		y->parent=p;
		x->parent=p->parent;
		if(p->parent==NULL)
		{
			root=x;
		}
		else if(p==p->parent->left)
		        p->parent->left=x;
		 else
		 p->parent->right=x;
		 x->left=p;
		 p->parent=x; 
	}
	void fixViolation(Node *&root, Node *&pt) 
{ 
    Node *parent_pt = NULL; 
    Node *grand_parent_pt = NULL; 
  
    while ((pt != root)&& (pt->color != BLACK) && (pt->parent->color == RED)) 
    { 
  
        parent_pt = pt->parent; 
        grand_parent_pt = pt->parent->parent; 
  
        if (parent_pt == grand_parent_pt->left) 
        { 
  
            Node *uncle_pt = grand_parent_pt->right; 
      if (uncle_pt != NULL && uncle_pt->color == RED) 
            { 
                grand_parent_pt->color = RED; 
                parent_pt->color = BLACK; 
                uncle_pt->color = BLACK; 
                pt = grand_parent_pt; 
            } 
  
            else
            { 
                if (pt == parent_pt->right) 
                { 
                    LL(root, parent_pt); 
                    pt = parent_pt; 
                    parent_pt = pt->parent; 
                } 
  
                RR(root, grand_parent_pt); 
                swap(parent_pt->color, grand_parent_pt->color); 
                pt = parent_pt; 
            } 
        } 
  
        else
        { 
            Node *uncle_pt = grand_parent_pt->left; 
  
            if ((uncle_pt != NULL) && (uncle_pt->color == RED)) 
            { 
                grand_parent_pt->color = RED; 
                parent_pt->color = BLACK; 
                uncle_pt->color = BLACK; 
                pt = grand_parent_pt; 
            } 
            else
            { 
                if (pt == parent_pt->left) 
                { 
                    RR(root, parent_pt); 
                    pt = parent_pt; 
                    parent_pt = pt->parent; 
                } 
  
                LL(root, grand_parent_pt); 
                swap(parent_pt->color, grand_parent_pt->color); 
                pt = parent_pt; 
                
            } 
        }
		if(pt->parent==NULL)
                break; 
    } 
    root->color = BLACK; 
} 
bool  search(Node *root,string data)
{
	if(root==NULL)
	{
	 cout<<"NOT FOUND IN DICTIONARY !"<<endl;
	return false;
		}	
	if(root->data.word>data)
	{
	return search(root->left,data);
	}
	else if(root->data.word<data)
	return search(root->right,data);
	else{
		cout<<"Word : "<<root->data.word<<"\nMeaning : "<<root->data.meaning<<endl;
		return true;
 	}
}

void insert(dictionary &data) 
{ 
if(data.word[0]>=65&&data.word[0]<='Z'||(data.word[0]>=97&&data.word[0]<='z'))
{
	  	  Node *pt = new Node;
	pt->data=data; 
   root = BSTinsert(root, pt); 
  fixViolation(root, pt); 
}} 
};
void inorder(Node *root)
{
	if(root==NULL)
	return;
	inorder(root->left);
	cout<<root->data.word<<" ";	
	inorder(root->right);
}
bool shelp(RBT *ob,string word)
{
	for(int i=0;word[i]!='\0';i++)
	{
		if(i==0)
		{
		word[i]=word[i]<='Z'?word[i]:word[i]-32;
		}else
		word[i]=word[i]<='Z'?word[i]+32:word[i];

	}
	return ob->search(ob->root,word);
}
RBT ob;
void load(){
	dictionary d;
	ifstream fp;
	fp.open("myfile.txt");
	while(!fp.eof())
	{
	
	fflush(stdin);
	fp>>d.word;
	getline(fp,d.meaning);
	ob.insert(d);
	}
	fp.close();
}
bool SearchWord(string word){
	return shelp(&ob,word);
}

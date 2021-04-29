#include<iostream>
#include "Dict.h" //dictionary program with red black tree;
#include<iomanip>//for formated output
#include<unistd.h>  //sleep()
#include<fstream>   //filling
#include<cstdlib>   // system(cls), rand(), srand()
#include<ctime>     // time()
#include<windows.h> //Setting cursor positions
#include<pthread.h> //Multithreading


using namespace std;
bool timeup=0;
int score=-1;


COORD CursorPosition()
{
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cbsi))
    {
        return cbsi.dwCursorPosition;
    }
    else
    {
        // The function failed. Call GetLastError() for details.
        COORD invalid = { 0, 0 };
        return invalid;
    }
}


struct Snode{
	COORD p;
	Snode *next;
	Snode(){
		next=NULL;
	}
	
};


class Stack{
Snode *head;
	public:
		Stack(){
			head=NULL;
		}
		push(COORD pos)
		{
			if(!head)
			{
				head=new Snode;
				head->p=pos;
			}
			else{
				Snode *temp=new Snode;
				temp->next=head;
				temp->p=pos;
				head=temp;
			}
		}
		COORD pop()
		{
			if(head)
			{
				Snode *temp=head;
				COORD t;
				t=temp->p;
				head=head->next;
				delete temp;
				return t;
			}
			else
			{
				cout<<"Underflow";
			}
		}
	
};
Stack cord;//cordinates



COORD p;
void gotoxy(int x,int y)
{
	COORD cord;
	cord.X=x;
	cord.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),cord);
} 
time_t beg,end;
void* timethread(void *len)//thread function
{  //  pthread_mutex_lock(&lock);
	while((*(int*)len*60-120)-(end-beg)!=0)
	{
	end=time(NULL);
	//cout<<end-beg;
	sleep(1);
	if(((*(int*)len*60-120)-(end-beg))%1==0)
	{     
		p=CursorPosition();
		cord.push(p);
		gotoxy(48,0);
		cout<<setfill('0')<<setw(4)<<(*(int*)len*60-120)-(end-beg);
		p=cord.pop();
		gotoxy(p.X,p.Y);
		
	}
	 
	//gotoxy(40,0);
	//time_t myt=time(NULL);
	//cout<<ctime(&myt);
	} 
	 timeup=1;
	  //  pthread_mutex_unlock(&lock); 
}


void ScoreUpdate()
{
	p=CursorPosition();
	cord.push(p);
	gotoxy(100,0);
	cout<<"YOUR SCORE = "<<setfill('0')<<setw(3)<<++score;
	p=cord.pop();
	gotoxy(p.X,p.Y);
}


struct  node{
	string word;
	int height;
	node *left,*right;
	node(){
		height=1;
		left=NULL;
		right=NULL;
	}
};


class Avl{
	
	public:
		node *root;
		 Avl(){
		root=NULL;
	}
	int h(node *n)
	{
		if(!n)
		return 0;
		return n->height;
	}
	node* Rrotate(node* n){
		node * l=n->left;
		node *sub=l->right;
		l->right=n;
		n->left=sub;
    n->height = max(h(n->left),h(n->right)) + 1;
	l->height = max(h(l->left),h(l->right)) + 1;  
	return l;  
	}
	node *Lrotate(node *n)
	{
		node *r=n->right;
		node *sub=r->left;
		r->left=n;
		n->right=sub;
		n->height = max(h(n->left),h(n->right))+1;  
		r->height = max(h(r->left),h(r->right))+1;  
	    return r;
	}
	node* insert(node *root,string word)
	{
		if(!root)
		{
			root=new node;
			root->word=word;
			return root;
		}
		if(word>root->word)
		root->right=insert(root->right,word);
		else if(word<root->word)
		root->left=insert(root->left,word);
		root->height=max(h(root->left),h(root->right))+1;
		int balance =h(root->left)-h(root->right);
		//LL
		if(balance>1&&word<root->left->word)
		{
			return Rrotate(root);
		}
		   //RR
		if(balance<-1&&word>root->right->word)
		{
			return Lrotate(root);
		}
		   //LR
		if(balance>1&&word>root->left->word)
		{
			root->left=Lrotate(root->left);
			return Rrotate(root);
		}	
		//RL	
		if(balance<-1&&word<root->right->word)
		{
			root->right= Rrotate(root->right);
			return Lrotate(root);
		}
		return root;
	}
	
	bool repeat(node *root,string word)
		{
			if(root==NULL)
			return 0;
			node *temp=root;
			while(temp)
			{
				if(temp->word==word)
				{
					return 1;
				}
				if(word>temp->word)
				temp=temp->right;
				else
				if(word<temp->word)
				temp=temp->left;
			}
			return 0;
		}

};
void inorder(node*root)
{
	if(!root)
	return;
	inorder(root->left);
	cout<<root->word<<" ";
	inorder(root->right);
}
Avl input ;//tree object for checking duplicate in INPUT tree


int is_Safe(char *arr[],int i,int j,string word,int k,int arr_len)
{
    if(i>=0&&i<arr_len&&j>=0&&j<arr_len&&arr[i][j]==word[k])
    {
    	return true;	
	}
    return false;
}



bool solveMazeUtil(char *maze[], int x, int y, string word,int k,int wrd_indx,int arr_len) 
	{ 
		if(wrd_indx>=word.length())
			return true;	
				if ( is_Safe(maze,x,y,word,wrd_indx,arr_len)== true)
			{ 
					if(k==1&&solveMazeUtil(maze,x,y+1,word,k,++wrd_indx,arr_len)==true)	// Right
						return true;

			 	 	else if(k==2&&solveMazeUtil(maze,x+1,y,word,k,++wrd_indx,arr_len)==true) // Down 
						return true; 
  
				else if (k==3&&solveMazeUtil(maze, x , y-1, word,k,++wrd_indx,arr_len) == true) // Left
            		return true;
            		
          		else if (k==4&&solveMazeUtil(maze, x-1 , y, word,k,++wrd_indx,arr_len) == true) // Up
            		return true;
            		
            	else if (k==5&&solveMazeUtil(maze, x-1 , y-1, word,k,++wrd_indx,arr_len) == true) //Upper-left Diagonal
            		return true;
            	
            	else if (k==6&&solveMazeUtil(maze, x+1 , y+1, word,k,++wrd_indx,arr_len) == true) // Lower-right Diagonal
            		return true;
            		
            	else if (k==7&&solveMazeUtil(maze, x-1 , y+1, word,k,++wrd_indx,arr_len) == true) // Upper-right Diagonal
            		return true;
 				
				 else if (k==8&&solveMazeUtil(maze, x+1 , y-1, word,k,++wrd_indx,arr_len) == true) // Lower-left Diagonal
            		return true;
            		
				return false;
			}
		return false;
		
	}
	
	
 
bool solveMaze(char *maze[],string word,int i,int j,int arr_len) 
	{ 
		for(int k=1;k<=8;k++)
		{
				if (solveMazeUtil(maze, i, j, word,k,0,arr_len) == true)
	 			{ 
	 				if(input.repeat(input.root,word))
					{
						cout<<"Already Entered "<<endl;
						return true;
					}
				else if(	SearchWord(word))
        			{
					ScoreUpdate();
					input.root=input.insert(input.root,word);
					}
					return true;
     			
		} 	
		}
     		return false;//not in puzzle
	}

void findword(int len,char *arr[]){
	string word;
	
		int c=0;
		cout<<"\t\tPRESS 0 FOR TERMINATION:\n";
		pthread_t mytime;
		beg=time(NULL);
		pthread_create(&mytime,NULL,timethread,&len);
	
		loop:
		
		while(true)//untill time
		{
			
			cout<< endl << "Enter word : ";
			cin>>word;
				
			if(word[0]=='0')
				break;
			if(timeup)
			goto over;
			
		for(int i=0;i<len;i++)
		{
			for(int j=0;j<len;j++)
				{
					if(arr[i][j]==word[0])
					{
						if(solveMaze(arr,word,i,j,len))
						{
						goto loop;	
						}
					}
				}

			}
			
		cout<<"WORD doesn't exist\n";
		
		}
		over:
		if(word[0]!='0')
		{
			cout<<"\n====Time's' up====";
		}
}



void disp_puzz(string puzz,int choice){
	system("cls");
	int len;
	
	if(choice == 1){

		cout << "Level : EASY \t\t\t====Time ";
		cout<<"Left : 120  seconds====" << endl << endl;
		len = 4;
	}
	
	else if(choice == 2){
		cout << "Level : MEDIUM \t\t\t====Time Left : 240  seconds====" << endl << endl;
		len = 6;
	}
		
	else if(choice == 3){
		cout << "Level : HARD \t\t\t====Time Left : 360  seconds====" << endl << endl;
		len = 8;
	}
		
	 char** show_puzz= new char*[len];
	 
	 for (int i = 0; i < len; i++)        
	 	 show_puzz[i]= new char[len];
		   
	int k = 0;
	for(int i=0;i<len;i++)
		for(int j=0;j<len;j++)
			show_puzz[i][j] = puzz[k++];
			
	for(int i=0;i<len;i++){
		cout << "\t\t";
		for(int j=0;j<len;j++){
			cout << show_puzz[i][j] << "   ";
		}
		cout << endl << endl;
	}
	ScoreUpdate();
	findword(len,show_puzz);
	
	for (int i = 0; i < len; i++)
	     delete[] show_puzz[i]; 
 
    delete[] show_puzz;
	
}



void get_puzz(int choice){
	ifstream file;
	
	switch(choice){
		case 1:
			file.open("levelEasy.txt");
			break;
		
		case 2:
			file.open("levelMedium.txt");
			break;
			
		case 3:
			file.open("levelHard.txt");
	}
	
	string puzz_depo[100];
	int puzz_count = 0;
	while(!file.eof()){
		getline(file,puzz_depo[puzz_count++]);
	}
	
	srand(time(NULL));
	int get_rand_puzz = (rand()%puzz_count);
	
	file.close();	
	cout<<endl;
	disp_puzz(puzz_depo[get_rand_puzz],choice);
}



int main(){
	gotoxy(25,11);
	cout << "EXTENDED CROSSWORD PUZZLE GAME";
	sleep(5);
	system("cls");
	
	load();
	cout << "Choose Level of Difficulty : " << endl << endl;
	cout << "1- EASY" << endl << "2- MEDIUM" << endl << "3- HARD" << endl << endl << " : " ;
	int opt;
	cin >> opt;
	get_puzz(opt);
	cout<<"\n====FINAL SCORE = "<<score<<"====";
	
	return 0;
}

//tree.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "search.h"
#include "limits.h"
#include "hash.h"

extern depth,maxdepth,tries,num,size,tr,l,in;

int search(treenode* node,char *word,unsigned char *bf, list **extra){
	//----------------------------------------------
	char **tempwords,**words;
	int i,len,k=0,r,c;
	c_list *temp;
	list **extra_;
	//extra_=malloc(sizeof(list));
	//temp=malloc(sizeof(treenode));
	//----------------------------------------------	
	tempwords=(char**)oracle(word);//call oracle
	tries++;
	
	//------------------------------------------
	if(tempwords==NULL){//success
		len=strlen(word);//add the word in the tree
		node->word = malloc((len+1)*sizeof(char));
		strcpy(node->word,word);
		printf("\n\n----------------------------------\n");
		printf("SECRET WORD:    %s\n",word);
		printf("TRIES: %d \n",tries);
		printf("DEPTH: %d\n",depth+1);
		printf("LIST: %d\n",l);
		printf("----------------------------------\n\n\n");
		
		printf("WAIT FOR IT!\n\n\n");
		sleep(5);
		return 0;
	}
	//------------------------------------------
	if(depth<maxdepth){
		
		depth++;//add one in the current depth 
		//------------------------------------------
		len=strlen(word);//add the word in the tree
		node->word = malloc((len+1)*sizeof(char));
		strcpy(node->word,word);
		//------------------------------------------	
		while(tempwords[k]!=NULL){k++;}//#words returned by oracle
		node->ch=0;
		//--------------------------------------------------------------
		words=malloc(k*sizeof(char*));
		for(i=0;i<k;i++){//change the matrix to have them in memory
			len=strlen(tempwords[i]);
			words[i]=malloc((len+1)*sizeof(char));
			strcpy(words[i],tempwords[i]);
		}
		//--------------------------------------------------------------
		printf("--	%s -- has %d children\n",word,k);
		node->kids=malloc(sizeof(c_list));//---------------saving some space;
		if(k==0){
			node->kids=NULL;
		}
		temp=node->kids;
		//------------------------------------------
		for(i=0;i<k;i++){ 
			printf("CHEKING %s 	---%d CHILD: %s 	--\n",word,i+1,words[i]);
			c=check(words[i],bf);//-------------------------------------bloom filter
			//-------int search_again_idiot(list**);--------------------------------------------------
			if ( c==0){
				in++;
				node->ch++;
				temp->next_level=malloc(sizeof(treenode));	
				//------------------------------------------------------recurse here
				r=search( temp->next_level, words[i],bf,extra);
				//-----------------------------------------------------
				if ( r == 0 )  {return 0;}//---------------------------end of tree
				//-----------------------------------------------------
				(temp)->next_inline=malloc(sizeof(c_list));
				temp=(temp)->next_inline;
			}
			//---------------------------------------------------------
			else{//--------------------------------------------extra list of words
			//---------------------------------------------------------
				l++;
				//printf("\n\nan extra word for the list %s\n\n",words[i]);
				if(*extra==NULL){//------------------------------------first time
					(*extra)=malloc(sizeof(list));
					len=strlen(words[i]);
					(*extra)->word=malloc((len+1)*sizeof(char));
					strcpy((*extra)->word,words[i]);
				}
				else{//-------------------------------------------------all others
					extra_=extra;
					while(*extra_!=NULL){//to infinity and beyond
						//printf("\n\nextra in search: %s\n",extra_->word);
						extra_=&((*extra_)->next);
					}
					(*extra_)=malloc(sizeof(list));
					len=strlen(words[i]);
					(*extra_)->word=malloc((len+1)*sizeof(char));
					strcpy((*extra_)->word,words[i]);
					//printf("\n\n-------%s\n\n",(*extra_)->word);
				}
			}
			//---------------------------------------------------------
		}	
		depth--;//after i check all words the recursion returns one step back in the tree
		printf("-----------DEPTH is: %d-----------\n",depth);
		
	}
	else{
		//here add the leafs of the tree
		len=strlen(word);//add the word in the tree
		node->word = malloc((len+1)*sizeof(char));
		strcpy(node->word,word);
		node->kids=NULL;
		printf("-----------DEPTH is: %d-----------\n",depth);
		printf("\nword:	%s    -- is a leaf has no children!\n\n",word);
	}
}


int check(char *word,unsigned char *bf){
	int i,x,posx,flag=0;
	//posx is the position i in the bf matrix and x is the position in bf[i]
	uint64_t result;
	for(i=0;i<num;i++){
		//--------------------------------------------------------------
		result=hash_by(i,word);
		result=result%size;
		//--------------------------------------------------------------
		posx=result/CHAR_BIT;
		x=result%CHAR_BIT;
		//--------------------------------------------------------------
		if ( ( (bf[posx]>>x) & 1 )== 0){//------------------------------make 0 to 1
			flag=1;
			bf[posx]=bf[posx] | (1<<x);
		}
		//--------------------------------------------------------------
	}
	if (flag==1) return 0;//prepei na to prosthesei sto tree
	else return 1;//alliws tha to valei sti lista
}

int search_again_idiot(list **again){
	list *head,**tail;
	int i,result,k=0,len;
	char **words;
	head=*again;
	tail=again;
	while(*tail!=NULL){//to infinity and beyond
		tail=&((*tail)->next);
	}
	head=*again;
	while(head!=NULL){
		words=(char**)oracle(head->word);//call oracle
		tries++;
		if(words==NULL){//success
			printf("\n\n----------------------------------\n");
			printf("After Searching extra list\n");
			printf("SECRET WORD:    %s\n",head->word);
			printf("Total words searched: %d \n",tries);
			printf("----------------------------------\n\n");
			return 0;
		}
		else{
			while(words[k]!=NULL){k++;}//#words returned by oracle
			for(i=0;i<k;i++){
				(*tail)=malloc(sizeof(list));
				len=strlen(words[i]);
				(*tail)->word=malloc((len+1)*sizeof(char));
				strcpy((*tail)->word,words[i]);
				tail=&((*tail)->next);
			}
			k=0;
		}
		head=head->next;
	}
	return 0;
}

int print_tree(treenode* node){
	c_list *kid;
	
	//printf("printing node in depth %d\n",depth);
	if(node!=NULL){
		depth++;
		printf("---Depth:	 %d---",depth);
		printf("---word:--%s-- has",node->word);
		printf("	%d children\n",node->ch);
		tr++;
		//printf("%d\n",tr);
		kid=node->kids;
		while(kid!=NULL){
			print_tree(kid->next_level);
			kid=kid->next_inline;
		}
		depth--;
	}
}


int free_tree(treenode* node){
	c_list *kid,*temp;
	if(node!=NULL){
		//kid=node->kids;
		while(node->kids!=NULL){
			free_tree(node->kids->next_level);
			kid=node->kids->next_inline;
			free(node->kids);
			node->kids=kid;
		}
		free(node->word);
		free(node);
	}
}

//main.c
#include <stdio.h>
#include <stdlib.h>
#include "search.h"
#include "hash.h"
#include "oracle.h"

int depth=0,maxdepth,tries=0,num=3,size,tr=0,l=0,in=1;

int main(int argc,char* argv[]){
//----------------------------------------------------------------------
	int i=1,seed=10,oh_god_why;
	char **words,* input;
	unsigned char *bf;
//----------------------------------------------------------------------
	treenode *root;
	root=malloc(sizeof(treenode));
	list **extra;
	extra=malloc(sizeof(list*));
//----------------------------------------------------------------------
	printf("Give me a seed!\n");
	scanf("%d",&seed);
	initSeed(seed);
	if(argc<3 || argc>5) { 
		printf("Correct syntax is: ./invoke-oracle [-k NUM] SIZE DEPTH\n"); 
		return -1;
	}
	if(!strcmp(argv[i],"-k")){
		num=atoi(argv[i+1]);
		i++;
	}
	
	size=atoi(argv[i++]);
	maxdepth=atoi(argv[i]);
	
	bf=malloc(size*sizeof(unsigned char));
	for(i=0;i<size;i++){
		bf[i]=0;
	}
//----------------------------------------------------------------------
	oh_god_why=search(root,"",bf, extra);
	depth=0;
	print_tree(root);
	
	printf("\n--Nodes created:	%d\n",in);
	printf("--Nodes printed:	%d\n",tr);
	printf("--Words in extra list:	%d\n",l);
	
	if(oh_god_why != 0 ){
		printf("--Depth was not enough!\n");
		printf("--Words checked in tree: %d\n",tries);
		search_again_idiot(extra);
	}
	printf("\nI don't like this game.\n\n");
//----------------------------------------------------------------------
	free_tree(root);
	return 0;
}

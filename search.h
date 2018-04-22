//def.h
typedef struct clist c_list; 

typedef struct treenode_ treenode;

typedef struct list_ list;

struct clist{
	treenode *next_level;
	c_list *next_inline;
};

struct treenode_ {
	char* word;
	int ch;
	c_list *kids;
};

struct list_{
	char *word;
	list *next;
};

int search(treenode*,char*,unsigned char*,list**);
int search_again_idiot(list**);
int freetree(treenode*);
int check(char*,unsigned char*);
int print_tree(treenode*);

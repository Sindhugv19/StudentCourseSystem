#include<stdio.h>
#include<stdlib.h>
struct tnode{
	int data;
	struct tnode *llink;
	struct tnode *rlink;
};

struct tnode* value(struct tnode* root){
	while(root!=NULL){
		root=root->llink;
	}
	return root;
}

struct tnode* delete(struct tnode* root,int key){
	if(root==NULL) return NULL;
	if(key>root->data)
	root->rlink=delete(root->rlink,key);
	else if(key<root->data)
	root->llink=delete(root->llink,key);
	else{
		if(root->rlink==NULL){
		
		struct tnode* temp=root->llink;
		free(root);
		return temp;}
		else if(root->llink==NULL){
			struct tnode* temp=root->rlink;
			free(root);
			return temp;
		}
		struct tnode* temp=value(root->rlink);
		root->val=temp->val;
		root->rlink=delete(root->right,temp->val);
		return root;
	}
	
}



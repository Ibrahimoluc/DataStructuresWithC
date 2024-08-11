#include <stdlib.h>
#include <stdio.h> 

struct node{
	int data;
	struct node *left;
	struct node *right;
};

struct node* createNode(int data){
	struct node *newNode = (struct node*)malloc(sizeof(struct node));
	newNode->data = data;
	newNode->left = NULL;
	newNode->right= NULL;
	return newNode; 	
}

struct node* createTree(int data){
	struct node *root = createNode(data);
	return root;
}

void insert(int data, struct node *root){
	struct node *parent;
	while(root!=NULL){
		parent = root;
		root = (data > root->data) ? root->right : root->left;
	}		
	
	if(data > parent->data) parent->right = createNode(data);
	else parent->left = createNode(data);
} 


//recursive traverse all nodes and print out. 
void traverse(struct node *root){
	if(root!=NULL){
		printf("data:%d, address of node:%p\n", root->data, root);
		traverse(root->left);
		traverse(root->right);
	}
}

//return adress of first node with given data
struct node* lookup(int data, struct node *root){
	while(root!=NULL){
		if(root->data==data) return root;
		root = (data > root->data) ? root->right : root->left;
	}
	return NULL;
}

int delete(int data, struct node **root){
	//burdan devam et, notlarrina bak, sadece datayi degistirmek, sag subtree nin en solunu almak.
	//firs step: find the node and his parent from data
	struct node *parent=*root;
	struct node *delNode=*root;
	while(delNode!=NULL){
		if(delNode->data==data) break;
		parent = delNode;
		delNode = (data > delNode->data) ? delNode->right : delNode->left;
	}
	
	if(delNode==NULL) return -1;

	//if delNode is leaf
	if(delNode->right==NULL && delNode->left==NULL){
		if(delNode==parent->left) parent->left = NULL;
		else parent->right = NULL;
		free(delNode);
		return 0;
	}

	//if it is not leaf, it can have two children or 1.  

	//if it has two children
	struct node *left=delNode->left; //represents only a node or subtree
	struct node *right=delNode->right; //represents only a node or subtree  
	if(left!=NULL && right!=NULL){
		//delNode=20, parent=10, right=25
		//sol subtreenin en sagini bul, oraya sag nodenin sol subtreesi konulacak
		//struct node *temp = left;
		while(left->right!=NULL) left = left->right; //burada left=16 olacak bizim ornege gore
		left->right = right->left;

		//now we have to bind delNode's parent to new Node
		//bizim ornekte delNode parentin saginda
		//eger delNode root ise yani parent = delNode
		if(parent==delNode){
			right->left = (*root)->left;
			*root = right;
		}

		//if it is right node
		if(parent->right==delNode){
			parent->right = right;
			right->left = delNode->left;	 	
		}
		else{ //if it is left node
			parent->left = right;
			right->left = delNode->left;
		}
	
		//lastly free delNode
		free(delNode);
		return 0;
	}
	
}


int main(){
	printf("%s", "Hello World, Let's have a Tree!!!\n");
	//struct node *root = createTree(5);
	//insert(3, root); insert(7, root); insert(2, root); insert(4, root); insert(6, root); insert(10, root);
	struct node *root = createTree(10);
	insert(4, root); insert(2, root); insert(8, root); insert(20, root); insert(15, root); insert(12, root); insert(16, root); insert(14, root); insert(25, root); insert(22, root); insert(21, root);
	insert(30, root); insert(36, root); insert(32, root);
	traverse(root);
	delete(3, &root);
	traverse(root);

	/*
	printf("Adress of node with data 2:%p\n", lookup(2, root));
	printf("Adress of node with data 3:%p\n", lookup(3, root));
	printf("Adress of node with data 10:%p\n", lookup(10, root));
	printf("Adress of node with data 6:%p\n", lookup(6, root));
	printf("Adress of node with data 5:%p\n", lookup(5, root));
	
	insert(20, root);
	printf("After insertion\n");
	printf("root-left-data:%d\n", root->left->data);
	printf("root-left:%p\n", root->left);
	printf("root-right:%p\n", root->right);
	*/
	return 0;
}

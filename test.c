#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node *left;
	struct node *right;
} t_node;

t_node *newNode(int data) {
	t_node *node = (t_node*)malloc(sizeof(t_node));
	node->data = data;

	node->left = NULL;
	node->right = NULL;
	return node;
}

int main() {
	t_node *root = newNode(1);
	root->left = newNode(2);
	root->right = newNode(3);
	
	root->left->left = newNode(10);	
	root->left->left->left = newNode(20);
	return 0;
	/*
	So newline stuff finally seems to work, this is editor is actually very nice
	not gonna lie 
	*/
}

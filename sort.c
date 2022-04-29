#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 1024

typedef struct node {
	char* text;
	struct node* left;
	struct node* right;
} Node;

Node* new_node(char* text) {
	Node* node = (Node*)malloc(sizeof(Node));
   	if (node == NULL)
		return NULL;
	if ((node->text = strdup(text)) == NULL) {
		free(node);
		return NULL;
	}
	node->left = node->right = NULL;
	return node;
}

Node* insert(Node* tree, char* text) {
	if (tree == NULL)
		return new_node(text);

	int cmp = strcmp(tree->text, text);

	if (cmp < 0)
		tree->left = insert(tree->left, text);
	if (cmp > 0)
		tree->right = insert(tree->right, text);

	return tree;
}

void print_tree(Node* node) {
	if (node == NULL)
		return;
	print_tree(node->right);
	printf("%s", node->text);
	print_tree(node->left);
}

int main() {
	char line[MAX_LINE];
	Node* tree = NULL;
	while (fgets(line, MAX_LINE, stdin))
		tree = insert(tree, line);

	print_tree(tree);
}

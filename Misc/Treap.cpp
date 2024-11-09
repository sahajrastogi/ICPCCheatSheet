#include <stdlib.h>

struct Node {
	// the value and priority of the node respectively
	int val, pri;
	// pointer to left and right child (NULL means no child)
	Node *left, *right;
	Node(int val) : val(val), pri(rand()), left(NULL), right(NULL){};
} *root;

/**
 * pass in root as pointer, left and right as references
 * to a node pointer so we can modify them
 * (alternatively, we can return left and right pointers
 * as an std::pair)
 */
void split(Node *root, int x, Node *&left, Node *&right) {
	if (!root) {
		left = right = NULL;
		return;
	}
	if (root->val <= x) {
		split(root->right, x, root->right, right);
		left = root;
	} else {
		split(root->left, x, left, root->left);
		right = root;
	}
}

/**
 * merge left and right pointers into root which
 * is a reference to a pointer to enable
 * modification within the function
 */
void merge(Node *&root, Node *left, Node *right) {
	if (!left || !right) {
		root = left ? left : right;
		return;
	}
	if (left->pri > right->pri) {
		merge(left->right, left->right, right);
		root = left;
	} else {
		merge(right->left, left, right->left);
		root = right;
	}
}
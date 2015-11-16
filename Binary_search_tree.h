// file name: binary_search_tree.h

// Author: Mahesh Yadav


#include <iostream>
#include <malloc.h>
#define null 0

using namespace std;


struct node{

	int data;
	struct node *left_child, *right_child;
};



// Function to initiallize a leaf node
// Argument is the data element of the node
// Returns a leaf node

struct node* initiallize_new_node(int data){

	struct node *new_node = (struct node*)malloc(sizeof(node));

	new_node->data = data;

	new_node->left_child = null;
	new_node->right_child = null;
}


// Function to insert a node in binary_search_tree
// Fuction returns the pointer to the root node

struct node* insert(struct node *root, int key){

	// base case

	if(root == null){
		root = initiallize_new_node(key);
		return root;
	}

	if(key < root->data){
		root->left_child = insert(root->left_child, key);
	}

	else{
		root->right_child = insert(root->right_child, key);
	}

	return root;

}

// Function for inorder traversal of BST

void inorder(struct node *root){

	if(root == null){
		return;
	}

	inorder(root->left_child);
	cout << root->data << endl;
	inorder(root->right_child);
}


// Function for post order traversal

void post_order(struct node *root){

	if(root == null){
		return;
	}

	post_order(root->left_child);
	post_order(root->right_child);
	cout << root->data << endl;
}

// Function for pre order traversal

void pre_order(struct node *root){

	if(root == null){
		return;
	}

	cout << root->data << endl;
	pre_order(root->left_child);
	pre_order(root->right_child);
}


// Function to find minimum value in BST

struct node* get_min_value(struct node *root){

	if(root->left_child == null || root == null){
		return root;
	}

	return get_min_value(root->left_child);
}

//Function to find maximal element in a BST

struct node* get_max_value(struct node* root){

	if(root->right_child == null || root == null){
		return root;
	}

	return get_max_value(root->right_child);
}

// Function to get pointer to a given key value

struct node* get_pointer_to(struct node* root, int key){

	if(root == null){
		return root;
	}

	if(root->data == key){
		return root;
	}

	if(key < root->data){
		return get_pointer_to(root->left_child, key);
	}

	else{
		return get_pointer_to(root->right_child, key);
	}

}
// Function for finding inorder Sucessor of a given node

struct node* inorder_successor(struct node *root, int key){

	struct node* node_key = get_pointer_to(root,key);
	cout << node_key->data;

	// if right subtree is not null, then smallest element in right subtree is the sucessor
	if(node_key->right_child != null){
		return get_min_value(node_key->right_child);
	}

	//otherwise search from the root
	struct node* successor;

	while(root != null){

		if(key < root->data){
			successor = root;
			root = root->left_child;
		}

		else if(key > root->data){
			root = root->right_child;
		}
		else{
			break;
		}
	}

	return successor;
}

// Function to find inorder_predecessor

struct node* inorder_predecessor(struct node* root, int key){
	struct node* node_key = get_pointer_to(root, key);

	// if there is left subtree, find maximum in left subtree

	if(node_key->left_child != null){
		return get_max_value(node_key->left_child);
	}

	// otherwise search through root down the tree

	struct node* predecessor = null;

	while(root != null){
		if(key > root->data){
			predecessor = root;
			root = root->right_child;
		}

		else if(key < root->data){
			root = root->left_child;
		}

		else{
			break;
		}
	}

	return predecessor;
}

// Function to check if a given node is leaf node

bool is_leaf_node(struct node *node){
	return (node->left_child == null && node->right_child == null);
}


struct node *delete_node(struct node *root, int key){

	if(root ==  null){
		return root;
	}

	if(key < root->data){
		root->left_child = delete_node(root->left_child,key);
	}

	else if(key > root->data){
		root->right_child = delete_node(root->right_child, key);
	}

	// if we find the root
	else{

		struct node *deleted_node = root;

		if(root->left_child == null){
			root = root->right_child;
			free(deleted_node);

			return root;
		}

		else if(root->right_child == null){
			root = root->left_child;
			free(deleted_node);

			return root;
		}

		// if there are two children, then find the sucessor

		struct node *temp = get_min_value(root->right_child);

		root->data = temp->data;

		root->right_child = delete_node(root->right_child, temp->data);

	}

	return root;
}


// Function to finde number of nodes in a binary search tree

int get_no_of_nodes(struct node *root){

	if(root == null){
		return 0;
	}

	return 1 + get_no_of_nodes(root->left_child) + get_no_of_nodes(root->right_child);
}


// Function to count no of leaf nodes

int get_no_of_leaf_nodes(struct node *root){

	if(root == null){
		return 0;
	}

	if(root->left_child == null && root->right_child == null){
		return 1;
	}


	return get_no_of_leaf_nodes(root->left_child) + get_no_of_leaf_nodes(root->right_child);

}


// Function to find height of binary tree

int get_height(struct node *root){

	if(root == null){
		return 0;
	}

	int left_subtree_height = get_height(root->left_child);
	int right_subtree_height = get_height(root->right_child);

	if(left_subtree_height > right_subtree_height){
		return 1 + left_subtree_height;
	}

	else{
		return 1 + right_subtree_height;
	}

}
// Function to find kth smallest element
// Assuming there are more than k nodes



// Function to find Kth smallest node
struct node* Kth_smallest_node(struct node *root, int k){

	// corner case - if no. of nodes in the tree are smaller than k

	if(get_no_of_nodes(root) < k){
		return null;
	}

	/* Base case - as all the nodes in the left subtree are smaller than the root, so if there are k-1 nodes
	   in left subtree, then the root will be the kth smallest node
	*/

	int n = get_no_of_nodes(root->left_child);

	if(n == k-1){
		return root;
	}

	/* otherwise if there are n < k nodes in the left subtree, then the root node is the (n+1)th smallest node.
 	   then find the k-(n+1)th smallest node in the right subtree
 	*/

 	else if(n < k-1){
 		return Kth_smallest_node(root->right_child, k-n-1);
 	}

 	/* if n > k, then search for the Kth smallest node in the left subtree
 	*/

 	else{
 		return Kth_smallest_node(root->left_child, k);
 	}

}




bool search_node(struct node *root, int key){

	if(root == null){
		return false;
	}

	else{

		if(key < root->data){

		return search_node(root->left_child, key);
		}

		else if(key > root->data) {
		return search_node(root->right_child, key);
		}

		else{
		return true;
		}
	}

}


// traverse the tree in postorder and delete every node/*struct node* delete_tree(struct node **root){

void delete_tree(struct node **root){

	if(*root == null){
		return;
	}


	delete_tree(&((*root)->left_child));
	delete_tree(&((*root)->right_child));
	delete(*root);
	root = null;
}

















































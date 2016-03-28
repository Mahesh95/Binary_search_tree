// file name: BST.h

// Author: Mahesh Yadav

struct node{
	int data;
	struct node *leftChild, *rightChild;
};

struct node * newNode(int data){
	struct node* newNodePtr = new node;
	
	newNodePtr->leftChild = NULL;
	newNodePtr->rightChild = NULL;
	newNodePtr->data = data;

	return newNodePtr;
}

struct node* insert(struct node *root, int data){
	if(root == NULL){
		return newNode(data);
	}

	if(data > root->data){
		root->rightChild = insert(root->rightChild, data);
	}else{
		root->leftChild = insert(root->leftChild,  data);
	}

	return root;
}


void inorder(struct node *root){
	if(root == NULL){
		return;
	}

	inorder(root->leftChild);
	std::cout << root->data << "\n";
	inorder(root->rightChild);
}

int findMaxElementBinaryTree(struct node* root){
	int max = -32768;
	int maxLeft, maxRight,rootVal;

	if(root != NULL){

		rootVal = root->data;
		maxRight = findMaxElementBinaryTree(root->leftChild);
		maxLeft = findMaxElementBinaryTree(root->rightChild);

		if(maxLeft > maxRight)
			max = maxLeft;
		else
			max = maxRight;

		if(rootVal > max)
			max = rootVal;

	}

	return max;
}


bool search(struct node* root, int data){

	if(root == NULL){
		return false;
	}

	if(root->data == data){
		return true;
	}else{
		if(data > root->data){
			return search(root->rightChild, data);
		}else{
			return search(root->leftChild, data);
		}
	}
}


int getSize(struct node* root){
	
	if(root == NULL){
		return 0;
	}

	return 1 + getSize(root->leftChild) + getSize(root->rightChild);
}

int getHeight(struct node* root){
	
	if(root == NULL){
		return 0;
	}

	return 1 + std::max(getHeight(root->leftChild), getHeight(root->rightChild));
}

/*Given two nodes a and b, assuming that they already exist in the tree, the idea is to find the first node while traveling from 
  root to bottom of the tree such that a < p < b. Then p will be inorder predecessor of a and b 
*/

struct node* lowestCommonAncestor(struct node* root, int a, int b){

	if(a > root->data && b > root->data){
		return lowestCommonAncestor(root->rightChild, a, b);
	}

	else if(a < root->data && b < root->data){
		return lowestCommonAncestor(root->leftChild, a, b);
	}

	else{
		return root;
	}
}

//inorder predecessor is the the largest node in the left subtree

struct node* inorderPredecessor(struct node* root){
	struct node* leftSubtree = root->leftChild;
	struct node* predecessor;
	// now find largest element in the left subtree
	while(leftSubtree){
		predecessor = leftSubtree;
		leftSubtree = leftSubtree->rightChild;
	}

	return predecessor;
}

struct node* deleteNode(struct node* root, int data){

	if(data > root->data){
		root->rightChild =  deleteNode(root->rightChild, data);
	}
	else if(data < root->data){
		root->leftChild = deleteNode(root->leftChild, data);
	}
	else{
			struct node* returnPtr;
		//if leaf node, return NULL to the parent
		if(!root->leftChild && !root->rightChild){
			delete(root);
			return NULL;
		}	
		//if two children, replace the node by inorder predecessor and delete the predecessor recursively
		else if(root->leftChild && root->rightChild){
			root->data = inorderPredecessor(root)->data;
			deleteNode(root->leftChild, root->data);
		} 	

		//if only one child, then return the child to the parent of the node to be deleted
		else{
			if(root->leftChild){
				returnPtr = root->leftChild;
			}else{
				returnPtr = root->rightChild;
			}

			delete(root);
			return returnPtr;
		}
	}
	return root;	
}

int noOfNodes(struct node* root){
	
	if(root == NULL){
		return 0;
	}else{
		return 1 + noOfNodes(root->leftChild) + noOfNodes(root->rightChild);
	}
}


// returns Kth smallest node assuming tree contains atleast k nodes, and k > 1

struct node* kthSmallestNode(struct node* root, int k){

	if(noOfNodes(root->leftChild) == k-1){
		return root;
	}


	if(noOfNodes(root->leftChild) < k-1){
		return kthSmallestNode(root->rightChild, k-noOfNodes(root->leftChild)-1);
	}else{
		return kthSmallestNode(root->leftChild, k);
	}
}

struct node* sortedArrayToBST(int *array, int left, int right){
	
}
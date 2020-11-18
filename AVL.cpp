// AVL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

struct node
{
	int val;
	node* left;
	node* right;
	int height;
};


class avl
{
public:
	int number;
	node* root;
	avl();
	int max(int,int);
	int height(node* );
	node* min(node* node);
	node* newnode(int vall);
	node* rotatel(node* x);
	node* rotater(node* y);
	int getbalance(node* );
	node* insert(node* r, int k);
	node* delet(node* root, int key); 
	void preorder(node* i);



};



avl::avl()
{
	root = NULL;
}


int avl::max(int a,int b)
{
	if (a > b)
	{
		return a;
	}
	else
	{
		return b;
	}
}


int avl::height(node* h)
{
	if (h == NULL)
	{
		return 0;
	}
	return h->height;
}


node* avl::newnode(int vall)
{
	node* temp = new node;
	temp->val = vall;
	temp->left = NULL;
	temp->right = NULL;
	temp->height = 1;

	return temp;
}


node* avl::rotater(node* y)
{
	node* x = y->left;
	node* T2 = x->right;

	x->right = y;
	y->left = T2;

	y->height = max(height(y->left), height(y->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;

	return x;
}

node* avl::rotatel(node* x)
{

	node* y = x->right;
	node* T2 = y->left;

	y->left = x;
	x->right = T2;

	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;

	return y;
}


node* avl::insert(node* root, int key)
{
	if (root == NULL)
	{
		root= newnode(key);
		return root;
	}
	else if (key < root->val)
	{
		root->left = insert(root->left,key);
	}
	else if (key > root->val)
	{
		root->right = insert(root -> right, key);
	}
	else
	{
		cout << "Number already present." << endl;
		return root;
	}

	root->height = 1 + max(height(root->left), height(root->right));

	int balance = getbalance(root);

	if (balance > 1 && key < root->left->val)
	{
		return rotater(root);
	}
	if (balance < -1 && key>root->right->val)
	{
		return rotatel(root);
	}
	if (balance > 1 && key > root->left->val)
	{
		root->left = rotatel(root->left);
		return rotater(root->right);
	}
	if (balance < -1 && key < root->right->val)
	{
		root->right = rotater(root->right);
		return rotatel(root);
	}

	return root;
}	


int avl::getbalance(node *t)
{
	if (t == NULL)
	{
		return 0;
	}
	return height(t->left) - height(t->right);
}

//////////////////MINIMUM VALUE//////////
 node* avl::min(node* start)
{
	 node* current = start;
	/* loop down to find the leftmost leaf */
	while (current->left != NULL)
		current = current->left;

	return current;
}

/////////////////DELETE FUNCTION////////////////
node* avl::delet(node* root, int key)
{

	// STEP 1: PERFORM STANDARD BST DELETE  
	if (root == NULL)
		return root;

	// If the key to be deleted is smaller  
	// than the root's key, then it lies 
	// in left subtree  
	if (key < root->val)
		root->left = delet(root->left, key);

	// If the key to be deleted is greater  
	// than the root's key, then it lies  
	// in right subtree  
	else if (key > root->val)
		root->right = delet(root->right, key);

	// if key is same as root's key, then  
	// This is the node to be deleted  
	else
	{
		// node with only one child or no child  
		if ((root->left == NULL) ||
			(root->right == NULL))
		{
			node* temp = root->left ?
				root->left :
				root->right;

			// No child case  
			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			else // One child case  
				*root = *temp; // Copy the contents of  
							   // the non-empty child  
			free(temp);
		}
		else
		{
			// node with two children: Get the inorder  
			// successor (smallest in the right subtree)  
			node* temp = min(root->right);

			// Copy the inorder successor's  
			// data to this node  
			root->val = temp->val;

			// Delete the inorder successor  
			root->right = delet(root->right,temp->val);
		}
	}

	// If the tree had only one node 
	// then return  
	if (root == NULL)
		return root;

	// STEP 2: UPDATE HEIGHT OF THE CURRENT NODE  
	root->height = 1 + max(height(root->left),
		height(root->right));

	// STEP 3: GET THE BALANCE FACTOR OF  
	// THIS NODE (to check whether this  
	// node became unbalanced)  
	int balance = getbalance(root);

	// If this node becomes unbalanced,  
	// then there are 4 cases  

	// Left Left Case  
	if (balance > 1 &&getbalance(root->left) >= 0)
		return rotater(root);

	// Left Right Case  
	if (balance > 1 &&
		getbalance(root->left) < 0)
	{
		root->left = rotatel(root->left);
		return rotater(root);
	}

	// Right Right Case  
	if (balance < -1 &&
		getbalance(root->right) <= 0)
		return rotatel(root);

	// Right Left Case  
	if (balance < -1 &&
		getbalance(root->right) > 0)
	{
		root->right = rotater(root->right);
		return rotatel(root);
	}

	return root;
}



void avl::preorder(node* root)
{
	if (root == NULL)
	{
		cout << "Empty Tree" << endl;
	}
	else if (root->left != NULL)
	{
		preorder(root->left);
	}
	cout << root->val << " ";
	if (root->right != NULL)
	{
		preorder(root->right);
	}

	return;
}

void options()
{
	cout << "Please Select an operation." << endl;
	cout << "Press 1 for Insertion" << endl;
	cout << "Press 2 for print" << endl;
	cout << "Press 3 for Delete" << endl;
}


int main()
{
	avl obj;

	char ans;
	while (4)
	{
		options();
		cout << "Enter option: ";
		cin >> ans;
		switch (ans)
		{
		case'1':
			cout << "Enter Value to insert: " ;
			cin >> obj.number;
			obj.root=obj.insert(obj.root, obj.number);
			break;
		case'2':
			obj.preorder(obj.root);
			cout << endl;
			break;
		case'3':
			cout << "Enter Value to delete: ";
			cin >> obj.number;
			obj.delet(obj.root,obj.number);
			break;
		case'4':
			exit(0);
		}

	}

}
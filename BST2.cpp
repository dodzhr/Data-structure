
#include <iostream>
using namespace std;

struct node
{
	int val;
	node* left;
	node* right;
};

class bst
{
public:
	node* root;
	int number;
	void insert(node* r);
	node* delet(node* p,int key);
	void options();
	void print(node *s);
	node* minimumkey(node* k);
	node* search(node* c, node* l, int va);
	bst();
};

////////////CONSTRUCTOR////////////////

bst::bst()
{

	root = NULL;
}

///////////OPTIONS///////////////

void bst::options()
{
	cout << "Enter 1 for insertion. "<<endl;
	cout << "Enter 2 for print. " << endl;
	cout << "Enter 3 for deletion. " << endl;
	cout << "Enter 4 for searching. " << endl;
	cout << "Enter 5 for Exiting. " << endl;
}




/////////////////////MINUMIUM KEY///////////////////
node* bst::minimumkey(node* k)
{
	if (k->left == NULL)
	{
		return k;
	}
	else
	{
		minimumkey(k->left);
		return k;
	}

}



///////////SEARCH NUMBER//////////////////////////

node* bst::search(node* current, node* extra, int vall)
{

	if (current->val == vall)
	{
		cout << current->val << " YES " << endl;
		extra = current;
		return extra;
	}
	if (current->val != vall && current != NULL)
	{

		if ( current->val>vall)
		{
			 search(current->left, current->left,vall);
		}
		else
		{
			search(current->right, current->right, vall);
		}
	}
	return extra;
}

/////////////INSERT//////////////

void bst::insert(node* pointer)
{


	if (root == NULL)
	{
		pointer = new node;
		pointer->left = NULL;
		pointer->right = NULL;
		pointer->val = number;
		root = pointer;
		return;
	}

	if (pointer->val == number)
	{
		cout << "Number is already present " << endl;
		return;
	}

	if (number < pointer->val)
	{
		if (pointer->left != NULL)
		{
			insert(pointer->left);
			return;
		}
		else
		{
			pointer->left = new node;
			pointer->left->left = NULL;
			pointer->left->right = NULL;
			pointer->left->val = number;
			return;
		}
	}
	else if (number > pointer->val)
	{
		if (pointer->right != NULL)
		{
			insert(pointer->right);
			return;
		}
		else
		{
			pointer->right = new node;
			pointer->right->val = number;
			pointer->right->left = NULL;
			pointer->right->right = NULL;
			return;
		}

	}
}


////////////////////PRINT////////////////////////

void bst::print(node* start)
{
	if (start == NULL)
	{
		cout << "Tree is empty" << endl;
		return;
	}
	else if (start->left != NULL)
	{
		print(start->left);
	}
	cout << start->val << " ";
	if (start->right != NULL)
	{
		print(start->right);
	}

	return;
}

////////////////////DELETE/////////////////////

node* bst::delet(node* root,int key)
{
		if (root == NULL) return root;
		else if (number < root->val) root->left = delet(root->left, key);
		else if (number > root->val) root->right = delet(root->right, key);
		// Wohoo... I found you, Get ready to be deleted	

		else {
			// Case 1:  No child
			if (root->left == NULL && root->right == NULL) {
				delete root;
				root = NULL;
				return root;
			}

			//Case 2: One child 
			else if (root->left == NULL) {
				 node* temp = root;
				root = root->right;
				delete temp;
			}
			else if (root->right == NULL) {
				node* temp = root;
				root = root->left;
				delete temp;
			}
			// case 3: 2 children
			else {
				node* temp = minimumkey(root->right);
				root->val = temp->val;
				root->right = delet(root->right, temp->val);
			}
		}
		return root;
}





int main()
{
	bst obj;


	while (5)
	{
		char a;
		obj.options();
		cin >> a;

		switch (a)
		{
		case'1':
			cout << "Enter number to insert: ";
			cin >> obj.number;
			obj.insert(obj.root);
			break;
		case'2':
			obj.print(obj.root);
			cout << endl;
			break;
		case'3':
			cout << "Enter number to delete: ";
			cin >> obj.number;
			obj.root=obj.delet(obj.root,obj.number);
			break;
		case'4':
			obj.search(obj.root, obj.root, 1);
			break;
		case'5':
			exit(0);
			break;
		}
	}
}
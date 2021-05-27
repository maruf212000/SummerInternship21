#include<iostream>
using namespace std;
#define COUNT 5

enum COLOR {RED,BLACK};

template <typename T>
class Node
{
public:
	T val;
	COLOR color;
	Node * left, * right, * parent;
	Node(T v) : val(v) {
		parent = left = right = NULL;
		color = RED;
	}
};

template <typename T>
class IRedBlackTree {
public:
	virtual void Insert(T val) = 0;
	virtual void Delete() = 0;
	virtual void Search() = 0;
};

template <typename T>
class RedBlackTree : public IRedBlackTree<T>
{
private:
	Node<T>* root;
	Node<T>* NULLNODE = new Node<T>(0);
public:
	RedBlackTree()
	{
		root = NULL;
	}

	Node<T>* find(T val)
	{
		Node<T>* shift = root;
		while (shift != NULL)
		{
			if (val > shift->val)
			{
				if (shift->right == NULL)
					break;
				else
					shift = shift->right;
			}
			else if (val < shift->val)
			{
				if (shift->left == NULL)
					break;
				else
					shift = shift->left;
			}
			else
				break;
		}
		return shift;
	}
	
	Node<T>* findSibling(Node<T>* shift)
	{
		if (shift->parent->val > shift->val)
			return shift->parent->right;
		else
			return shift->parent->left;
	}

	Node<T>* rightRotate(Node<T>* shift)
	{
		//cout << "Right Shift val: " << shift->val << endl;
		Node<T>* oldparent = shift->parent;
		Node<T>* temp = shift->right;
 		if (oldparent == root)
		{
			root = shift;
			shift->right = oldparent;
			oldparent->left = NULL;
			oldparent->parent = shift;
		}
		else
		{
			//oldparent->parent->right = shift;
			shift->parent = oldparent->parent;
			oldparent->parent = shift;
			shift->right = oldparent;
			oldparent->left = temp;
			if(temp!=NULL)
				temp->parent = oldparent;
		}
		//print2DUtil(root, 0);
		return shift;
		
	}

	Node<T>* leftRotate(Node<T>* shift)
	{
		//cout << "Left Shift val: " << shift->val << endl;
		Node<T>* oldparent = shift->parent;
		Node<T>* temp = shift->left;
		if (oldparent == root)
		{
			root = shift;
			shift->left = oldparent;
			oldparent->right = temp;
			oldparent->parent = shift;
			shift->parent = NULL;
		}
		else
		{
			//oldparent->parent->left = shift;
			shift->parent = oldparent->parent;
			oldparent->parent = shift;
			shift->left = oldparent;
			oldparent->right = temp;
			if (temp != NULL)
				temp->parent = oldparent;
		}
		//print2DUtil(root, 0);
		return shift;
	}

	void rotate(Node<T>* shift)
	{
		if (shift->val < shift->parent->val && shift->parent->val < shift->parent->parent->val)
		{
			shift = rightRotate(shift);
			if (shift != root)
				shift->parent->left = shift;
			COLOR temp = shift->color;
			shift->color = shift->right->color;
			shift->right->color = temp;
		}
		else if (shift->val > shift->parent->val && shift->parent->val < shift->parent->parent->val)
		{
			shift = leftRotate(shift);
			if (shift != root)
				shift->parent->left = shift;
			shift = rightRotate(shift);
			if (shift != root)
				shift->parent->right = shift;
			COLOR temp = shift->color;
			shift->color = shift->right->color;
			shift->right->color = temp;
		}
		else if (shift->val < shift->parent->val && shift->parent->val > shift->parent->parent->val)
		{
			//cout << "Lol\n";
			shift = rightRotate(shift);
			shift->parent->right = shift;
			shift = leftRotate(shift);
			shift->parent->left = shift;
			COLOR temp = shift->color;
			shift->color = shift->left->color;
			shift->left->color = temp;
		}
		else if (shift->val > shift->parent->val && shift->parent->val > shift->parent->parent->val)
		{
			shift = leftRotate(shift->parent);
			if(shift!=root)
				shift->parent->right = shift;
			COLOR temp = shift->color;
			shift->color = shift->left->color;
			shift->left->color = temp;
		}
	}

	void fixRedRed(Node<T>* shift)
	{
		if (shift->parent->color == RED)
		{
			Node<T>* parentSibling = findSibling(shift->parent);
			if (parentSibling != NULL)
			{
				if (parentSibling->color == RED)
				{
					shift->parent->color = BLACK;
					parentSibling->color = BLACK;
					if (shift->parent->parent != root)
					{
						shift->parent->parent->color = RED;
						fixRedRed(shift->parent->parent);
						//cout << shift->parent->parent->val <<"\n";
					}
				}
				else
				{
					rotate(shift);
				}
			}
			else
			{
				//rotate
				rotate(shift);
			}
		}
	}

	void Insert(T val)
	{
		Node<T>* newnode = new Node<T>(val);
		if (root == NULL)
		{
			root = newnode;
			root->color = BLACK;
		}
		else
		{
			Node<T>* temp = find(val);
			if (temp->val == val)
				return;
			newnode->parent = temp;
			if (val > temp->val)
				temp->right = newnode;
			else
				temp->left = newnode;
			fixRedRed(newnode);
			//root->left = newnode;
		}
		print2DUtil(root, 0);
	}

	void print2D()
	{
		print2DUtil(root, 0);
	}

	void print2DUtil(Node<T>* root,int space)
	{
		if (root == NULL)
			return;

		space += COUNT;

		print2DUtil(root->right, space);

		cout << endl;
		for (int i = COUNT; i < space; i++)
			cout << " ";
		char ch = root->color==0 ? 'R' : 'B';
		cout << root->val << ch << "\n";

		print2DUtil(root->left, space);
	}

	void Delete(){}

	void Search(){}
};

int main()
{
	RedBlackTree<int> RBTree;
	int val;
	while (1)
	{
		cout << "Insert Value\n";
			cin >> val;
		if (val == 0)
			break;
		RBTree.Insert(val);
		//RBTree.print2D();
	}
}

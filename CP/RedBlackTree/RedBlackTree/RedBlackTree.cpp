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
		Node<T>* x = shift->left;

		shift->left = x->right;
		if (x->right != NULL)
			x->right->parent = shift;
		if (shift->parent == NULL)
		{
			root = x;
			x->parent = NULL;
		}
		else if (shift->parent->left == shift)
		{
			shift->parent->left = x;
			x->parent = shift->parent;
		}
		else
		{
			shift->parent->right = x;
			x->parent = shift->parent;
		}
		x->right = shift;
		shift->parent = x;
		//print2DUtil(root, 0);
		return shift->parent;
		
	}

	Node<T>* leftRotate(Node<T>* shift)
	{
		//cout << "Left Shift val: " << shift->val << endl;
		Node<T>* y = shift->right;
		
		shift->right = y->left;
		if (y->left != NULL)
			y->left->parent = shift;
		if (shift->parent == NULL)
		{
			root = y;
			y->parent = NULL;
		}
		else if (shift == shift->parent->left)
		{
			shift->parent->left = y;
			y->parent = shift->parent;
		}
		else
		{
			shift->parent->right = y;
			y->parent = shift->parent;
		}
		shift->parent = y;
		y->left = shift;
		return shift->parent;
	}

	void rotate(Node<T>* shift)
	{
		if (shift->val < shift->parent->val && shift->parent->val < shift->parent->parent->val)
		{
			//cout << "1\n";
			shift = rightRotate(shift->parent->parent);
			COLOR temp = shift->color;
			shift->color = shift->right->color;
			shift->right->color = temp;
		}
		else if (shift->val > shift->parent->val && shift->parent->val < shift->parent->parent->val)
		{
			//cout << "2\n";
			shift = leftRotate(shift->parent);
			shift = rightRotate(shift->parent);
			COLOR temp = shift->color;
			shift->color = shift->right->color;
			shift->right->color = temp;
		}
		else if (shift->val < shift->parent->val && shift->parent->val > shift->parent->parent->val)
		{
			//cout << "3\n";
			shift = rightRotate(shift->parent);
			shift = leftRotate(shift->parent);
			COLOR temp = shift->color;
			shift->color = shift->left->color;
			shift->left->color = temp;
		}
		else if (shift->val > shift->parent->val && shift->parent->val > shift->parent->parent->val)
		{
			//cout << "4\n";
			shift = leftRotate(shift->parent->parent);
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
				//cout << "HUva\n";
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

#include<iostream>
#include<vector>
#include<map>
#include<queue>
#include<stack>
using namespace std;

template <typename T>
class Node {
public:
	T val;
	Node* next;
	Node(T v) : val(v) {
		next = nullptr;
	}
};

template <typename T>
class ILinkList {
public:
	virtual void Insert(T val) = 0;
	virtual void printList() = 0;
};

template <typename T>
class LinkList : public ILinkList<T> {	
public:
	Node<T>* head;
	LinkList()
	{
		head = nullptr;
	}
	void Insert(T val)
	{
		Node<T>* newnode = new Node<T>(val);
		if (head == nullptr)
		{
			head = newnode;
		}
		else
		{
			newnode->next = head;
			head = newnode;
		}
	}
	void printList() {
		Node<T>* shift = head;
		while (shift->next != nullptr)
		{
			cout << shift->val << "-> ";
			shift = shift->next;
		}
		cout << shift->val << endl;
	}
};


template <typename T>
class IGraph {
public:
	virtual void addEdge(T a, T b) = 0;
};

enum class Color{White,Grey,Black};

template <typename T>
class Graph : public IGraph<T> {
private:
	map<T, LinkList<T>> list;
public:
	void addEdge(T a, T b)
	{
		list[a].Insert(b);
	}
	void printAdjacencyList()
	{
		for (auto i = list.begin(); i != list.end(); i++)
		{
			cout << i->first << ": ";
			list[i->first].printList();
		}
	}
	void BFS(T source) {
		queue<T> q;
		map<T, bool> visited;
		q.push(source);
		visited[source] = true;
		cout << "BFS from source " << source << endl;
		while (!q.empty())
		{
			T data = q.front();
			cout << data << " ";
			visited[data] = true;
			Node<T>* shift = list[data].head;
			while (shift != nullptr)
			{
				if (visited[shift->val] == false)
				{
					q.push(shift->val);
					visited[shift->val] = true;
				}
				shift = shift->next;
			}
			q.pop();
		}
		cout << "\n";
	}

	void dfs_recursive(T source, map<T, bool>& visited)
	{
		cout << source << " ";
		visited[source] = true;
		Node<T>* shift = list[source].head;
		while (shift != NULL)
		{
			if (visited[shift->val] == false)
			{
				dfs_recursive(shift->val, visited);
			}
			shift = shift->next;
		}
	}

	void DFS(T source)
	{
		map<int, bool>visited;
		visited[source] = true;
		cout << "DFS from source " << source << endl;
		dfs_recursive(source, visited);
	}
};

int main()
{
	Graph<int> g;
	g.addEdge(0, 1);
	g.addEdge(0, 9);
	g.addEdge(1, 2);
	g.addEdge(2, 0);
	g.addEdge(2, 3);
	g.addEdge(9, 3);
	g.printAdjacencyList();
	g.DFS(2);

}
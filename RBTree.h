#pragma once
#include<iostream>
using namespace std;
enum Color
{
	RED,
	BLACK,
};
template<class K, class V>
struct RBTreeNode
{
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;
	std::pair<K, V> _kv;
	Color _color;

	RBTreeNode(const pair<K, V>& kv)
	{
		_left = nullptr;
		_right = nullptr;
		_parent = nullptr;
		_kv = kv;
		_color = BLACK;
	}
};
template<class K, class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
private:
	Node* _root;

public:
	RBTree()
		:_root(nullptr)
	{}
	bool Insert(const pair<K, V>& kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
			return true;
		}
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_kv.first < kv.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_kv.first > kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}
		cur = new Node(kv);
		cur->_color = RED;
		if (parent->_kv.first > kv.first)
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		//����ƽ��
		while (parent && parent->_color == RED)//�϶��������ڵ�
		{
			Node* gparent = parent->_parent;
			if (parent == gparent->_left)
			{
				Node* uncle = gparent->_right;
				if (uncle && uncle->_color == RED)
				{
					parent->_color = uncle->_color = BLACK;
					gparent->_color = RED;
					cur = gparent;
					parent = cur->_parent;
				}
				else//uncle�����ڻ���Ϊ��ɫ,˵���Ѿ��е㲻ƽ����
				{
					if (cur == parent->_left)//���ҵ������
					{
						RotateR(gparent);
						parent->_color = BLACK;
						gparent->_color = RED;
					}
					else//˫��
					{
						RotateL(parent);
						RotateR(gparent);
						cur->_color = BLACK;
						gparent->_color = RED;
					}
					break;
				}
			}
			else//parent == gparent->_right ��������
			{
				Node* uncle = gparent->_left;
				if (uncle && uncle->_color == RED)
				{
					parent->_color = uncle->_color = BLACK;
					gparent->_color = RED;
					cur = gparent;
					parent = cur->_parent;
				}
				else
				{
					//       g
					//           p
					//				c
					if (cur == parent->_right)//���������
					{
						RotateL(gparent);
						parent->_color = BLACK;
						gparent->_color = RED;
					}
					//       g
					//           p
					//         c
					else
					{
						RotateR(parent);
						RotateL(gparent);
						cur->_color = BLACK;
						gparent->_color = RED;
					}
					break;
				}
			}
		}
		_root->_color = BLACK;
		return true;
	}
	void RotateL(Node* parent)
	{
		Node* subr = parent->_right;
		Node* subrl = subr->_left;

		Node* pparent = parent->_parent;
		parent->_parent = subr;
		subr->_left = parent;
		parent->_right = subrl;
		if (subrl)
			subrl->_parent = parent;
		if (parent == _root)
		{
			_root = subr;
			subr->_parent == nullptr;
		}

		else
		{
			if (pparent->_left == parent)
			{
				pparent->_left = subr;
			}
			else
			{
				pparent->_right = subr;
			}
			subr->_parent = pparent;
		}
	}
	void RotateR(Node* parent)
	{
		Node* subl = parent->_left;
		Node* sublr = subl->_right;
		//������תά��������
		parent->_left = sublr;
		if (sublr)
			sublr->_parent = parent;
		Node* pparent = parent->_parent;

		subl->_right = parent;
		parent->_parent = subl;

		if (parent == _root)
		{
			_root = subl;
			_root->_parent = nullptr;
		}
		else
		{
			if (pparent->_left == parent)
				pparent->_left = subl;
			else
				pparent->_right = subl;
			subl->_parent = pparent;
		}
	}
	bool IsBalance()
	{
		if (_root && _root->_color == RED)
		{
			cout << "���ڵ㲻�Ǻ�ɫ" << endl;
			return false;
		}
		int banchmark = 0;
		Node* left = _root;
		while (left)
		{
			if (left->_color == BLACK)
			{
				++banchmark;
			}
			left = left->_left;
		}
		int blackNum = 0;
		return _IsBalance(_root, banchmark, blackNum);
	}

	void InOrder()
	{
		_InOrder(_root);
	}
private:
	bool _IsBalance(Node* root, int banchmark, int blackNum)
	{
		if (root == nullptr)
		{
			if (banchmark != blackNum)
			{
				cout << "����·����ɫ�ڵ�����������" << endl;
				return false;
			}
			return true;
		}
		if (root->_color == RED && root->_parent->_color == RED)
		{
			cout << "�������ֺ�ɫ�ڵ�" << endl;
			return false;
		}
		if (root->_color == BLACK)
		{
			++blackNum;
		}
		return _IsBalance(root->_left, banchmark, blackNum)
			&& _IsBalance(root->_right, banchmark, blackNum)
	}
	int Height()
	{
		return _Height(_root);
	}

	void _InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		_InOrder(root->_left);
		cout << root->_kv.first << ":" << root->_kv.second << endl;
		_InOrder(root->_right);
	}
	int _Height(Node* root)
	{
		if (root == nullptr)
			return 0;
		int leftH = _Height(root->_left);
		int rightH = _Height(root->_right);
		return leftH > rightH ? leftH + 1 : rightH + 1;

	}
};

void test_RBTree()
{
	RBTree<int, int>rb;
	//int a[] = { 5,4,3,2,1,0 };
	//int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16,14 };
	for (auto e : a)
	{
		rb.Insert(std::pair<int, int>(e, e));
		//cout << "Insert:" << e << ":" << rb.IsBalance() << endl;//��֤ƽ�������Ƿ���ȷʱ����14ʱ��������
	}
	rb.InOrder();
	cout << rb.IsBalance() << endl;
}
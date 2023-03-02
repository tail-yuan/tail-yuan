#pragma once

template<class K, class V>
struct AVLTreeNode
{
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;
	pair<K, V> _kv;

	int _bf; // balance factor

	AVLTreeNode(const pair<K, V>& kv)
		:_left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _bf(0)
		, _kv(kv)
	{}
};

template<class K,class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	AVLTree()
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
		if (parent->_kv.first < kv.first)
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_left = cur;
			cur->_parent = parent;
		}

		// 控制平衡
		// 1、更新平衡因子 -- 新增节点到根节点的祖先路径
		// 2、出现异常平衡因子，那么需要旋转平衡处理
		while (parent)
		{
			if (cur == parent->_left)
				parent->_bf--;
			else
				parent->_bf++;

			if (parent->_bf == 0)
			{
				break;
			}
			else if (parent->_bf == 1 || parent->_bf == -1)
			{
				// 继续往上更新
				cur = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == 2 || parent->_bf == -2)
			{
				if (parent->_bf == -2 && cur->_bf == -1)
				{
					RotateR(parent);
				}
				else if (parent->_bf == 2 && cur->_bf == 1)
				{
					RotateL(parent);
				}
				else if (parent->_bf == -2 && cur->_bf == 1)
				{
					RotateLR(parent);
				}
				else if (parent->_bf == 2 && cur->_bf == -1)
				{
					RotateRL(parent);
				}
				break;
			}
			else
			{
				// 说明插入更新平衡因子之前，树中平衡因子就有问题了
				assert(false);
			}
		}
		return true;
	}
	void RotateLR(Node* parent)
	{
		Node* subl = parent->_left;
		Node* sublr = subl->_right;
		int bf = sublr->_bf;

		RotateL(parent->_left);
		RotateR(parent);

		if (bf == -1)
		{
			parent->_bf = 1;
		}
		else if (bf == 1)
		{
			subl->_bf = -1;
		}
		else if (bf == 0)
		{
		}
		else
		{
			assert(false);
		}
	}
	void RotateRL(Node* parent)
	{
		Node* subr = parent->_right;
		Node* subrl = subr->_left;
		int bf = subrl->_bf;

		RotateR(parent->_right);
		RotateL(parent);

		if (bf == 1)
		{
			parent->_bf = -1;
		}
		else if (bf == -1)
		{
			subr->_bf = 1;
		}
		else if (bf == 0)
		{
			//
		}
		else
		{
			assert(false);
		}
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
		subr->_bf = parent->_bf = 0;
	}
	void RotateR(Node* parent)
	{
		Node* subl = parent->_left;
		Node* sublr = subl->_right;
		//进行旋转维护三叉连
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
		subl->_bf = parent->_bf = 0;
	}
	void InOrder()
	{
		_InOrder(_root);
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
	bool IsBalance()
	{
		return _IsBalance(_root);
	}
	bool _IsBalance(Node* root)
	{
		if (root == nullptr)
			return true;
		int leftHeight = Height(root->_left);
		int rightHeight = Height(root->_right);

		if (rightHeight- leftHeight!= root->_bf)
		{
			cout << root->_kv.first << "应该是:" << rightHeight - leftHeight << endl;
			cout << root->_kv.first << "实际是:" << root->_bf << endl;
			return false;
		}
		return abs(leftHeight-rightHeight)<2
			&& _IsBalance(root->_left)
			&& _IsBalance(root->_right);
	}
	int Height(Node* root)
	{
		if (root == nullptr)
			return 0;
		int leftHeight = Height(root->_left);
		int rightHeight = Height(root->_right);
		return leftHeight > rightHeight ? leftHeight+1 : rightHeight + 1;
	}
private:
	Node* _root;
};
void test_AVLTree()
{
	AVLTree<int, int>avl;
	//int a[] = { 5,4,3,2,1,0 };
	//int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	int a[] =  {4, 2, 6, 1, 3, 5, 15, 7, 16,14 };
	for (auto e : a)
	{
		avl.Insert(make_pair(e, e));
		cout << "Insert:" << e << ":" << avl.IsBalance() << endl;//验证平衡因子是否正确时插入14时出现问题
	}
	avl.InOrder();
	cout << avl.IsBalance() << endl;
}
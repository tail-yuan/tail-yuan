#pragma once

namespace K
{
	template<class T>
	struct BinarySearchTreeNode
	{
		BinarySearchTreeNode<T>* _left;
		BinarySearchTreeNode<T>* _right;
		T _key;
		BinarySearchTreeNode(const T& key)
			:_key(key)
			, _left(nullptr)
			, _right(nullptr)
		{}
	};
	template<class T>
	class BSTree
	{
		typedef BinarySearchTreeNode<T> Node;
	public:
		BSTree()
			:_root(nullptr)
		{}
		bool Insert(const T& key)
		{
			if (_root == nullptr)
			{
				_root = new Node(key);
			}
			//不是第一次
			Node* parent = nullptr;
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key < key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else if (cur->_key > key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else
				{
					return false;
				}
			}
			cur = new Node(key);
			if (key > parent->_key)
			{
				parent->_right = cur;
			}
			else
			{
				parent->_left = cur;
			}
			return true;
		}
		void InOrder()
		{
			_InOrder(_root);
		}
		void _InOrder(Node* root)
		{
			if (root == nullptr)
				return;
			_InOrder(root->_left);
			cout << root->_key << " ";
			_InOrder(root->_right);
		}
		Node* Find(const T& key)
		{
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key > key)
					cur = cur->_left;
				else if (cur->_key < key)
					cur->_right;
				else
					return cur;
			}
			return nullptr;
		}
		bool Erase(const T& key)
		{
			Node* parent = nullptr;
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key < key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else if (cur->_key > key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else
				{
					if (cur->_left == nullptr)
					{
						if (parent == nullptr)
							_root = cur->_right;

						if (parent->_left == cur)
							parent->_left = cur->_right;
						else
							parent->_right = cur->_right;

						delete cur;
					}
					else if (cur->_right == nullptr)
					{
						if (parent == nullptr)
							_root = cur->_left;

						if (parent->_left == cur)
							parent->_left = cur->_left;
						else
							parent->_right = cur->_left;

						delete cur;
					}
					else
					{
						//右子树,找最小节点
						Node* tmp = cur->_right;
						Node* ptmp = cur;
						while (tmp->_left)
						{
							ptmp = tmp;
							tmp = tmp->_left;
						}
						swap(cur->_key, tmp->_key);
						//不能直接删,可能最左节点还有右孩子需要和父亲连接
						if (ptmp->_left == tmp)
							ptmp->_left = tmp->_right;
						else
							ptmp->_right = tmp->_right;

						delete tmp;
					}
					return true;
				}
			}
			return false;
		}
		bool InsertR(const T& key)
		{
			return _InsertR(_root, key);
		}
		bool _InsertR(Node*& root, const T& key)
		{
			if (root == nullptr)//找到要插入的位置了
			{
				root = new Node(key);
				return true;
			}

			if (root->_key < key)
				return _InsertR(root->_right, key);
			else if (root->_key > key)
				return _InsertR(root->_left, key);
			else
				return false;
		}
		Node* FindR(const T& key)
		{
			return _FindR(_root, key);
		}
		Node* _FindR(Node* root, const T& key)
		{
			if (root == nullptr)return nullptr;
			if (key > root->_key)
				return _FindR(root->_right, key);
			else if (key < root->_key)
				return _FindR(root->_left, key);
			else
				return root;//一层层往回返回,可以记录路径使用
		}
		bool EraseR(const T& key)
		{
			return _EraseR(_root, key);
		}
		bool _EraseR(Node*& root, const T& key)
		{
			if (root == nullptr)return false;
			if (root->_key < key)
				return _EraseR(root->_right, key);
			else if (root->_key > key)
				return _EraseR(root->_left, key);
			else
			{
				Node* del = root;
				if (root->_left == nullptr)//下面的两个孩子节点的那个下一次递归到这删除(值相等,其实就是下一次子树调用根节点)
				{
					root = root->_right;//要删的节点的地址,也是节点他爹的右孩子指针的别名,直接连就行了
				}
				else if (root->_right == nullptr)
				{
					root = root->_left;
				}
				else
				{
					//右子树最左节点替换删除
					Node* min = root->_right;
					while (min->_left)
					{
						min = min->_left;
					}
					//T tmp = root->_key;
					//cout << "root->key:" << tmp << endl;
					/*cout << "min->key:" << min->_key << endl; */
					swap(min->_key, root->_key);
					/*cout << "root->key:" << tmp << endl;
					cout << "min->key:" << min->_key << endl;*/
					//递归调用自己,从自己的右子树删除那个数的节点
					//cout << "root->_right->key" << root->_right->_key << endl;
					//return _EraseR(root->_right, tmp);//用tmp提前记录也可
					return _EraseR(root->_right, key);//我想要删除的数就是7,即使我把7和8调换了,我往下传的想要删除的值还是7

				}
				delete del;
				return true;
			}
		}
	private:
		Node* _root;
	};

	void TestBSTree()
	{
		BSTree<int>bt;
		int a[] = { 5,3,4,1,7,8,2,6,0,9,1,2,3,4 };
		for (auto e : a)
		{
			bt.InsertR(e);
		}
		bt.InOrder();
		cout << endl;

		bt.EraseR(7);
		bt.InOrder();
		cout << endl;

		/*bt.EraseR(5);
		bt.InOrder();
		cout << endl;

		bt.EraseR(1);
		bt.InOrder();
		cout << endl;*/

	}
}
namespace K_V
{
#pragma once

	template<class T,class V>
	struct BinarySearchTreeNode
	{
		BinarySearchTreeNode<T,V>* _left;
		BinarySearchTreeNode<T,V>* _right;
		T _key;
		V _val;
		BinarySearchTreeNode(const T& key,const V& value)
			:_key(key)
			,_val(value)
			, _left(nullptr)
			, _right(nullptr)
		{}
	};
	template<class T,class V>
	class BSTree
	{
		typedef BinarySearchTreeNode<T,V> Node;
	public:
		BSTree()
			:_root(nullptr)
		{}
		bool Insert(const T& key,const V& value)
		{
			if (_root == nullptr)
			{
				_root = new Node(key,value);
			}
			//不是第一次
			Node* parent = nullptr;
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key < key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else if (cur->_key > key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else
				{
					return false;
				}
			}
			cur = new Node(key,value);
			if (key > parent->_key)
			{
				parent->_right = cur;
			}
			else
			{
				parent->_left = cur;
			}
			return true;
		}
		void InOrder()
		{
			_InOrder(_root);
			cout << endl;
		}
		void _InOrder(Node* root)
		{
			if (root == nullptr)
				return;
			_InOrder(root->_left);
			cout << root->_key << ":" << root->_val << endl;;
			_InOrder(root->_right);
		}
		Node* Find(const T& key)
		{
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key > key)
					cur = cur->_left;
				else if (cur->_key < key)
					cur=cur->_right;
				else
					return cur;
			}
			return nullptr;
		}
		bool Erase(const T& key)
		{
			Node* parent = nullptr;
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key < key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else if (cur->_key > key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else
				{
					if (cur->_left == nullptr)
					{
						if (parent == nullptr)
							_root = cur->_right;

						if (parent->_left == cur)
							parent->_left = cur->_right;
						else
							parent->_right = cur->_right;

						delete cur;
					}
					else if (cur->_right == nullptr)
					{
						if (parent == nullptr)
							_root = cur->_left;

						if (parent->_left == cur)
							parent->_left = cur->_left;
						else
							parent->_right = cur->_left;

						delete cur;
					}
					else
					{
						//右子树,找最小节点
						Node* tmp = cur->_right;
						Node* ptmp = cur;
						while (tmp->_left)
						{
							ptmp = tmp;
							tmp = tmp->_left;
						}
						swap(cur->_key, tmp->_key);
						swap(cur->_val,tmp->_val);

						//不能直接删,可能最左节点还有右孩子需要和父亲连接
						if (ptmp->_left == tmp)
							ptmp->_left = tmp->_right;
						else
							ptmp->_right = tmp->_right;

						delete tmp;
					}
					return true;
				}
			}
			return false;
		}
	private:
		Node* _root;
	};

	void TestBSTree()
	{
		// 字典KV模型
		BSTree<string, string> dict;
		dict.Insert("sort", "排序");
		dict.Insert("left", "左边");
		dict.Insert("right", "右边");
		dict.Insert("map", "地图、映射");
		//...

		string str;
		while (cin >> str)
		{
			BinarySearchTreeNode<string, string>* ret = dict.Find(str);
			if (ret)
			{
				cout << "对应中文解释：" << ret->_val << endl;
			}
			else
			{
				cout << "无此单词" << endl;
			}
		}

	}

	void TestBSTree2()
	{
		// 统计水果出现次数
		string arr[] = { "苹果", "西瓜","草莓", "苹果", "西瓜", "苹果", "苹果", "西瓜", "苹果", "香蕉", "苹果", "香蕉" };
		BSTree<string, int> countTree;
		for (auto& str : arr)
		{
			//BSTreeNode<string, int>* ret = countTree.Find(str);
			auto ret = countTree.Find(str);
			if (ret != nullptr)
			{
				ret->_val++;
			}
			else
			{
				countTree.Insert(str, 1);
			}
		}

		countTree.InOrder();

	}
}
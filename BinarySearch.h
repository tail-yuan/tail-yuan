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
			//���ǵ�һ��
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
						//������,����С�ڵ�
						Node* tmp = cur->_right;
						Node* ptmp = cur;
						while (tmp->_left)
						{
							ptmp = tmp;
							tmp = tmp->_left;
						}
						swap(cur->_key, tmp->_key);
						//����ֱ��ɾ,��������ڵ㻹���Һ�����Ҫ�͸�������
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
			if (root == nullptr)//�ҵ�Ҫ�����λ����
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
				return root;//һ������ط���,���Լ�¼·��ʹ��
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
				if (root->_left == nullptr)//������������ӽڵ���Ǹ���һ�εݹ鵽��ɾ��(ֵ���,��ʵ������һ���������ø��ڵ�)
				{
					root = root->_right;//Ҫɾ�Ľڵ�ĵ�ַ,Ҳ�ǽڵ��������Һ���ָ��ı���,ֱ����������
				}
				else if (root->_right == nullptr)
				{
					root = root->_left;
				}
				else
				{
					//����������ڵ��滻ɾ��
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
					//�ݹ�����Լ�,���Լ���������ɾ���Ǹ����Ľڵ�
					//cout << "root->_right->key" << root->_right->_key << endl;
					//return _EraseR(root->_right, tmp);//��tmp��ǰ��¼Ҳ��
					return _EraseR(root->_right, key);//����Ҫɾ����������7,��ʹ�Ұ�7��8������,�����´�����Ҫɾ����ֵ����7

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
			//���ǵ�һ��
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
						//������,����С�ڵ�
						Node* tmp = cur->_right;
						Node* ptmp = cur;
						while (tmp->_left)
						{
							ptmp = tmp;
							tmp = tmp->_left;
						}
						swap(cur->_key, tmp->_key);
						swap(cur->_val,tmp->_val);

						//����ֱ��ɾ,��������ڵ㻹���Һ�����Ҫ�͸�������
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
		// �ֵ�KVģ��
		BSTree<string, string> dict;
		dict.Insert("sort", "����");
		dict.Insert("left", "���");
		dict.Insert("right", "�ұ�");
		dict.Insert("map", "��ͼ��ӳ��");
		//...

		string str;
		while (cin >> str)
		{
			BinarySearchTreeNode<string, string>* ret = dict.Find(str);
			if (ret)
			{
				cout << "��Ӧ���Ľ��ͣ�" << ret->_val << endl;
			}
			else
			{
				cout << "�޴˵���" << endl;
			}
		}

	}

	void TestBSTree2()
	{
		// ͳ��ˮ�����ִ���
		string arr[] = { "ƻ��", "����","��ݮ", "ƻ��", "����", "ƻ��", "ƻ��", "����", "ƻ��", "�㽶", "ƻ��", "�㽶" };
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
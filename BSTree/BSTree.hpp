#pragma once
#include<iostream>
using namespace std;

template<class K, class V>
class BSTreeNode {
public:
	const K _key;
	V _value;

	class BSTreeNode<K, V>* _left;
	class BSTreeNode<K, V>* _right;

	BSTreeNode(const K& key, const V& value)
		: _key(key)
		, _value(value)
		, _left(nullptr)
		, _right(nullptr)
	{}

};

template<class K, class V>
class BSTree {
	typedef BSTreeNode<K, V> Node;
public:
	bool Insert(const K& key, const V& value) {
		if (_root == nullptr) {
			_root = new Node(key, value);
			return true;
		}

		//Ѱ��λ��
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur) {
			if (cur->_key > key) {
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_key < key) {
				parent = cur;
				cur = cur->_right;
			}
			else {
				return false;
			}
		}

		//�������
		Node* node = new Node(key, value);
		if (parent->_key > key) {
			parent->_left = node;
		}
		else {
			parent->_right = node;
		}

		return true;
	}

	Node* Find(const K& key) {
		Node* cur = _root;
		while (cur) {
			if (cur->_key == key) {
				return cur;
			}
			else if(cur->_key < key) {
				cur = cur->_right;
			}
			else {
				cur = cur->_left;
			}
		}
		
		return nullptr;
	}

	bool Erase(const K& key) {
		if (_root == nullptr)
			return false;

		Node* parent = nullptr;
		Node* cur = _root;
		while (cur) {
			if (key == cur->_key) {
				break;
			}
			else if (key < cur->_key) {
				parent = cur;
				cur = cur->_right;
			}
			else {
				parent = cur;
				cur = cur->_left;
			}
		}

		if (nullptr == parent)
			return false;

		if (nullptr == cur->_right) {
			//��ǰ���ֻ�����ӻ�������Ϊ��
			if (parent->_left == cur)
				parent->_left = cur->_left;
			else
				parent->_right = cur->_left;
			delete cur;
		}
		else if (nullptr == cur->_left) {
			//��ǰ���ֻ���Һ���
			if (parent->_left == cur)
				parent->_left = cur->_right;
			else
				parent->_right = cur->_right;
			delete cur;
		}
		else {
			//���Ӿ�����
			//�������������ڵ㣬����������С�Ľ��
			//���������ֵ������ɾ�����
			//1.
			parent = cur;
			Node* maxleft = cur->_left;
			while (maxleft) {
				parent = maxleft;
				maxleft = maxleft->_right;
			}

			swap(cur->_key, maxleft->_key);

			if (maxleft->_left != nullptr)
				parent->_right = maxleft->_left;
			else
				parent->_right = nullptr;

			delete maxleft;
		}
	}

	void _InOrder(Node* root) {
		if (root == nullptr)
			return;

		_InOrder(root->_left);
		cout << root->_key << ":" << root->_value << endl;
		_InOrder(root->_right);
	}

	void InOrder() {
		_InOrder(_root);
		cout << endl;
	}

private:
	Node* _root = nullptr;
};
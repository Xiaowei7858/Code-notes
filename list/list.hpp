#pragma once

namespace list_realize {
	template<class T>

	//listnode节点
	struct ListNode {
		ListNode(const T& val = T());
		ListNode<T>* _pPre;
		ListNode<T>* _pNext;
		T _val;
	};

	//list的迭代器类
	template<class T, class Ref, class Ptr>
	class ListIterator {
		typedef ListNode<T>* PNode;
		typedef ListIterator<T, Ref, Ptr> Self;
	public:
		ListIterator(PNode pNode = nullptr)
			: _pNode(pNode)
		{}

		ListIterator(const Self& s)
			: _pNode(s._pNode)
		{}

		bool operator!=(const self& s) const {
			return _pNode != s._pNode;
		}

		bool operator==(const self& s) const {
			return !(*this != s);
		}

		Ptr operator->() const {
			return &_pNode->_val;
		}

		Ref operator*() const {
			return _pNode->_val;
		}

		//++it it.operator(&it)
		Self& operator++() {
			_pNode = _pNode->_pNext;
			return *this;
		}

		//it++ it.operator(&it,0)
		Self operator++(int) {
			self tmp(*this);
			_node = _node->_next;
			return tmp;
		}

		Self& operator--() {
			_pNode = _pNode->_pPre;
			return *this;
		}

		Self operator--(int) {
			self tmp(*this);
			_node = _node->_pPre;
			return tmp;
		}

		PNode _pNode;
	};

	template<class T>
	class list {
		typedef ListNode<T> Node;
		typedef Node* pNode;
	public:
		typedef ListIterator<T, T&, T*> iterator;
		typedef ListIterator<T, const T&, const T&>const_iterator;
		
		iterator begin() {
			return iterator(_head->_next);
		}

		iterator end() {
			return _head;
		}

		const_iterator begin() const {
			return _head->_next;
		}

		const_iterator end() const {
			return _head;
		}

		//构造
		list() {
			_head = new Node;
			_head->_pNext = _head;
			_head->_pPre = _head;
		}

		template<class InputIterator>
		//迭代器构造
		list(InputIterator first, InputIterator last) {
			_head = new Node;
			_head->_pNext = _head;
			_head->_pPre = _head;

			while (first != last) {
				push_back(*first);
				++first;
			}
		}

		list(const list<T>& lt) {
			_head = new Node;
			_head->_pNext = _head;
			_head->_pPre = _head;
			
			list<T> tmp(lt.begin(), lt.end());
			std::swap(_head, tmp._head);
		}

		//lt1 = lt2
		list<T>& operator=(list<T> lt) {
			std::swap(_head, lt._head);
			return *this;
		}

		//lt2(lt1)
		list(const list<T>& lt) {
			_head = new Node;
			_head->_pNext = _head;
			_head->_pPre = _head;

			const_iterator it = lt.begin();
			while (it != lt.end()) {
				push_back(*it);
				++it;
			}
		}

		~list() {
			clear();
			delete _head;
			_head = nullptr;
		}

		void clear() {
			iterator it = begin();
			while (it != end()) {
				erase(it++);
			}
		}

		void push_back(const T& x) {
			insert(end(), x);
		}

		void push_front(const T& x) {
			insert(begin(), x);
		}

		void pop_front() {
			erase(begin());
		}

		iterator insert(iterator pos, const T& x) {
			Node* Newnode = new Node(x);
			Node* cur = pos._pNode;
			Node* prev = cur->_pPre;

			prev->_pNext = Newnode;
			Newnode->_pPre = prev;
			Newnode->_pNext = cur;
			cur->_pPre = Newnode;

			return iterator(Newnode);
		}

		iterator erase(iterator pos) {
			assert(pos != end());

			Node* cur = pos._pNode;
			Node* prev = cur->_pPre;
			Node* next = cur->_pNext;

			prev->_pNext = cur;
			cur->_pPre = prev;

			delete cur;

			return iterator(next);
		}

	private:
		//双向带头循环
		Node* _head;
	};
}
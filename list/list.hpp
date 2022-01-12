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

		ListIterator(const Self& l)
			: _pNode(l._pNode)
		{}

		T& operator*() {
			return _pNode->_val;
		}

		T* operator->() {
			return &(operator*());
		}

		Self& operator++() {
			_pNode = _pNode->_pNext;
			return *this;
		}

		PNode _pNode;
	};

	class list {

	public:
	private:

	};
}
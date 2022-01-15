#pragma once
#include<vector>
#include<assert.h>
using namespace std;
namespace my_priorityqueue {
	template<class T>
	class less {
		bool operator()(const T& left, const T& right) {
			return left < right;
		}
	};

	template<class T>
	class greater {
		bool operator()(const T& left, const T& right) {
			return left > right;
		}
	};

	template<class T, class Container = vector<T>, class Compare = less<T>>
	class priority_queue {
	public:
		priority_queue()
			: _c()
		{}

		template<class Iterator>
		priority_queue(Iterator first, Iterator last)
			: _c(first, last)
		{
			//调整为堆结构
			int size = _c.size();
			int root = (size - 2) >> 1;
			for (; root >= 0; root--) {
				AdjustDown(root);
			}
		}

		void push(const T& data) {
			_c.push_back(data);
			AdjustUp(_c.size() - 1);
		}

		void pop(const T& data) {
			assert(_c.size() > 0);

			swap(_c.front(), _c.back());
			_c.pop_back();
			AdjustDown(0);
		}
		
		size_t size() const {
			return _c.size();
		}

		const T& top() const {
			return _c.front();
		}

		bool empty() const
		{
			return _con.empty();
		}

	private:

		void AdjustUp(int child) {
			Compare com;
			int parent = (child - 1) >> 1;
			while (child) {
				if (com()(_c[parent], _c[child])) {
					swap(_c[child], _c[parent]);
					child = parent;
					parent = (child - 1) >> 1;
				}
				else
					return;
			}
		}

		void AdjustDown(int parent) {
			Compare com;
			int child = parent * 2 + 1;
			while (child < _c.size()) {
				if (child + 1 < _c.size() && com()(_c[child], _c[child + 1]))
					child += 1;
				if (com()(_c[parent], _c[child])) {
					swap(_c[child], _c[parent]);
					parent = child;
					child = parent * 2 + 1;
				}
				else
					return;
			}
		}

		Container _c;
	};
}
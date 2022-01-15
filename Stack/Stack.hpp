#pragma once
#include<deque>
using namespace std;
namespace mystack {
	// 设计模式 -- 适配器模式(配接器)
	template<class T, class Container = deque<T>>
	class stack {
	public:
		void push(const T& x) {
			_c.push_back(x);
		}

		void pop() {
			_c.pop_back();
		}

		const T& top() const {
			return _c.back();
		}

		size_t size() const {
			return _c.size();
		}

		bool empty() const {
			return _c.empty();
		}
	private:
		Container _c;
	};
};
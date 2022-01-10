#include<iostream>
using namespace std;
#include<assert.h>

namespace bit {
	template<class T>
	class vector {
	public:
		typedef T* iterator;
		typedef const T* const_iterator;

		iterator begin() {
			return _start;
		}

		iterator end() {
			return _end;
		}

		const_iterator cbegin() const {
			return _start;
		}

		const_iterator cend() const {
			return _end;
		}

		vector()
			: _start(nullptr),
			_end(nullptr),
			_endofStorage(nullptr);
		{}

		vector(int n, const T& value = T()) 
			: _start(nullptr)
			, _end(nullptr)
			, _endofStorage(nullptr)
		{
			reserve(n);
			while (n--) {
				push_back(value);
			}
		}

		template<class InputIterator>
		vector(InputIterator first, InputIterator last) 
			: _start(nullptr)
			，_end(nullptr)
			, _endofStorage(nullptr)
		{
			reserve(last - first);
			while (first != last) {
				push_back(*first);
				++first;
			}
		}

		void swap(const vector<T>& v) {
			std::swap(_start, v._start);
			std::swap(_end, v._end);
			std::swap(_endofStorage, v._endofStorage);
		}

		vector(const vector<T>& v) 
			: _start(nullptr)
			, _end(nullptr)
			, _endofStorage(nullptr)
		{
			vector<T> tmp = vector(v.start(), v.end());
			this->swap(tmp);
		}

		vector<T>& operator=(vector<T> v) {
			this->swap(v);
			return this;
		}

		~vector() {
			delete[] _start;
			_start = _end = _endofStorage = nullptr;
		}

		size_t size() const {
			return _end - _start;
		}

	private:
		iterator _start;
		iterator _end;
		iterator _endofStorage; //指向存储容量的尾
	};
}
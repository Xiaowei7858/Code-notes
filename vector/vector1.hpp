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

		size_t capacity() const {
			return _endofStorage - _start;
		}

		void reserve(size_t n) {
			if (n > capacity()) {
				size_t oldSize = size();
				T* tmp = new T[n];

				if (_start) {
					for (size_t i = 0; i < oldSize; ++i) {
						tmp[i] = _start[i];
					}
				}

				_start = tmp;
				_end = _start + oldSize;
				_endofStorage = _start + n;
			}
		}

		void resize(size_t n, const T& value = T()) {
			//1.如果n小于当前的size，则数据个数缩小的n
			if (n <= size()) {
				_end = _start + n;
				return;
			}
			//2.空间不够则增容
			if (n > capacity()) {
				reserve(n);
			}
			//3.将size扩大到n
			iterator it = _end;
			_end = _start + n;
			while (it != _end) {
				*it = value;
				++it;
			}
		}

		///////////////access///////////////////////////////

		T& operator[](size_t pos) {
			return _start[pos];
		}

		const T& operator[](size_t pos)const {
			return _start[pos];
		}

		///////////////modify/////////////////////////////

		void push_back(const T& x) {
			check_capacity();
			insert(end(), x);
		}

		void pop_back() {
			erase(--end());
		}


		void check_capacity()
		{
			if (_finish == _endofstorage)
			{
				size_t newcapacity = capacity() == 0 ? 1 : capacity() * 2;
				reserve(newcapacity);
			}
		}

		iterator insert(iterator pos, const T& x) {
			assert(pos <= _end);

			if (_end == _endofStorage) {
				check_capacity();

				//重置pos
				pos = _start + size();
			}

			iterator end = _end - 1;
			while (end >= pos) {
				*(end + 1) = *end;
				--end;
			}

			*pos = x;
			++_end;
			return pos;
		}

		iterator erase(Iterator pos) {
			iterator begin = pos + 1;
			while (begin != _end) {
				*(begin - 1) = *begin;
				++begin;
			}

			--_end;
			return pos;
		}

	private:
		iterator _start;
		iterator _end;
		iterator _endofStorage; //指向存储容量的尾
	};
}